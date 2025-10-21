#ifndef FLOWERFACTORY_H
#define FLOWERFACTORY_H

#include "PlantFactory.h"
#include "FlowerProduct.h"
#include "Flower.h"
#include "FlowerGroup.h"

/**
 * @class FlowerFactory
 * @brief Concrete factory for creating flower products
 */
class FlowerFactory : public PlantFactory {
private:
    int productionCounter;
    
public:
    FlowerFactory();
    ~FlowerFactory() override;
    
    SucculentProduct* createSucculent(std::string name, double price, int stock) override;
    TreeProduct* createTree(std::string name, double price, int stock) override;
    FlowerProduct* createFlower(std::string name, double price, int stock) override;
    SucculentGroup* createSucculentGroup(std::string groupName) override;
    FlowerGroup* createFlowerGroup(std::string groupName) override;
    TreeGroup* createTreeGroup(std::string groupName) override;
};

#endif