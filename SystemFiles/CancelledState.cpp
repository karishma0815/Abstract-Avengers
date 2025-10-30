/*Abstract Avengers*/

/**
 * @file CancelledState.cpp
 * @brief Implementation of CancelledState.
 */

#include "CancelledState.h"
#include "SalesContext.h"

CancelledState& CancelledState::instance() 
{
  static CancelledState s; 
  return s;
}

std::string CancelledState::getStateName() const 
{ 
    return "Cancelled"; 
}

void CancelledState::enterState(Customer& customer, SalesContext& ctx) 
{
  State::enterState(customer, ctx);
  ctx.notify("Order cancelled.");
  ctx.clearOrder();
}

void CancelledState::onEnter()
{}