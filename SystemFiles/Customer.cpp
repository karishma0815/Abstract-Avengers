 /*Abstract Avengers*/

/**
 * @file Customer.cpp
 * @brief Implementation of Customer.
 */

#include "Customer.h"

Customer::Customer(std::string name) : name(name) {
    cart = new PlantInventory();
}

Customer::~Customer() {
    delete cart;
}

const std::string& Customer::nameFunc() const 
{ 
    return name; 
}

void Customer::setName(std::string n) 
{ 
    name = n; 
}

PlantInventory* Customer::getCart() {
    return cart;
}