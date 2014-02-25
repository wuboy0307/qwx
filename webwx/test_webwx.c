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

#include "webwx.h"

int main(int argc, char *argv[]) 
{
    char uuid[BUFFER_SIZE] = {'\0'};
    if (get_uuid(uuid) == NULL) {
        printf("ERROR: fail to get uuid!\n");
        return -1;
    }
    printf("获取uuid: %s\n", uuid);
    printf("获取二维码 https://login.weixin.qq.com/qrcode/%s?t=webwx\n", uuid);

#if WIN32
    system("pause");
#endif

    return 0;
}
