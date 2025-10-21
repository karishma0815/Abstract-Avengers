/*Abstract Avengers*/

/**
 * @file ItemDecorator.cpp
 * @brief Implementation of ItemDecorator.
 */

#include "ItemDecorator.h"

// Base decorator keeps ownership of the wrapped component.
// Concrete decorators customize price/describe/clone.
ItemDecorator::ItemDecorator(std::unique_ptr<Item> inner) : wrapped(std::move(inner)) 
{}

double ItemDecorator::price() const 
{ 
    return wrapped->price(); 
}

std::string ItemDecorator::describe() const 
{ 
    return wrapped->describe(); 
}

bool ItemDecorator::readyForSale() const 
{ 
    return wrapped->readyForSale(); 
}

const Item& ItemDecorator::wrappedFunc() const 
{ 
    return *wrapped;
}
