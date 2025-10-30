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

#include "CustomerQuery.h"
#include "JuniorStaff.h"
#include "SalesAssistant.h"
#include "SalesExpert.h"
#include "Manager.h"

namespace 
{
template <typename Handler>
bool tryHandle(Handler& h, const CustomerQuery& q) {
    if (h.canHandle(q)) { h.handleQuery(q); return true; }
    return false;
}
} 

SeekingAssistanceState& SeekingAssistanceState::instance() 
{
  static SeekingAssistanceState s; 
  return s;
}

std::string SeekingAssistanceState::getStateName() const 
{ 
  return "SeekingAssistance"; 
}

void SeekingAssistanceState::onEnter() 
{
  ctxFunc().notify("Welcome! Our staff is ready to assist you.");
}

void SeekingAssistanceState::onAssistComplete() 
{
  ctxFunc().notify("Assistance complete. Returning to Browsing.");
  ctxFunc().setState(BrowsingState::instance());
}

void SeekingAssistanceState::onSelect(const std::string& sku, int qty) 
{
  std::string q = "What's the price and availability for SKU " + sku +
                    " qty " + std::to_string(qty);
  CustomerQuery query(CustomerQuery::PRICING, q, /*customer*/ nullptr);
  handleCustomerQuery(query);
}

void SeekingAssistanceState::onCancel() 
{
  ctxFunc().notify("Cancelled during assistance.");
  ctxFunc().setState(CancelledState::instance());
}

void SeekingAssistanceState::handleCustomerQuery(const CustomerQuery& query) 
{
    JuniorStaff junior;
    SalesAssistant assistant("Assistant", 1, /*inv*/ nullptr, /*comm*/ 0.05);
    SalesExpert expert;
    Manager manager("Store Manager", 100, /*inv*/ nullptr, "Sales");

    bool handled =
        tryHandle(junior,    query) ||
        tryHandle(assistant, query) ||
        tryHandle(expert,    query) ||
        tryHandle(manager,   query);

    if (!handled) 
    {
      ctxFunc().notify("No staff could handle the query right now.");
      //Fall back to browsing and let the user continue
      ctxFunc().setState(BrowsingState::instance());
      return;
    }

    switch (query.type) 
    {
        case CustomerQuery::PRICING: 
        {
            std::string sku;
            int qty = 1;
            if (parseSkuQty(query.question, sku, qty)) 
            {
                if (ctxFunc().hasStock(sku, qty) && ctxFunc().reserveStock(sku, qty)) 
                {
                    ctxFunc().notify("Item reserved after assistance. Opening cart.");
                    ctxFunc().setState(CartOpenState::instance());
                } 
                else 
                {
                    ctxFunc().notify("Item confirmed out-of-stock. Awaiting replenishment.");
                    ctxFunc().setState(AwaitingStockState::instance());
                }
            } 
            else 
            {
                // General price question → keep user in assistance or go back to browsing
                ctxFunc().notify("Pricing info provided. You can keep browsing.");
                ctxFunc().setState(BrowsingState::instance());
            }
            break;
        }

        case CustomerQuery::SPECIAL_REQUEST:
          ctxFunc().notify("Special request noted. Returning to browsing.");
          ctxFunc().setState(BrowsingState::instance());
          break;

        case CustomerQuery::COMPLAINT:
          ctxFunc().notify("We are sorry about the issue. Please continue shopping while we assist.");
          ctxFunc().setState(BrowsingState::instance());
          break;

        default:
          ctxFunc().notify("Thanks for your question. Happy shopping!");
          ctxFunc().setState(BrowsingState::instance());
          break;
    }
}

bool SeekingAssistanceState::parseSkuQty(const std::string& text, std::string& skuOut, int& qtyOut) 
{
    auto findWord = [&](const std::string& key) -> size_t 
    {
      auto pos = text.find(key);
      return pos == std::string::npos ? pos : pos + key.size();
    };

    size_t pSku = findWord("SKU ");
    if (pSku == std::string::npos) 
    {
      return false;
    }

    size_t endSku = pSku;
    while (endSku < text.size() && !isspace(static_cast<unsigned char>(text[endSku]))) ++endSku;
    skuOut = text.substr(pSku, endSku - pSku);

    //qty defaults to 1; only overwrite if we find "qty "
    qtyOut = 1;
    size_t pQty = findWord("qty ");
    if (pQty != std::string::npos) 
    {
        int val = 0;
        size_t i = pQty;
        bool any = false;
        while (i < text.size() && isdigit(static_cast<unsigned char>(text[i]))) 
        {
            any = true;
            val = val * 10 + (text[i]-'0');
            ++i;
        }
        if (any) qtyOut = val;
    }
    return true;
}