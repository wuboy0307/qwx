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

typedef void (*UUID_CALLBACK)(char *);

char *webwx_get_uuid(char *uuid, UUID_CALLBACK fptr);
char *webwx_wait_scan(char *uuid, int timestamp, int timeout, char *redirect_uri);
int webwx_get_cookie(char *redirect_uri);
void webwx_post_statreport(int timestamp);
void webwx_post_init(int timestamp);
void webwx_get_avatar(char *username);
void webwx_cleanup();

#ifdef __cplusplus
}
#endif

#endif /* WEBWX_H */
