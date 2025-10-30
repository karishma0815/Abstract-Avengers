/*Abstract Avengers*/

/**
 * @file PaymentAuthorizedState.cpp
 * @brief Implementation of PaymentAuthorizedState.
 */

#include "PaymentAuthorizedState.h"
#include "CompletedState.h"
#include "PendingPaymentState.h"
#include "CancelledState.h"
#include "SalesContext.h"

PaymentAuthorizedState& PaymentAuthorizedState::instance() 
{
  static PaymentAuthorizedState s; 
  return s;
}

std::string PaymentAuthorizedState::getStateName() const 
{ 
    return "PaymentAuthorized"; 
}

void PaymentAuthorizedState::onCommit() 
{
  if (ctxFunc().capturePayment()) 
  {
    ctxFunc().notify("Payment captured. Completing order.");
    ctxFunc().setState(CompletedState::instance());
  } 
  else 
  {
    ctxFunc().notify("Capture failed, returning to PendingPayment.");
    ctxFunc().setState(PendingPaymentState::instance());
  }
}

void PaymentAuthorizedState::onCancel() 
{
  ctxFunc().notify("Cancelled after authorization.");
  ctxFunc().setState(CancelledState::instance());
}

void PaymentAuthorizedState::onEnter()
{}