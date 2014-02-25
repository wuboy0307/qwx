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
#include <curl/curl.h>

#include "http_get.h"

typedef struct {
    char *ptr;
    size_t len;
} chunk_t;

static int m_chunk_init();
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

char *http_get(char *url, int timeout) 
{
    CURL *curl = NULL;
    CURLcode res;
    chunk_t c;
    if (m_chunk_init(&c) != 0) 
        return NULL;
 
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) 
        return NULL;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &c);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &m_callback);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        printf("ERROR: %s\n", curl_easy_strerror(res));
        return NULL;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return c.ptr;
}
