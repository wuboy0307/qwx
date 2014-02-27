/*                                                                              
 * Copyright (C) 2014 ISOFT INFRASTRUCTURE SOFTWARE CO., LTD.
 *               2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>
 *                                                                              
 * This program is free software: you can redistribute it and/or modify         
 * it under the terms of the GNU General Public License as published by         
 * the Free Software Foundation, either version 3 of the License, or            
 * any later version.                                                           
 *                                                                              
 * This program is distributed in the hope that it will be useful,              
 * but WITHOUT ANY WARRANTY; without even the implied warranty of               
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                
 * GNU General Public License for more details.                                 
 *                                                                              
 * You should have received a copy of the GNU General Public License            
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.        
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "my_curl.h"

typedef struct {
    char *ptr;
    size_t len;
} chunk_t;

static CURL *m_curl = NULL;
static chunk_t m_c;

static int m_chunk_init(chunk_t *c);
static size_t m_callback(void *ptr, size_t size, size_t nmemb, chunk_t *s);

static int m_chunk_init(chunk_t *c) 
{
    c->len = 0;
    int size = c->len + 1;
    c->ptr = malloc(size);
    if (c->ptr == NULL) {
        printf("ERROR: fail to allocate chunk!\n");
        return -1;
    }
    memset(c->ptr, size, 0);
    return 0;
}

static size_t m_callback(void *ptr, size_t size, size_t nmemb, chunk_t *c) 
{
    size_t new_len = c->len + size * nmemb;
    c->ptr = realloc(c->ptr, new_len + 1);
    if (c->ptr == NULL) {
        printf("ERROR: fail to allocate chunk!\n");
        return -1;
    }
    memcpy(c->ptr + c->len, ptr, size * nmemb);
    c->ptr[new_len] = '\0';
    c->len = new_len;

    return size * nmemb;
}

int my_curl_init(char *url, int timeout) 
{
    if (m_chunk_init(&m_c) != 0) 
        return -1;
 
    curl_global_init(CURL_GLOBAL_DEFAULT);
    m_curl = curl_easy_init();
    if (!m_curl) 
        return -1;

    curl_easy_setopt(m_curl, CURLOPT_URL, url);
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, timeout);
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(m_curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(m_curl, CURLOPT_COOKIEFILE, ""); /* just to start the cookie engine */

    return 0;
}

char *my_curl_get_content() 
{
    if (m_curl == NULL) 
        return NULL;

    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &m_c);
    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, &m_callback);

    CURLcode res = curl_easy_perform(m_curl);
    if (res != CURLE_OK) {
        printf("ERROR: %s\n", curl_easy_strerror(res));
        return NULL;
    }

    return m_c.ptr;
}

void my_curl_post_json(char *str) 
{
    if (m_curl) 
        return;

    struct curl_slist *headerlist = NULL;
    char content_len[BUFFER_SIZE] = {'\0'};
    snprintf(content_len, BUFFER_SIZE, "Content-Length: %d", (int)strlen(str));
    headerlist = curl_slist_append(headerlist, "Content-Type: application/json");
    headerlist = curl_slist_append(headerlist, content_len);

    curl_easy_setopt(m_curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, str);
    curl_easy_setopt(m_curl, CURLOPT_HTTPHEADER, headerlist);

    CURLcode res = curl_easy_perform(m_curl);                                   
    if (res != CURLE_OK) 
        printf("ERROR: %s\n", curl_easy_strerror(res));                         
}

void my_curl_cleanup() 
{
    if (m_curl) {
        curl_easy_cleanup(m_curl);
        curl_global_cleanup();
        m_curl = NULL;
    }
}

struct curl_slist *my_curl_get_cookies()                                                       
{                                                                               
    CURLcode res;                                                                 
    struct curl_slist *nc = NULL, *cookies = NULL;
    int i;                                                                        
    
    if (m_curl == NULL) 
        return cookies;

    res = curl_easy_getinfo(m_curl, CURLINFO_COOKIELIST, &cookies);                 
    if (res != CURLE_OK) {                                                        
        printf("ERROR: %s\n", curl_easy_strerror(res));
        return cookies;                                     
    }                                                                             
    nc = cookies, i = 1;                                                          
    while (nc) {
#if DEBUG        
        printf("DEBUG: [%d]: %s\n", i, nc->data);
#endif
        char domain[BUFFER_SIZE] = {'\0'};
        char arg2[BUFFER_SIZE] = {'\0'};
        char path[BUFFER_SIZE] = {'\0'};
        char exp[BUFFER_SIZE] = {'\0'};
        unsigned long timestamp = 0;
        char key[BUFFER_SIZE] = {'\0'};
        char val[BUFFER_SIZE] = {'\0'};
        sscanf(nc->data, "%s\t%s\t%s\t%s\t%lu\t%s\t%s", 
            domain, arg2, path, exp, &timestamp, key, val);
        printf("DEBUG: %s %s %s %s %lu %s %s\n", 
            domain, arg2, path, exp, timestamp, key, val);
        nc = nc->next;                                                              
        i++;                                                                        
    }                                                                             
    if (i == 1) {                                                                 
        printf("DEBUG: (none)\n");                                                         
    }

    return cookies;    
}

void my_curl_set_cookies(struct curl_slist *cookies) 
{
    CURLcode res;
    struct curl_slist *nc;
    nc = cookies;
    while (nc) {
        printf("DEBUG: set cookie %s\n", nc->data);
        res = curl_easy_setopt(m_curl, CURLOPT_COOKIELIST, nc->data);
        if (res != CURLE_OK) 
            printf("ERROR: %s\n", curl_easy_strerror(res));
        nc = nc->next;
    }
}
