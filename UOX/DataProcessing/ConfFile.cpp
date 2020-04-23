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
#include <filesystem>


#include "StringFunctions.hpp"

#include "ConfFile.hpp"






ConfFile::ConfFile() {
    
}
//=====================================================
void ConfFile::loadDirectory(const std::string &path){
    for (auto &iter: std::filesystem::recursive_directory_iterator(path) ) {
        if (iter.is_directory()) {
            loadFile( iter.path());
        }
        
    }
    
}
//=====================================================
void ConfFile::loadFile(const std::string &filepath){
    
    std::string data = prepdata(filepath);
    
    auto rvalue = sections(data);
    
    for (std::size_t i=0;i<std::get<1>(rvalue).size();i++) {
        
        ConfSection sec(std::get<1>(rvalue)[i]) ;
        secvalues.insert(std::make_pair(sec.key(), sec));
    }
    // We need to the any values
    
    auto tempvalues = ConfSection::parsevalues(data);
    std::multimap<std::string, KeyValue>::iterator iter = tempvalues.begin();
    while (iter != tempvalues.end() ) {
        values.insert(*iter) ;
        iter++;
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Remove all the comments, and the spaces before/after lines.
// Add \n after each line, to perserve line endings, for later parsing
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::string ConfFile::prepdata(const std::string &filepath) {
    std::ifstream file ;
    file.open(filepath) ;
    if (!file.is_open()) {
        throw std::runtime_error(std::string("Error opening: ")+filepath);
    }
    
    std::string temp;
    std::stringstream data;
    const int buffersize = 4096;
    char buffer[buffersize];
    while (!file.eof()) {
        std::memset(buffer, 0, buffersize);
        file.getline(buffer,buffersize);
        std::string line(buffer);
        remcomment(line);
        trim(line);
        if (line.size() > 0) {
            // Check to see if their is a ending continuation mark
            if (line[line.size()-1] == '\\') {
                line.erase(line.size()-1,1);
                data << line <<" ";
            }
            else {
                data << line << "\n" ;
            }
            
        }
    }
    return data.str();
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
std::tuple<std::string,std::vector<std::string>> ConfFile::sections(std::string& value) {
    std::vector<std::string> section;
    
    auto addr = ConfFile::findSection(value) ;
    
    while (addr.valid()) {
        
        // We found at least one section!
        auto sec = value.substr(addr.start+1,(addr.end - addr.start) - 1 ) ;
        
        section.push_back(sec);
        value.erase(addr.start,(addr.end - addr.start) + 1);
        addr = ConfFile::findSection(value);
    }
    return {value,section} ;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::vector<KeyValue> ConfFile::valueFor(const std::string &keypath) {
    // NOTE:  THis is essentially duplicated in ConfFile as well
    // So changes here should be made there as well
    auto keys = keypath;
    auto key = ConfSection::parsekeys(keys) ;
    KeyValue rvalue ;
    std::vector<KeyValue> vrvalue;
    
    
    
    if (keys.size() == 0) {
        // it is a value lookup
        
        auto range = values.equal_range(key);

        if (range.first  == range.second) {
            throw std::runtime_error(std::string("Nonexisting key: ")+key);
        }
        // We know the key exists, and we should have the iterator to the first one
        for (auto itr = range.first; itr != range.second; ++itr) {
            vrvalue.push_back(itr->second);
        }
    }
    else {
        // Ok, is a section we have to get;
        try {
            //std::cout <<"Look for section: " << key<<std::endl;
            auto sec = secvalues.at(key) ;
            //std::cout << "looking for value (in section) for : " <<keys<<std::endl;
            vrvalue = sec.valueFor(keys);
            
        }
        catch(...) {
            throw;
        }
    }
    return vrvalue;
}

