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
#include <sys/types.h>
#include <regex.h>

#include "http_get.h"

namespace webwx 
{

std::string get_uuid() 
{
    std::string uuid = "";
    std::string content = http_get("https://login.weixin.qq.com/jslogin?appid="
        "wx782c26e4c19acffb&redirect_uri=https://wx.qq.com/cgi-bin/mmwebwx-bin"
        "/webwxnewloginpage&fun=new&lang=zh_CN&_=" + std::to_string(time(NULL)));
    std::cout << "DEBUG: " << content << std::endl;
    
    regex_t regex;
    regmatch_t pmatch[1];
    if (regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED) != 0) 
        return uuid;
    if (regexec(&regex, content.c_str(), 1, pmatch, 0) == 0) {
        std::cout << "DEBUG: rm_so, rm_eo = " << pmatch[0].rm_so << ", " << pmatch[0].rm_eo << std::endl;
        uuid = content.substr(pmatch[0].rm_so + 1, pmatch[0].rm_eo - pmatch[0].rm_so - 2);
    }
    regfree(&regex);
    return uuid;
}

}
