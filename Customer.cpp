 /*Abstract Avengers*/

/**
 * @file Customer.cpp
 * @brief Implementation of Customer.
 */

#include "Customer.h"

explicit Customer::Customer(std::string name = "Guest") : name(name) 
{}

const std::string& Customer::nameFunc() const 
{ 
    return name; 
}

void Customer::setName(std::string n) 
{ 
    name = n; 
}