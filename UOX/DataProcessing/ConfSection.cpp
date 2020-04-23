//
//  ConfSection.cpp
//  UOX
//
//  Created by Charles Kerr on 4/22/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

// System Includes
#include <sstream>
#include <cstring>
#include <exception>
#include <iostream>

#include "ConfFile.hpp"
#include "ConfSection.hpp"
#include "StringFunctions.hpp"

//======================= Constructor/Destructor ================
//++++++++++++++++++++++++++++++++++++
ConfSection::~ConfSection(){
    subsections.clear();
    values.clear();
}
//+++++++++++++++++++++++++++++++++++++
ConfSection::ConfSection() {
    subsections.clear();
    values.clear();
}

//+++++++++++++++++++++++++++++++++++++
ConfSection::ConfSection(const std::string& secstring):ConfSection() {
    auto temp = secstring;
    loadsection(temp);
}

//====================== Support Methods =========================
//+++++++++++++++++++++++++++++++++++++
void ConfSection::loadsection(std::string &secstring){
    
    auto rvalue = ConfFile::sections(secstring);
    std::vector<std::string>::iterator iter = std::get<1>(rvalue).begin();
    while (iter != std::get<1>(rvalue).end() ) {
        try {
            ConfSection section(*iter) ;
            subsections.insert(std::make_pair(section.key(), section));
            iter++;
        }
        catch(...) {
            break;
        }
    }
    auto remaining = std::get<0>(rvalue) ;
    name = getname(remaining) ;
    values = parsevalues(remaining);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::string ConfSection::key() {
    return name;
}
//++++++++++++++++++++++++++++++++++++++
std::string ConfSection::getname(std::string &secstring){
    std::string rvalue ;
    auto loc = secstring.find_first_of(":") ;
    if ((loc == std::string::npos) || (loc == 0)) {
        throw std::runtime_error("Section has no name");
    }
    else {
        rvalue = secstring.substr(0,loc);
        trim(rvalue) ;
        if (rvalue.size() == 0) {
            throw std::runtime_error("Section has no name");
        }
        secstring.erase(0,loc);
    }
    return rvalue;
}

//+++++++++++++++++++++++++++++++++++++++++
std::map<std::string,KeyValue> ConfSection::parsevalues(std::string& secstring){
    // we look for =
    std::stringstream input ;
    
    input.str(secstring);
    const int buffersize = 4096;
    char buffer[buffersize];
    std::map<std::string,KeyValue> values;
    std::string line;
    bool concat = false;
    while (!input.eof()) {
        
        line = std::string();
        do {
            
            std::memset(buffer, 0, buffersize);
            input.getline(buffer,buffersize) ;
            auto readin = input.gcount() ;
            
            if (readin == buffersize) {
                
                if (concat) {
                    line = line + std::string(buffer);
                }
                else {
                    line = std::string(buffer);
                }
                concat = true;
            }
            else {
                if (concat) {
                    line = line + std::string(buffer);
                }
                else {
                    line = std::string(buffer);
                }
                concat = false;

            }
            
        } while ((concat == true) && (!input.eof()));
        
        trim(line);
        
        if (line.size() > 0) {
            
            auto rvalue = parseline(line);
            values.insert(std::make_pair(std::get<0>(rvalue), std::get<1>(rvalue)));
        }
        
    }
    
    return values;
}
//+++++++++++++++++++++++++++++++++++++++++
std::tuple<std::string,KeyValue> ConfSection::parseline(const std::string &line) {
    auto loc = line.find_first_of("=") ;
    if (loc == std::string::npos) {
        // So this is a name only!
        std::string key = trim_copy(line);
        return { key,KeyValue()};
    }
    else {
        
        std::string key = line.substr(0,loc) ;
        loc = loc + 1 ; // move past the =
        KeyValue value; ;
        
        if (loc < line.size() ) {
            
            std::string temp = line.substr(loc) ;
            
            trim(temp);
            
            if (temp.size() > 0) {
                
                value = KeyValue(temp);
                
            }
            
        }
        
        return {key,value};
    }
    
    
}