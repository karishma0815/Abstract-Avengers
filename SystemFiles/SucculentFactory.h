#ifndef SUCCULENTFACTORY_H
#define SUCCULENTFACTORY_H

#include "PlantFactory.h"
#include "SucculentProduct.h"
#include "Succulent.h"
#include "SucculentGroup.h"

/**
 * @class SucculentFactory
 * @brief Concrete factory for creating succulent products
 */
class SucculentFactory : public PlantFactory {
private:
    int productionCounter;
    
public:
    /**
     * @brief Constructor
     */
    SucculentFactory();
    
    /**
     * @brief Destructor
     */
    ~SucculentFactory() override;
    
    /**
     * @brief Create a succulent
     * @param name Name of succulent
     * @param price Price
     * @param stock Stock count
     * @return Pointer to new Succulent
     */
    SucculentProduct* createSucculent(std::string name, double price, int stock) override;
    
    /**
     * @brief Create tree - not supported by SucculentFactory
     * @return nullptr
     */
    TreeProduct* createTree(std::string name, double price, int stock) override;
    
    /**
     * @brief Create flower - not supported by SucculentFactory
     * @return nullptr
     */
    FlowerProduct* createFlower(std::string name, double price, int stock) override;
    
    /**
     * @brief Create succulent group
     * @param groupName Name of the group
     * @return Pointer to new SucculentGroup
     */
    SucculentGroup* createSucculentGroup(std::string groupName) override;
    
    /**
     * @brief Create flower group - not supported
     * @return nullptr
     */
    FlowerGroup* createFlowerGroup(std::string groupName) override;
    
    /**
     * @brief Create tree group - not supported
     * @return nullptr
     */
    TreeGroup* createTreeGroup(std::string groupName) override;
};

#endif