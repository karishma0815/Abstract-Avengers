/*Abstract Avengers*/

/**
 * @file BrowsingState.cpp
 * @brief Implementation of BrowsingState.
 */

#include "BrowsingState.h"
#include "CartOpenState.h"
#include "SeekingAssistanceState.h"
#include "AwaitingStockState.h"
#include "CancelledState.h"
#include "SalesContext.h"

BrowsingState& BrowsingState::instance() 
{
  static BrowsingState s; 
  return s;
}

std::string BrowsingState::getStateName() const 
{ 
    return "Browsing"; 
}

void BrowsingState::onSelect(const std::string& sku, int qty) 
{
  if (ctxFunc().hasStock(sku, qty) && ctxFunc().reserveStock(sku, qty)) 
  {
    ctxFunc().notify("Item reserved; moving to CartOpen.");
    ctxFunc().setState(CartOpenState::instance());
  } 
  else 
  {
    ctxFunc().notify("Out-of-stock; AwaitingStock.");
    ctxFunc().setState(AwaitingStockState::instance());
  }
}

void BrowsingState::onAssist() 
{
  ctxFunc().notify("Requesting assistance...");
  ctxFunc().setState(SeekingAssistanceState::instance());
}

void BrowsingState::onCancel() 
{
  ctxFunc().notify("Browsing cancelled.");
  ctxFunc().setState(CancelledState::instance());
}
