//
//  ConfSection.hpp
//  UOX
//
//  Created by Charles Kerr on 4/22/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

#ifndef ConfSection_hpp
#define ConfSection_hpp

#include <map>
#include <string>
#include <tuple>

#include "KeyValue.hpp"
#include "ConfFile.hpp"

class ConfSection {
public:
    ConfSection() ;
    ConfSection(const std::string& secstring);
    virtual ~ConfSection() ;
    std::string key();
    
private:
    std::map<std::string,ConfSection> subsections;
    std::map<std::string, KeyValue> values;
    std::string name;
    
private:
    
    void loadsection(std::string& secstring);
    std::string getname(std::string& secstring);
    static std::map<std::string,KeyValue> parsevalues(std::string& secstring);
    static std::tuple<std::string,KeyValue> parseline(const std::string& line);
    friend class ConfFile;
};

#endif /* ConfSection_hpp */
