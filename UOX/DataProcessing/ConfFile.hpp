//
//  ConfFile.hpp
//  UOX
//
//  Created by Charles Kerr on 4/21/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

#ifndef ConfFile_hpp
#define ConfFile_hpp

#include <string>
#include <sstream>
#include <map>
#include <vector>


// Local includes
#include "KeyValue.hpp"
#include "ConfSection.hpp"

class ConfFile {
private:
    struct secaddr {
        secaddr() {
            start = std::string::npos;
            end = std::string::npos;
        }
        secaddr(std::size_t start, std::size_t end) {
            this->start = start ;
            this->end = end ;
        }
        std::size_t start ;
        std::size_t end;
        bool contains(const secaddr& value) {
            if ((value.start > this->start) && (value.end < this->end)) {
                return true;
            }
            return false;
        };
        bool valid() const {
            return (start != std::string::npos) && (end != std::string::npos);
        }
    };
    
    std::multimap<std::string,KeyValue> values ;
    std::map<std::string,ConfSection> secvalues;

public:
    ConfFile();
    ~ConfFile() = default;
    
    void loadFile(const std::string& filepath);
    std::vector<KeyValue> valueFor(const std::string& keypath) ;
private:
    std::string prepdata(const std::string& filepath);
    static secaddr findSection(const std::string& value);
    static std::tuple<std::string,std::vector<std::string>> sections(std::string& value);
    
    friend class ConfSection;
};


#endif /* ConfFile_hpp */
