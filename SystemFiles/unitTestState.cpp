#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "SalesContext.h"
#include "BrowsingState.h"
#include "SeekingAssistanceState.h"
#include "CartOpenState.h"
#include "AwaitingStockState.h"
#include "Customer.h"
#include "CustomerQuery.h"

static std::string stateName(SalesContext& ctx) 
{ 
    return ctx.current().getStateName(); 
}

TEST_CASE("[Assist] Pricing query with SKU reserves stock -> CartOpen")
{
    Customer c;
    c.setName("Test");
    SalesContext ctx(BrowsingState::instance(), c);
    ctx.putStock("ABC", 3);

    // Move into seeking assistance
    ctx.setState(SeekingAssistanceState::instance());

    // Selecting triggers a PRICING query first (CoR), then transition
    SeekingAssistanceState::instance().onSelect("ABC", 2);

    CHECK(stateName(ctx) == std::string("CartOpen"));
    CHECK(ctx.stockOf("ABC") == 1); // reserved 2
}

TEST_CASE("[Assist] Pricing query w/o SKU -> back to Browsing")
{
    Customer c;
    c.setName("A");
    SalesContext ctx(BrowsingState::instance(), c);

    ctx.setState(SeekingAssistanceState::instance());

    CustomerQuery q(CustomerQuery::PRICING, "What's the price for orchids?", &c);
    SeekingAssistanceState::instance().handleCustomerQuery(q);

    CHECK(stateName(ctx) == std::string("Browsing"));
}

TEST_CASE("[Assist] Pricing query with OOS -> AwaitingStock")
{
    Customer c;
    c.setName("B");
    SalesContext ctx(BrowsingState::instance(), c);

    ctx.setState(SeekingAssistanceState::instance());

    // No stock ⇒ AwaitingStock
    CustomerQuery q(CustomerQuery::PRICING, "What's the price and availability for SKU XYZ qty 5", &c);
    SeekingAssistanceState::instance().handleCustomerQuery(q);

    CHECK(stateName(ctx) == std::string("AwaitingStock"));
}
