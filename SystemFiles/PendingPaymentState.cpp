/*Abstract Avengers*/

/**
 * @file PendingPaymentState.cpp
 * @brief Implementation of PendingPaymentState.
 */

#include "PendingPaymentState.h"
#include "PaymentAuthorizedState.h"
#include "PaymentFailedState.h"
#include "CancelledState.h"
#include "SalesContext.h"

PendingPaymentState& PendingPaymentState::instance() 
{
  static PendingPaymentState s; 
  return s;
}

std::string PendingPaymentState::getStateName() const 
{ 
    return "PendingPayment"; 
}

void PendingPaymentState::onAuthorize() 
{
  if (ctxFunc().authorizePayment()) 
  {
    ctxFunc().notify("Payment authorized.");
    ctxFunc().setState(PaymentAuthorizedState::instance());
  } 
  else 
  {
    ctxFunc().notify("Payment authorization failed.");
    ctxFunc().setState(PaymentFailedState::instance());
  }
}

void PendingPaymentState::onCancel() 
{
  ctxFunc().notify("Order cancelled during payment.");
  ctxFunc().setState(CancelledState::instance());
}

void PendingPaymentState::onEnter()
{}