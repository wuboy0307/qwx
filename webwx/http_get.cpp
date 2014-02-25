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

#include <iostream>
#include <curl/curl.h>
#include "http_get.h"

namespace webwx 
{

size_t chunk::handle(char* data, size_t size, size_t nmemb, void* p)
{
    return static_cast<chunk*>(p)->m_handle_impl(data, size, nmemb);
}

size_t chunk::m_handle_impl(char* data, size_t size, size_t nmemb)
{
    m_content.append(data, size * nmemb);
    return size * nmemb;
}

std::string chunk::get_content() 
{
    return m_content;
}

std::string http_get(std::string url) 
{
    CURL* curl = NULL;
    CURLcode res;
    chunk c;
 
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) 
        return "";

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &c);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &chunk::handle);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cout << curl_easy_strerror(res) << std::endl;
        return "";
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return c.get_content();
}

}
