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
#include <sys/types.h>
#include <regex.h>

#include "webwx.h"

char *get_uuid(char *uuid) 
{
    if (uuid == NULL) 
        return NULL;

    char url[BUFFER_SIZE] = {'\0'}; 
    snprintf(url, BUFFER_SIZE, "https://login.weixin.qq.com/jslogin?appid="          
        "wx782c26e4c19acffb&redirect_uri=https://wx.qq.com/cgi-bin/mmwebwx-bin" 
        "/webwxnewloginpage&fun=new&lang=zh_CN&_=%d", (int)time(NULL));
    char *content = http_get(url);
    if (content == NULL) 
        return NULL;

    regex_t regex;
    regmatch_t pmatch[1];
    if (regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED) != 0) 
        return NULL;
    if (regexec(&regex, content, 1, pmatch, 0) == 0) 
        strncpy(uuid, content + pmatch[0].rm_so + 1, pmatch[0].rm_eo - pmatch[0].rm_so - 2);
    regfree(&regex);
    return uuid;
}

int wait_scan(char *uuid, int timestamp) 
{
    int scaned = 0;

    return scaned;
}
