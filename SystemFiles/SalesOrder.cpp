 /*Abstract Avengers*/

/**
 * @file SalesOrder.cpp
 * @brief Implementation of SalesOrder.
 */

#include "SalesOrder.h"

SalesOrder::SalesOrder(State& start, Customer& customer)
: state(&start), customer(&customer) 
{
  state->enterState(*this->customer, *this);
}

void SalesOrder::setState(State& next) 
{
  state = &next;
  state->enterState(*customer, *this);
}

void SalesOrder::notify(const std::string& msg) 
{
  std::cout << "[SalesOrder] " << msg << "\n";
}

bool SalesOrder::hasStock(const std::string& sku, int qty) const 
{
  auto it = stock.find(sku);
  return it != stock.end() && it->second >= qty;
}

bool SalesOrder::reserveStock(const std::string& sku, int qty) 
{
  auto it = stock.find(sku);
  if (it == stock.end() || it->second < qty) return false;
  it->second -= qty;
  return true;
}

void SalesOrder::releaseStock(const std::string& sku, int qty) 
{
  stock[sku] += qty;
}

void SalesOrder::clearOrder() 
{
  authorized = false;
}

bool SalesOrder::authorizePayment() 
{
  authorized = true;
  return true;
}

bool SalesOrder::capturePayment() 
{
  return authorized;
}

void SalesOrder::putStock(const std::string& sku, int qty) 
{
  stock[sku] += qty;
}

int SalesOrder::stockOf(const std::string& sku) const 
{
  auto it = stock.find(sku);
  return it == stock.end() ? 0 : it->second;
}

State& SalesOrder::current() const 
{ 
    return *state; 
}

Customer& SalesOrder::customerFunc() const 
{ 
    return *customer; 
}

void SalesOrder::eventSelect(const std::string& sku, int qty) 
{ 
    state->onSelect(sku, qty); 
}

void SalesOrder::eventAssist()                                
{ 
    state->onAssist(); 
}

void SalesOrder::eventAssistComplete()                        
{ 
    state->onAssistComplete(); 
}

void SalesOrder::eventReplenished()                           
{ 
    state->onReplenished(); 
}

void SalesOrder::eventCheckout()                              
{ 
    state->onCheckout(); 
}

void SalesOrder::eventAuthorize()                             
{ 
    state->onAuthorize(); 
}

void SalesOrder::eventCommit()                                
{ 
    state->onCommit(); 
}

void SalesOrder::eventRetry()                                 
{ 
    state->onRetry(); 
}

void SalesOrder::eventCancel()                                
{ 
    state->onCancel(); 
}