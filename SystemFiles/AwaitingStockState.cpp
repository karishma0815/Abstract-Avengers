/*Abstract Avengers*/

/**
 * @file AwaitingStockState.cpp
 * @brief Implementation of AwaitingStockState.
 */

#include "AwaitingStockState.h"
#include "CartOpenState.h"
#include "CancelledState.h"
#include "SalesContext.h"

AwaitingStockState& AwaitingStockState::instance() 
{
  static AwaitingStockState s; 
  return s;
}

std::string AwaitingStockState::getStateName() const 
{ 
    return "AwaitingStock"; 
}

void AwaitingStockState::onReplenished() 
{
  ctxFunc().notify("Stock replenished. Moving to CartOpen.");
  ctxFunc().setState(CartOpenState::instance());
}

void AwaitingStockState::onCancel() 
{
  ctxFunc().notify("Order cancelled while awaiting stock.");
  ctxFunc().setState(CancelledState::instance());
}

void AwaitingStockState::onEnter()
{}