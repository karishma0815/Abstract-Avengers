/*Abstract Avengers*/

/**
 * @file CartOpenState.cpp
 * @brief Implementation of CartOpenState.
 */

#include "CartOpenState.h"
#include "PendingPaymentState.h"
#include "CancelledState.h"
#include "SalesContext.h"
#include "SeekingAssistanceState.h"

CartOpenState& CartOpenState::instance() 
{
  static CartOpenState s; 
  return s;
}

std::string CartOpenState::getStateName() const 
{ 
    return "CartOpen"; 
}

void CartOpenState::enterState(Customer& customer, SalesContext& ctx) 
{
  State::enterState(customer, ctx);
  ctx.notify("Cart is open. Add/remove items or checkout.");
}

void CartOpenState::onCheckout() 
{
  ctxFunc().notify("Proceeding to payment...");
  ctxFunc().setState(PendingPaymentState::instance());
}

void CartOpenState::onCancel() 
{
  ctxFunc().notify("Order cancelled.");
  ctxFunc().setState(CancelledState::instance());
}

void CartOpenState::onAssist() 
{
  ctxFunc().notify("Connecting you to staff for assistance...");
  ctxFunc().setState(SeekingAssistanceState::instance());
}