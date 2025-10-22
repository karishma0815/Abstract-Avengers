 /*Abstract Avengers*/

/**
 * @file SalesContext.cpp
 * @brief Implementation of SalesContext.
 */

#include "SalesContext.h"

SalesContext::SalesContext(State& start, Customer& customer)
: state(&start), customer(&customer) 
{
  state->enterState(*this->customer, *this);
}

void SalesContext::setState(State& next) 
{
  state = &next;
  state->enterState(*customer, *this);
}

void SalesContext::notify(const std::string& msg) 
{
  std::cout << "[SalesContext] " << msg << "\n";
}

bool SalesContext::hasStock(const std::string& sku, int qty) const 
{
  auto it = stock.find(sku);
  return it != stock.end() && it->second >= qty;
}

bool SalesContext::reserveStock(const std::string& sku, int qty) 
{
  auto it = stock.find(sku);
  if (it == stock.end() || it->second < qty) return false;
  it->second -= qty;
  return true;
}

void SalesContext::releaseStock(const std::string& sku, int qty) 
{
  stock[sku] += qty;
}

void SalesContext::clearOrder() 
{
  authorized = false;
}

bool SalesContext::authorizePayment() 
{
  //authorized = true;
  //return true;
  #ifdef SUPPORT_TEST_TOGGLES
  if (testAuthArmed) {
    authorized  = testAuthNext;
    testAuthArmed = false;      
    return authorized;
  }
#endif
  authorized = true;             //default path (success)
  return true;
}

bool SalesContext::capturePayment() 
{
  #ifdef SUPPORT_TEST_TOGGLES
  if (testCaptureArmed) 
  {
    bool ok = testCaptureNext;
    testCaptureArmed = false;    
    return ok && authorized;
  }
#endif
  return authorized;             //default: succeed only if previously authorized

}

void SalesContext::putStock(const std::string& sku, int qty) 
{
  stock[sku] += qty;
}

int SalesContext::stockOf(const std::string& sku) const 
{
  auto it = stock.find(sku);
  return it == stock.end() ? 0 : it->second;
}

State& SalesContext::current() const 
{ 
    return *state; 
}

Customer& SalesContext::customerFunc() const 
{ 
    return *customer; 
}

void SalesContext::eventSelect(const std::string& sku, int qty) 
{ 
    state->onSelect(sku, qty); 
}

void SalesContext::eventAssist()                                
{ 
    state->onAssist(); 
}

void SalesContext::eventAssistComplete()                        
{ 
    state->onAssistComplete(); 
}

void SalesContext::eventReplenished()                           
{ 
    state->onReplenished(); 
}

void SalesContext::eventCheckout()                              
{ 
    state->onCheckout(); 
}

void SalesContext::eventAuthorize()                             
{ 
    state->onAuthorize(); 
}

void SalesContext::eventCommit()                                
{ 
    state->onCommit(); 
}

void SalesContext::eventRetry()                                 
{ 
    state->onRetry(); 
}

void SalesContext::eventCancel()                                
{ 
    state->onCancel(); 
}