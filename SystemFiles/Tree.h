#ifndef TREE_H
#define TREE_H

#include "Plant.h"
#include "TreeProduct.h"
#include <string>

/**
 * @class Tree
 * @brief Concrete product for trees, inherits from Plant
 */
class Tree : public Plant, public TreeProduct {
protected:
    std::string species;
    std::string name;
    double price;
    
public:
    Tree(std::string name, double price, std::string species);
    virtual ~Tree();
    
    // Implement pure virtual functions from Plant
    std::string getName();
    bool isFertilized();
    std::string getPlantID();
    int getExposureSunlightHours();
    int getLastWaterLevel();
    void setName(const std::string& n);
    void setFertilized(bool fert);
    void setPlantID(const std::string& id);
    void setExposureSunlightHours(int hours);
    void setLastWaterLevel(int level);
    
    // Tree-specific methods
    virtual std::string getPlantType() const;
    std::string getSpecies() const;
    int getCount() const;
    double getTotalValue() const;
};

#endif
