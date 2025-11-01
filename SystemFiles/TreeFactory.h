#ifndef TREEFACTORY_H
#define TREEFACTORY_H

#include "PlantFactory.h"
#include "TreeProduct.h"
#include "Tree.h"
#include "TreeGroup.h"

/**
 * @class TreeFactory
 * @brief Concrete factory for creating tree products
 */
class TreeFactory : public PlantFactory {
private:
    int productionCounter;
    
public:
    TreeFactory();
    ~TreeFactory() override;
    
    SucculentProduct* createSucculent(std::string name, double price, std::string species, int stock);
    TreeProduct* createTree(std::string name, double price, std::string species, int stock) override;
    FlowerProduct* createFlower(std::string name, double price, std::string species, int stock) override;
    SucculentGroup* createSucculentGroup(std::string groupName) override;
    FlowerGroup* createFlowerGroup(std::string groupName) override;
    TreeGroup* createTreeGroup(std::string groupName) override;
};

#endif