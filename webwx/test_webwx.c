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

#include "webwx.h"

static void m_uuid_callback(char *uuid);

static void m_uuid_callback(char *uuid) 
{
    printf("DEBUG: %s %s\n", __func__, uuid);
}

int main(int argc, char *argv[]) 
{
    char uuid[BUFFER_SIZE] = {'\0'};
    char redirect_uri[BUFFER_SIZE] = {'\0'};
    if (webwx_get_uuid(uuid, &m_uuid_callback) == NULL) {
        printf("ERROR: fail to get uuid!\n");
        return -1;
    }
    printf("获取uuid: %s\n", uuid);
    
    printf("获取二维码 https://login.weixin.qq.com/qrcode/%s?t=webwx\n", uuid);
    
    while (1) {
        if (webwx_wait_scan(uuid, (int)time(NULL), 6, redirect_uri))  
            break;
        printf("等待扫描二维码...\n");
    }

    printf("登陆获取Cookie %s\n", redirect_uri);
    webwx_get_cookie(redirect_uri);

    webwx_post_statreport((int)time(NULL));
    
    webwx_post_init((int)time(NULL));

    webwx_get_avatar("sirtoozee");

    return 0;
}
