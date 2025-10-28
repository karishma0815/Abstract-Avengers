#ifndef TREE_H
#define TREE_H

#include "TreeProduct.h"

/**
 * @class Tree
 * @brief Concrete leaf product for individual trees
 */
class Tree : public TreeProduct {
private:
    std::string species;
    
public:
    Tree(std::string name, double price, std::string species);
    ~Tree();
    
    int getCount() const override;
    std::string getSpecies() const;
    double getTotalValue() const override;
    std::string getPlantType() const override;
};

#endif