/*Abstract Avengers*/

/**
 * @file PaymentFailedState.cpp
 * @brief Implementation of PaymentFailedState.
 */

#include "PaymentFailedState.h"
#include "PendingPaymentState.h"
#include "CancelledState.h"
#include "SalesContext.h"

PaymentFailedState& PaymentFailedState::instance() 
{
  static PaymentFailedState s; 
  return s;
}

std::string PaymentFailedState::getStateName() const 
{ 
    return "PaymentFailed"; 
}

void PaymentFailedState::onRetry() 
{
  ctxFunc().notify("Retrying payment...");
  ctxFunc().setState(PendingPaymentState::instance());
}

void PaymentFailedState::onCancel() 
{
  ctxFunc().notify("Order cancelled after payment failure.");
  ctxFunc().setState(CancelledState::instance());
}

void PaymentFailedState::onEnter()
{}