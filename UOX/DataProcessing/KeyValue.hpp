//
//  KeyValue.hpp
//  UOX
//
//  Created by Charles Kerr on 4/22/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

#ifndef KeyValue_hpp
#define KeyValue_hpp

#include <string>
#include <cstring>
#include <vector>



class KeyValue {
public:
    KeyValue() ;
    KeyValue(const std::string& value) ;
    std::size_t argcount() const ;
    std::string valueFor(int index) ;
    std::string listvalues() ;
    
private:
    std::vector<std::string> values;
    
private:
    void loadValues(const std::string& value) ;
    std::string parseString(std::string& value);
    std::vector<std::string> argsFor(std::string value);
};

#endif /* KeyValue_hpp */
