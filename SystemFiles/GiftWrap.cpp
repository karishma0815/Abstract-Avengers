/*Abstract Avengers*/

/**
 * @file GiftWrap.cpp
 * @brief Implementation of GiftWrap.
 */

#include "GiftWrap.h"
#include <utility>

GiftWrap::GiftWrap(std::unique_ptr<Item> dec, std::string message, double extra)
  : ItemDecorator(std::move(dec)), message(std::move(message)), extra(extra) 
  {}

double GiftWrap::price() const 
{ 
    return wrapped->price() + extra; 
}

// Include the message in the description for receipts / previews.
std::string GiftWrap::describe() const 
{
  return wrapped->describe() + " + Wrap(\"" + message + "\")";
}

// Wrap doesn't change readiness to sell.
bool GiftWrap::readyForSale() const 
{ 
    return wrapped->readyForSale(); 
}

// Deep clone the chain and re-attach wrap with same text/price.
std::unique_ptr<Item> GiftWrap::clone() const 
{
  return std::unique_ptr<Item>(new GiftWrap(wrapped->clone(), message, extra));
}

// Accessors 
const std::string& GiftWrap::messageFunc() const 
{ 
    return message; 
}

double GiftWrap::extraFunc() const 
{ 
    return extra; 
}