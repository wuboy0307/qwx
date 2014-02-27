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
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

#include "config.h"
#include "webwx.h"

static struct curl_slist *m_cookies = NULL;

static void m_get_quote(char *ori, char *dst);

static void m_get_quote(char *ori, char *dst) 
{
    regex_t regex;                                                              
    regmatch_t pmatch[1];                                                       
    if (regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED) != 0)                     
        return;                                                            
    if (regexec(&regex, ori, 1, pmatch, 0) == 0)                            
        strncpy(dst, ori + pmatch[0].rm_so + 1, pmatch[0].rm_eo - pmatch[0].rm_so - 2); 
    regfree(&regex);
}

char *webwx_get_uuid(char *uuid, UUID_CALLBACK fptr) 
{
    if (uuid == NULL) 
        return NULL;

    char url[BUFFER_SIZE] = {'\0'}; 
    snprintf(url, BUFFER_SIZE, "https://login.weixin.qq.com/jslogin?appid="          
        "wx782c26e4c19acffb&redirect_uri=https://wx.qq.com/cgi-bin/mmwebwx-bin" 
        "/webwxnewloginpage&fun=new&lang=zh_CN&_=%d", (int)time(NULL));
    if (my_curl_init(url, 0) != 0) 
        return NULL;
    char *content = my_curl_get_content();
    my_curl_cleanup();
    if (content == NULL) {
        if (fptr) 
            fptr(NULL);
        return NULL;
    }

    m_get_quote(content, uuid);
    free(content);
    content = NULL;
    if (fptr) 
        fptr(uuid);
    return uuid;
}

char *webwx_wait_scan(char *uuid, int timestamp, int timeout, char *redirect_uri) 
{
    char url[BUFFER_SIZE] = {'\0'};
    snprintf(url, BUFFER_SIZE, "https://login.weixin.qq.com/cgi-bin/"
        "mmwebwx-bin/login?uuid=%s&tip=0&_=%d", uuid, timestamp);
#ifdef DEBUG
    printf("DEBUG: %s\n", url);
#endif
    if (my_curl_init(url, timeout) != 0) 
        return NULL;
    char *content = my_curl_get_content();
    my_curl_cleanup();
    if (content == NULL) 
        return NULL;
#ifdef DEBUG
    printf("DEBUG: %s\n", content);
#endif
    if (strstr(content, "200")) { 
        m_get_quote(content, redirect_uri);
        free(content);
        content = NULL;
        return redirect_uri;
    }

    return NULL;
}

int webwx_get_cookie(char *redirect_uri) 
{
    char url[BUFFER_SIZE] = {'\0'};
    snprintf(url, BUFFER_SIZE, "%s&fun=new", redirect_uri);
#ifdef DEBUG
    printf("DEBUG: %s\n", url);
#endif
    if (my_curl_init(url, 0) != 0) 
        return -1;
    char *content = my_curl_get_content();
    /*
     * [1]: .qq.com TRUE    /   FALSE   1393467796  wxuin   1225436020
     * [2]: .qq.com TRUE    /   FALSE   1393467796  wxsid   AOXWIgn5TjaSqAOZ
     * [3]: .qq.com TRUE    /   FALSE   1393467796  wxloadtime  1393381396
     * [4]: .qq.com TRUE    /   FALSE   1393467796  mm_lang zh_CN
     *
     */
    m_cookies = my_curl_get_cookies();
    
    my_curl_cleanup();
    if (content == NULL) 
        return -1;
    if (strstr(content, "OK")) {
        free(content);
        content = NULL;
        return 0;
    }

    return -1;
}

void webwx_post_statreport(int timestamp) 
{
    char url[BUFFER_SIZE] = {'\0'};
    snprintf(url, BUFFER_SIZE, 
        "https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxstatreport?type=1&r=%d", 
        timestamp);
#ifdef DEBUG
    printf("DEBUG: %s\n", url);
#endif
    if (my_curl_init(url, 0) != 0) 
        return;
    my_curl_set_cookies(m_cookies);
    char *content = my_curl_get_content();
    my_curl_cleanup();
    if (content) {
        free(content);
        content = NULL;
    }
}

void webwx_post_init(int timestamp) 
{
    char url[BUFFER_SIZE] = {'\0'};
    snprintf(url, BUFFER_SIZE, 
        "https://wx.qq.com/cgi-bin/mmwebwx-bin/webwxinit?r=%d", timestamp);
#ifdef DEBUG
    printf("DEBUG: %s\n", url);
#endif
    if (my_curl_init(url, 0) != 0) 
        return;
    my_curl_set_cookies(m_cookies);
    char *content = my_curl_get_content();
    my_curl_cleanup();
    if (content == NULL) 
        return;
#ifdef DEBUG
    printf("DEBUG: %s\n", content);
#endif
    free(content);
    content = NULL;
}

void webwx_get_avatar(char *username) 
{
    char url[BUFFER_SIZE] = {'\0'};
    snprintf(url, BUFFER_SIZE, "https://wx.qq.com/cgi-bin/mmwebwx-bin/"
        "webwxgeticon?username=%s", username);
    if (my_curl_init(url, 0) != 0) 
        return;
    char *content = my_curl_get_content();
    my_curl_cleanup();
    if (content == NULL) 
        return;
#ifdef DEBUG
    printf("DEBUG: %s\n", content);
#endif
    free(content);
    content = NULL;
}

void webwx_cleanup() 
{
    if (m_cookies) {
        curl_slist_free_all(m_cookies);
        m_cookies = NULL;
    }
}
