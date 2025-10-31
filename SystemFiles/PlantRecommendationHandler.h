#ifndef PLANTRECOMMENDATIONHANDLER_H
#define PLANTRECOMMENDATIONHANDLER_H

#include "CustomerQueryHandler.h"
#include "StratContext.h"
#include "RecommStrategy.h"
#include "DefaultRecomm.h"
#include "WaterRecomm.h"
#include "SunlightRecomm.h"
#include "CustomerQuery.h"

class PlantRecommendationHandler : public CustomerQueryHandler {
private:
    StratContext* strategyContext;

public:
    PlantRecommendationHandler() {
        // Initialize with default recommendation strategy
        strategyContext = new StratContext(new DefaultRecomm(), nullptr);
    }

    ~PlantRecommendationHandler() {
        delete strategyContext;
    }

    bool canHandle(const CustomerQuery& query) const override {
        return query.type == CustomerQuery::CARE_ADVICE;
    }

    void handleQuery(const CustomerQuery& query) override {
        if (canHandle(query)) {
            // Choose appropriate recommendation strategy based on query content
            if (query.question.find("water") != std::string::npos) {
                strategyContext->setRecommStrategy(new WaterRecomm());
            } else if (query.question.find("sunlight") != std::string::npos || 
                      query.question.find("light") != std::string::npos) {
                strategyContext->setRecommStrategy(new SunlightRecomm());
            } else {
                strategyContext->setRecommStrategy(new DefaultRecomm());
            }

            // Execute recommendation strategy
            strategyContext->executeRecommStrategy();
        } else if (nextHandler != nullptr) {
            nextHandler->handleQuery(query);
        }
    }
};

#endif