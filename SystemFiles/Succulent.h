#ifndef SUCCULENT_H
#define SUCCULENT_H

#include "SucculentProduct.h"

/**
 * @class Succulent
 * @brief Concrete leaf product for individual succulents
 */
class Succulent : public SucculentProduct {
private:
    std::string species;
    
public:
    /**
     * @brief Constructor
     * @param name Name of the succulent
     * @param price Price of the succulent
     * @param species Species of the succulent
     */
    Succulent(std::string name, double price, std::string species);
    
    /**
     * @brief Destructor
     */
    ~Succulent() override;
    
    /**
     * @brief Get count - always 1 for individual plant
     * @return 1
     */
    int getCount() const override;
    
    /**
     * @brief Get the species
     * @return Species name
     */
    std::string getSpecies() const;
    
    /**
     * @brief Get total value - same as price for leaf
     * @return Price of this succulent
     */
    double getTotalValue() const override;
};

#endif