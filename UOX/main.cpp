//
//  main.cpp
//  UOX
//
//  Created by Charles Kerr on 4/21/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//
// System headers
#include <iostream>
#include <cstdlib>
#include <fstream>

// Third party

// Our includes
#include "ConfFile.hpp"
#include "StringFunctions.hpp"

int main(int argc, const char * argv[]) {
    // Make sure we got passed our configuration
    if (argc < 2) {
        std::cout <<"Program must be started with a configuration file"<<std::endl;
        exit(EXIT_FAILURE);
    }
    std::string configpath(argv[1]) ;
    std::ifstream configstream;
    ConfFile config ;
    config.loadFile(configpath);
    
    
    
    
    return 0;
}
