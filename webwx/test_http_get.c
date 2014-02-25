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
#include <stdlib.h>

#include "http_get.h"

#if WIN32
#pragma comment(lib, "curllib.lib") 
#endif

int main(int argc, char *argv[]) 
{
    char url[BUFFER_SIZE] = {'\0'};
    char *content = NULL;
    snprintf(url, BUFFER_SIZE, "https://login.weixin.qq.com/jslogin?appid="
        "wx782c26e4c19acffb&redirect_uri=https://wx.qq.com/cgi-bin/mmwebwx-bin/"
        "webwxnewloginpage&fun=new&lang=zh_CN&_=%d", (int)time(NULL));
    content = http_get(url);
    printf("%s\n", content ? content : "NULL");
    if (content) {
        free(content);
        content = NULL;
    }

#if WIN32
    system("pause");
#endif

    return 0;
}
