#ifndef PRICINGQUERYHANDLER_H
#define PRICINGQUERYHANDLER_H

#include "CustomerQueryHandler.h"
#include "StratContext.h"
#include "PricingStrategy.h"
#include "RegularPrice.h"
#include "BulkDiscount.h"
#include "CustomerQuery.h"

class PricingQueryHandler : public CustomerQueryHandler {
private:
    StratContext* strategyContext;

public:
    PricingQueryHandler() {
        // Initialize with default pricing strategy
        strategyContext = new StratContext(nullptr, new RegularPrice());
    }

    ~PricingQueryHandler() {
        delete strategyContext;
    }

    bool canHandle(const CustomerQuery& query) const override {
        return query.type == CustomerQuery::PRICING;
    }

    void handleQuery(const CustomerQuery& query) override {
        if (canHandle(query)) {
            // Check if query mentions bulk or regular pricing
            if (query.question.find("bulk") != std::string::npos) {
                strategyContext->setPricingStrategy(new BulkDiscount());
            } else {
                strategyContext->setPricingStrategy(new RegularPrice());
            }

            // Process pricing query using appropriate strategy
            // Note: In real implementation, parse quantity and base price from query
            double result = strategyContext->executePricingStrategy(1, 25.0, "");
            
            // Handle the pricing result (e.g., communicate back to customer)
            std::cout << "Price calculated for " << query.question << ": R" << result << std::endl;
        } else if (nextHandler != nullptr) {
            nextHandler->handleQuery(query);
        }
    }
};

#endif