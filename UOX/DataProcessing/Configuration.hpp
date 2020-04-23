//
//  Configuration.hpp
//  UOX
//
//  Created by Charles Kerr on 4/21/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

#ifndef Configuration_hpp
#define Configuration_hpp

#include <fstream>
#include <string>

// Third party

class Configuration {
public:
    // Some structure defines available to all
    struct shard {
        std::string name;
        std::string ipaddress;
        int port;
    };
    struct directory {
        std::string uodata;
        std::string account;
        std::string world;
        std::string script;
        std::string defintion;
    };
    struct system {
        std::string log;
        
    };

public:
    Configuration(const std::string& filepath);
    Configuration();
    virtual ~Configuration() = default;
    bool load(const std::string& filepath);
    
    
private:
    std::string filepath;
    
};

#endif /* Configuration_hpp */
