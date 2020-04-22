//
//  StringFunctions.hpp
//  UOX
//
//  Created by Charles Kerr on 4/21/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

#ifndef StringFunctions_hpp
#define StringFunctions_hpp
#include <string>
void remcomment(std::string &s);
void ltrim(std::string &s);
void rtrim(std::string &s);
void trim(std::string &s);
std::string ltrim_copy(std::string s);
std::string rtrim_copy(std::string s);
std::string trim_copy(std::string s);

std::tuple<std::string,std::string> section(const std::string& value);

#endif /* StringFunctions_hpp */
