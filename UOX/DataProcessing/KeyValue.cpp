//
//  KeyValue.cpp
//  UOX
//
//  Created by Charles Kerr on 4/22/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

// System includes
#include <exception>

#include "KeyValue.hpp"
#include "StringFunctions.hpp"

// =========================== Constructors ========================
KeyValue::KeyValue() {
    
}
KeyValue::KeyValue(const std::string& value) {
    
}
//===========================  Support methods
std::size_t KeyValue::argcount() const  {
    return values.size();
}
std::string KeyValue::valueFor(int index){
    if (index < values.size()) {
        return values[index];
    }
    return std::string();
}

void KeyValue::loadValues(const std::string& value){
    values.clear() ;
    auto temp = value;
    std::string::iterator iter = temp.begin();
}

std::string KeyValue::parseString(std::string &value) {
    std::string::iterator iter = value.begin();
    bool ignore = false;
    std::string rvalue ;
    while (iter != value.end() ) {
        if (*iter == '"'){
            ignore = !ignore;
        }
        else if ((*iter == ',') && (!ignore)) {
            // We found a seperator!
            rvalue = std::string(value.begin(),iter-1);
            trim(rvalue);
            value.erase(value.begin(), iter);
            break;
        }
        iter++;
    }
    if (iter == value.end()) {
        // we never found a divider
        throw std::runtime_error("No seperator found");
    }
    return rvalue;

}
