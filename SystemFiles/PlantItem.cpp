/*Abstract Avengers*/

/**
 * @file PlantItem.cpp
 * @brief Implementation of PlantItem.
 */

#include "PlantItem.h"
#include <utility>   
#include <memory>    

PlantItem::PlantItem(std::string name, double basePrice, bool ready)
: name_(std::move(name)), base_(basePrice), ready_(ready) {}

double PlantItem::priceFunc() const 
{ 
    return base_; 
}

std::string PlantItem::describe() const 
{ 
    return name_; 
}

bool PlantItem::readyForSale() const 
{ 
    return ready_; 
}

const std::string& PlantItem::name() const 
{ 
    return name_; 
}

void PlantItem::setReady(bool r) 
{ 
    ready_ = r; 
}