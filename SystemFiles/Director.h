#pragma once
#include "ArrangementBuilder.h"
#include <memory>
#include <string>

class Director {
public:
    /**
        * @brief Set the builder used by recipes.
        * @param b Non-owning pointer to an ArrangementBuilder.
        */
    void setBuilder(ArrangementBuilder* b);

     /**
        * @brief Build a gift: base + pot + wrap.
        * @param plantPrototype Base plant to clone.
        * @param potExtra Surcharge for the pot.
        * @param colour Pot colour/style.
        * @param wrapExtra Surcharge for wrap.
        * @param message Wrap message text.
        * @return Finished item.
        */
    std::unique_ptr<Item> buildGift(const Item& proto,
                                    double potExtra,  const std::string& potColor,
                                    double wrapExtra, const std::string& message);

                                    /**
        * @brief Build a gift with a note: base + pot + wrap + note.
        * @param noteExtra Surcharge for the note.
        * @param text Note text.
        * @return Finished item.
        */
    std::unique_ptr<Item> buildGiftWithNote(const Item& proto,
                                            double potExtra,  const std::string& potColor,
                                            double wrapExtra, const std::string& message,
                                            double noteExtra, const std::string& noteText);

private:
    ArrangementBuilder* b_{nullptr};
};