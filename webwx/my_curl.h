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

#ifndef MY_CURL_H
#define MY_CURL_H

#ifdef __cplusplus
extern "C" {
#endif

#define BUFFER_SIZE 1024

int my_curl_init(char *url, int timeout);
char *my_curl_get_content();
void my_curl_cleanup();
void my_curl_print_cookies();

#ifdef __cplusplus
}
#endif

#endif /* MY_CURL_H */
