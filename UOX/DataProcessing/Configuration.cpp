//
//  Configuration.cpp
//  UOX
//
//  Created by Charles Kerr on 4/21/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//



#include "Configuration.hpp"

Configuration::Configuration(const std::string& filepath): Configuration(){
    
}

Configuration::Configuration() {
    
}

bool Configuration::load(const std::string &filepath){
    this->filepath = filepath;
    return true;
}
