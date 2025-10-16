/*Abstract Avengers*/

/**
 * @file ArrangementBuilder.h
 * @brief Builder interface for constructing a single personalized item
 * @author Taskeen Abdoola
 * @date 2025-10-14
 */

#ifndef ARRANGEMENTBUILDER_H
#define ARRANGEMENTBUILDER_H

#include "Item.h"

#include <memory>

class Item;

class ArrangementBuilder : public Item
{
    public:
        virtual ~ArrangementBuilder() {}

        /** @brief Reset internal state before starting a new build. */
        virtual void reset() = 0;

        /**
        * @brief Start from a plant prototype (cloned).
        * @param plantPrototype Base item to clone.
        */
        virtual void buildBasePlant(const Item& plantProto) = 0;

        /**
        * @brief Optionally add a pot.
        * @param extra Surcharge.
        * @param colour Pot colour/style.
        */
        virtual void buildPot(double extra, const std::string& colour) = 0;

        /**
        * @brief Optionally add gift wrap.
        * @param extra Surcharge.
        * @param message Message text.
        */
        virtual void buildWrap(double extra, const std::string& message) = 0;

        /**
        * @brief Optionally add a note.
        * @param extra Surcharge.
        * @param text Note text.
        */
        virtual void buildNote(double extra, const std::string& text) = 0;

        /**
        * @brief Yield the finished product and clear builder state.
        * @return Ownership of the built Item.
        */
        virtual std::unique_ptr<Item> getResult() = 0;
};

#endif