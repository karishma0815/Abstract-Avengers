/*Abstract Avengers*/

/**
 * @file CompletedState.cpp
 * @brief Implementation of CompletedState.
 */

#include "CompletedState.h"
#include "SalesContext.h"

CompletedState& CompletedState::instance() 
{
  static CompletedState s; 
  return s;
}

std::string CompletedState::getStateName() const 
{ 
    return "Completed"; 
}

void CompletedState::enterState(Customer& customer, SalesContext& ctx) 
{
  State::enterState(customer, ctx);
  ctx.notify("Order complete. Thank you!");
  ctx.clearOrder();
}