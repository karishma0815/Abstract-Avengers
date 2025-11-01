/*Abstract Avengers*/

/**
 * @file ArrangementBuilder.h
 * @brief Builder interface for constructing a single personalized item
 * @author Taskeen Abdoola
 * @date 2025-10-14
 */

#pragma once
#include "Item.h"
#include <memory>
#include <string>

class ArrangementBuilder {
public:
    virtual ~ArrangementBuilder() = default;

/** @brief Reset internal state before starting a new build. */
    virtual void reset() = 0;
    /**
        * @brief Start from a plant prototype (cloned).
        * @param plantPrototype Base item to clone.
        */
    virtual void buildBasePlant(const Item& proto) = 0; // clone from prototype
    /**
        * @brief Optionally add a pot.
        * @param extra Surcharge.
        * @param colour Pot colour/style.
        */
    virtual void buildPot(double extra, const std::string& color) = 0;
    /**
        * @brief Optionally add gift wrap.
        * @param extra Surcharge.
        * @param message Message text.
        */
    virtual void buildWrap(double extra, const std::string& message) = 0;
    virtual void buildNote(double extra, const std::string& text) = 0;
    /**
        * @brief Yield the finished product and clear builder state.
        * @return Ownership of the built Item.
        */
    virtual std::unique_ptr<Item> getResult() = 0;
};