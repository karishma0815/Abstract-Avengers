
/*Abstract Avengers*/

/**
 * @file PlantItem.h
 * @brief Leaf items built from greenhouse for personalization
 * @author Taskeen Abdoola
 * @date 2025-10-14
 */
#pragma once
#include "Item.h"
#include <string>
#include <memory>

class PlantItem : public Item {
public:
    PlantItem(std::string name, double basePrice, bool ready = true);

    double priceFunc() const override;
    std::string describe() const override;
    bool readyForSale() const override;

    const std::string& name() const;
    void setReady(bool r);

private:
    std::string name_;
    double      base_;
    bool        ready_;
};