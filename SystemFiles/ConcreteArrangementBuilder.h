/*Abstract Avengers*/

/**
 * @file ArrangementBuilder.h
 * @brief Builder interface for constructing a single personalized item
 * @author Taskeen Abdoola
 * @date 2025-10-14
 */

#pragma once
#include "ArrangementBuilder.h"
#include <memory>

class ConcreteArrangementBuilder : public ArrangementBuilder {
public:
    void reset() override;
    void buildBasePlant(const Item& proto) override;
    void buildPot(double extra, const std::string& color) override;
    void buildWrap(double extra, const std::string& message) override;
    void buildNote(double extra, const std::string& text) override;
    std::unique_ptr<Item> getResult() override;

private:
    std::unique_ptr<Item> current_;
};
