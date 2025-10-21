/*Abstract Avengers*/

/**
 * @file ConcreteArrangementBuilder.h
 * @brief COncrete builder for constructing a single personalized item
 * @author Taskeen Abdoola
 * @date 2025-10-14
 */

#ifndef CONCRETEARRANGEMENTBUILDER_H
#define CONCRETEARRANGEMENTBUILDER_H

#include "Item.h"
#include "ArrangementBuilder.h"

#include <memory>

class Item;

class ConcreteArrangementBuilder : public ArrangementBuilder
{
    public:
        ConcreteArrangementBuilder();
        void reset() override;
        void buildBasePlant(const Item& plantProto) override;
        void buildPot(double extra, const std::string& colour) override;
        void buildWrap(double extra, const std::string& message) override;
        void buildNote(double extra, const std::string& text) override;
        std::unique_ptr<Item> getResult() override;
        bool hasProduct() const; //state, if no request replenishment?

    private:
        std::unique_ptr<Item> single;
};

#endif