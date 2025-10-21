/*Abstract Avengers*/

/**
 * @file Director.h
 * @brief Director that orchestrates common build recipes
 * @author Taskeen Abdoola
 * @date 2025-10-15
 */

#ifndef NURSERY_DIRECTOR_H
#define NURSERY_DIRECTOR_H

#include "Item.h"
#include "ArrangementBuilder.h"

#include <memory>
#include <string>

class Item;

class Director 
{
    public:
        /**
        * @brief Set the builder used by recipes.
        * @param b Non-owning pointer to an ArrangementBuilder.
        */
        void setBuilder(ArrangementBuilder* b);

        ArrangementBuilder* builderFunc() const;

        /**
        * @brief Build a gift: base + pot + wrap.
        * @param plantPrototype Base plant to clone.
        * @param potExtra Surcharge for the pot.
        * @param colour Pot colour/style.
        * @param wrapExtra Surcharge for wrap.
        * @param message Wrap message text.
        * @return Finished item.
        */
        std::unique_ptr<Item> buildGift(const Item& plantProto,
            double potExtra, const std::string& color,
            double wrapExtra, const std::string& message);

        /**
        * @brief Build a gift with a note: base + pot + wrap + note.
        * @param noteExtra Surcharge for the note.
        * @param text Note text.
        * @return Finished item.
        */
        std::unique_ptr<Item> buildGiftWithNote(const Item& plantPrototype,
            double potExtra, const std::string& color,
            double wrapExtra, const std::string& message,
            double noteExtra, const std::string& text);
                                        
    private:
        ArrangementBuilder* builder;
};

#endif
