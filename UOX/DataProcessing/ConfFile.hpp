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
    std::stringstream data;

public:
    ConfFile();
    ~ConfFile() = default;
    
    void loadFile(const std::string& filepath);

private:
    secaddr findSection(const std::string& value);
    std::tuple<std::string,std::vector<std::string>> sections(std::string value);
    
};


#endif /* ConfFile_hpp */
