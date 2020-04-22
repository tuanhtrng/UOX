//
//  ConfFile.cpp
//  UOX
//
//  Created by Charles Kerr on 4/21/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <exception>
#include <cstring>
#include <regex>
#include <vector>


#include "StringFunctions.hpp"

#include "ConfFile.hpp"






ConfFile::ConfFile() {
    
}
//=====================================================
void ConfFile::loadFile(const std::string &filepath){
    std::ifstream file ;
    file.open(filepath) ;
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Error opening: ")+filepath);
    }
    
    std::string temp;
    data.str("");
    auto buffersize = 4096;
    char buffer[buffersize];
    while (!file.eof()) {
        std::memset(buffer, 0, buffersize);
        file.getline(buffer,buffersize);
        std::string line(buffer);
        remcomment(line);
        trim(line);
        if (line.size() > 0) {
            data << line << "\n" ;
        }
    }
    
    auto rvalue = sections(data.str());
    //std::cout << "Found " << std::get<1>(rvalue).size() <<" sections"<<std::endl;
    for (std::size_t i=0;i<std::get<1>(rvalue).size();i++) {
        std::cout <<"SECTION" <<std::endl;
        std::cout << std::get<1>(rvalue)[i] << std::endl;
    }
    
}
//====================================================================
ConfFile::secaddr ConfFile::findSection(const std::string& value) {
    struct secaddr section;
    section.start = value.find_first_of("{") ;
    int depth = 0;
    
    if (section.start != std::string::npos) {
        std::string::const_iterator iter = value.begin() + section.start + 1 ;
        auto count = section.start + 1;
        while (iter != value.end()) {
            if (*iter == '{') {
                depth = depth + 1;
            }
            else if (*iter == '}'){
                // check our depth
                if (depth > 0) {
                    depth = depth -1;
                }
                else {
                    // We found it!
                    
                    section.end = count ;
                    break;
                }
                
            }
            count = count + 1;
            iter++;
        }
        // Now for some checks to ensure we just didn't run off
        if (depth != 0) {
            
            throw std::runtime_error("Section mismatch");
        }
        if (section.end == value.size()) {
            if (value[section.end-1] != '}') {
                
                throw std::runtime_error("Section mismatch");
            }
        }
        if (section.end == std::string::npos) {
            
            throw std::runtime_error("Section mismatch");
        }
    }
    
    return section;
}

//===============================================================
std::tuple<std::string,std::vector<std::string>> ConfFile::sections(std::string value) {
    std::vector<std::string> section;
    
    auto addr = findSection(value) ;
    
    while (addr.valid()) {
        
        // We found at least one section!
        auto sec = value.substr(addr.start+1,(addr.end - addr.start)-2 ) ;
        
        
        section.push_back(sec);
        value.erase(addr.start,addr.end - addr.start);
        addr = findSection(value);
    }
    return {value,section} ;
}
