//
//  StringFunctions.cpp
//  UOX
//
//  Created by Charles Kerr on 4/21/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

#include <algorithm>
#include <cctype>
#include <locale>

#include "StringFunctions.hpp"

// Remove comment
void remcomment(std::string &s) {
    try {
        s.erase(s.begin()+s.find_first_of("//"),s.end());
    }
    catch(...){
        // Ok, so we dont want to do anything
    }
    

}


// trim from start (in place)
void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

// Find a section
std::tuple<std::string,std::string> section(std::string& value) {
    auto start = value.find_last_of("{");
    auto end = value.find_first_of("}",start);
    std::string sec = value.substr(start,end-start);
    value.erase(start,end-start);
    return {value,sec};
}
std::tuple<std::string,std::string> sectionname(std::string& value) {
    auto start = value.find_first_of(":") ;
    auto name = value.substr(0,start);
    trim(name);
    value.erase(0,start+1);
    return {name, value};
}
