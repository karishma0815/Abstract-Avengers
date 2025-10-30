/*Abstract Avengers*/

/**
 * @file PlantItem.cpp
 * @brief Implementation of PlantItem.
 */

#include "PlantItem.h"

#include <utility>

PlantItem::PlantItem(std::string name, double basePrice, bool readyForSale)
  : name(std::move(name)), basePrice(basePrice), ready(readyForSale) 
  {}

double PlantItem::price() const 
{ 
    return basePrice; 
}

std::string PlantItem::describe() const 
{ 
    return "Plant(" + name + ")"; 
}

bool PlantItem::readyForSale() const 
{ 
    return ready; 
}

std::unique_ptr<Item> PlantItem::clone() const 
{
  return std::unique_ptr<Item>(new PlantItem(*this));
}

const std::string& PlantItem::nameFunc() const 
{ 
    return name; 
}

double PlantItem::basePriceFunc() const 
{ 
    return basePrice; 
}
