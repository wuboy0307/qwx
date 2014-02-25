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

#ifndef HTTP_GET_H
#define HTTP_GET_H

#include <string>

namespace webwx 
{

class chunk
{ 
public:
    static size_t handle(char* data, size_t size, size_t nmemb, void* p);
    std::string get_content();

private:
    std::string m_content;
    size_t m_handle_impl(char* data, size_t size, size_t nmemb);
};

std::string http_get(std::string url);

}

#endif /* HTTP_GET_H */
