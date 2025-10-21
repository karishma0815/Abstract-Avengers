/*Abstract Avengers*/

/**
 * @file PlantItem.h
 * @brief Leaf items built from greenhouse for personalization
 * @author Taskeen Abdoola
 * @date 2025-10-10
 */

#ifndef PLANTITEM_H
#define PLANTITEM_H

#include "Item.h"

#include <string>

class PlantItem : public Item {
    public:
        PlantItem(std::string name, double basePrice, bool readyForSale = true);
        double price() const override;
        std::string describe() const override;
        bool readyForSale() const override;
        std::unique_ptr<Item> clone() const override;
        const std::string& nameFunc() const;
        double basePriceFunc() const;
    private:
        std::string name;
        double basePrice;
        bool ready;
};

#endif
