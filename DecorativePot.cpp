/*Abstract Avengers*/

/**
 * @file DecorativePot.cpp
 * @brief Implementation of DecorativePot.
 */

#include "DecorativePot.h"
#include <utility>

// Pot adds color and a small surcharge (extra_).
DecorativePot::DecorativePot(std::unique_ptr<Item> dec, std::string color, double extra)
  : ItemDecorator(std::move(dec)), color(std::move(color)), extra(extra) 
{}

// Price is additive: base chain + pot surcharge.
double DecorativePot::price() const 
{ 
    return wrapped->price() + extra; 
}

std::string DecorativePot::describe() const 
{
  return wrapped->describe() + " + Pot(" + color + ")";
}

// Pot doesn't affect sellability; pass-through.
bool DecorativePot::readyForSale() const 
{ 
    return wrapped->readyForSale(); 
}

// Deep clone the wrapped chain and re-apply the same pot.
std::unique_ptr<Item> DecorativePot::clone() const 
{
  return std::unique_ptr<Item>(new DecorativePot(wrapped->clone(), color, extra));
}

// Accessors 
const std::string& DecorativePot::colorFunc() const 
{ 
    return color; 
}

double DecorativePot::extraFunc() const 
{ 
  return extra; 
}
