#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

#include <string>
#include "SucculentProduct.h"
#include "FlowerProduct.h"
#include "TreeProduct.h"
#include "SucculentGroup.h"
#include "FlowerGroup.h"
#include "TreeGroup.h"

/**
 * @class PlantFactory
 * @brief Abstract Factory for creating plant products
 */
class PlantFactory {

protected:
    /**
     * @brief Protected production counter to track number of created products
     */
    int productionCounter;

public:
    /**
     * @brief Constructor
     */
    PlantFactory();
    
    /**
     * @brief Virtual destructor
     */
    virtual ~PlantFactory();
    
    /**
     * @brief Create a succulent product
     * @param name Name of the succulent
     * @param price Price of the succulent
     * @param stock Stock quantity
     * @return Pointer to created SucculentProduct
     */
    virtual SucculentProduct* createSucculent(std::string name, double price, int stock) = 0;
    
    /**
     * @brief Create a tree product
     * @param name Name of the tree
     * @param price Price of the tree
     * @param stock Stock quantity
     * @return Pointer to created TreeProduct
     */
    virtual TreeProduct* createTree(std::string name, double price, int stock) = 0;
    
    /**
     * @brief Create a flower product
     * @param name Name of the flower
     * @param price Price of the flower
     * @param stock Stock quantity
     * @return Pointer to created FlowerProduct
     */
    virtual FlowerProduct* createFlower(std::string name, double price, int stock) = 0;
    
    /**
     * @brief Create a succulent group
     * @param groupName Name of the group
     * @return Pointer to created SucculentGroup
     */
    virtual SucculentGroup* createSucculentGroup(std::string groupName) = 0;
    
    /**
     * @brief Create a flower group
     * @param groupName Name of the group
     * @return Pointer to created FlowerGroup
     */
    virtual FlowerGroup* createFlowerGroup(std::string groupName) = 0;
    
    /**
     * @brief Create a tree group
     * @param groupName Name of the group
     * @return Pointer to created TreeGroup
     */
    virtual TreeGroup* createTreeGroup(std::string groupName) = 0;
};

#endif