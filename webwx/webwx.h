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

#ifndef WEBWX_H
#define WEBWX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "my_curl.h"

#define DEBUG 1

typedef void (*UUID_CALLBACK)(char *);

char *get_uuid(char *uuid, UUID_CALLBACK fptr);
char *wait_scan(char *uuid, int timestamp, int timeout, char *redirect_uri);
int get_cookie(char *redirect_uri);
void get_init(int timestamp);
void get_avatar(char *username);

#ifdef __cplusplus
}
#endif

#endif /* WEBWX_H */
