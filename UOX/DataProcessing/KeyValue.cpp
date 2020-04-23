//
//  KeyValue.cpp
//  UOX
//
//  Created by Charles Kerr on 4/22/20.
//  Copyright © 2020 Charles Kerr. All rights reserved.
//

// System includes
#include <exception>
#include <sstream>
#include <iostream>

#include "KeyValue.hpp"
#include "StringFunctions.hpp"

// =========================== Constructors ========================

//++++++++++++++++++++++++++++++++++++++
KeyValue::KeyValue() {
    values.clear();
}
//++++++++++++++++++++++++++++++++++++++
KeyValue::KeyValue(const std::string& value) : KeyValue() {
    loadValues(value);
}

//===========================  Support methods
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::size_t KeyValue::argcount() const  {
    return values.size();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::string KeyValue::valueFor(int index){
    if (index < values.size()) {
        return values[index];
    }
    return std::string();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void KeyValue::loadValues(const std::string& value){
    values.clear() ;
    auto temp = value;
    values = argsFor(temp);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::vector<std::string> KeyValue::argsFor(std::string value) {
    std::vector<std::string> values;
    while (true) {
        try {
            auto rvalue = parseString(value);
            //trim(rvalue);
            values.push_back(rvalue);
        }
        catch(...){
            // there wasn't a separator
            trim(value);
            if (value.size() > 0) {
                values.push_back(value);
                break;
            }
        }
    }
    return values;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::string KeyValue::parseString(std::string &value) {
    
    std::string::iterator iter = value.begin();
    bool ignore = false;
    std::string rvalue ;
    while (iter != value.end() ) {
        if (*iter == '"'){
            ignore = !ignore;
        }
        else if ((*iter == ',') && (!ignore)) {
            
            // We found a separator!
            // What if the separator is at the beginning, is that an issue?
            if (iter == value.begin()) {
                rvalue  = std::string();
            }
            else {
                // WE subtract the one off the iter, for we dont what the ","
                rvalue = std::string(value.begin(),iter-1);
                trim(rvalue);
            }
            value.erase(value.begin(), iter +1 );
            break;
        }
        iter++;
    }
    //std::cout << "Keyvalue checking iter against value.end" << std::endl;
    if (iter == value.end()) {
        // we never found a divider
        throw std::runtime_error("No separator found");
    }
    return rvalue;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
std::string KeyValue::listvalues() {
    std::stringstream rvalue;
    std::vector<std::string>::iterator iter = values.begin() ;
    while (iter != values.end()) {
        rvalue << *iter ;
        iter++ ;
        if (iter != values.end()){
            rvalue <<",";
        }
    }
    return rvalue.str();
}
