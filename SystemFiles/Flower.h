#ifndef FLOWER_H
#define FLOWER_H

#include "FlowerProduct.h"

/**
 * @class Flower
 * @brief Concrete leaf product for individual flowers
 */
class Flower : public FlowerProduct {
private:
    std::string species;
    
public:
    Flower(std::string name, double price, std::string species);
    ~Flower() override;
    
    int getCount() const override;
    std::string getSpecies() const;
    double getTotalValue() const override;
};

#endif