/*Abstract Avengers*/

/**
 * @file SeekingAssistanceState.cpp
 * @brief Implementation of SeekingAssistanceState.
 */

#include "SeekingAssistanceState.h"
#include "BrowsingState.h"
#include "CartOpenState.h"
#include "AwaitingStockState.h"
#include "CancelledState.h"
#include "SalesContext.h"

SeekingAssistanceState& SeekingAssistanceState::instance() 
{
  static SeekingAssistanceState s; 
  return s;
}

std::string SeekingAssistanceState::getStateName() const 
{ 
    return "SeekingAssistance"; 
}

void SeekingAssistanceState::onAssistComplete() 
{
  ctxFunc().notify("Assistance complete. Returning to Browsing.");
  ctxFunc().setState(BrowsingState::instance());
}

void SeekingAssistanceState::onSelect(const std::string& sku, int qty) 
{
  if (ctxFunc().hasStock(sku, qty) && ctxFunc().reserveStock(sku, qty)) 
  {
    ctxFunc().notify("Item reserved; moving to CartOpen.");
    ctxFunc().setState(CartOpenState::instance());
  } 
  else 
  {
    ctxFunc().notify("Reservation failed or OOS; AwaitingStock.");
    ctxFunc().setState(AwaitingStockState::instance());
  }
}

void SeekingAssistanceState::onCancel() {
  ctxFunc().notify("Cancelled during assistance.");
  ctxFunc().setState(CancelledState::instance());
}