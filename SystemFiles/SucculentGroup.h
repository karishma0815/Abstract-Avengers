#ifndef SUCCULENTGROUP_H
#define SUCCULENTGROUP_H

#include "SucculentProduct.h"
#include <vector>

/**
 * @class SucculentGroup
 * @brief Composite class for grouping succulent products
 */
class SucculentGroup : public SucculentProduct {
private:
    std::vector<SucculentProduct*> plants;
    
public:
    /**
     * @brief Constructor
     * @param groupName Name of the group
     */
    SucculentGroup(std::string groupName);
    
    /**
     * @brief Destructor - deletes all contained plants
     */
    ~SucculentGroup() override;
    
    /**
     * @brief Get total count of all plants in group
     * @return Sum of counts from all children
     */
    int getCount() const override;
    
    /**
     * @brief Add a plant to the group
     * @param plant Pointer to SucculentProduct to add
     */
    void add(SucculentProduct* plant) override;
    
    /**
     * @brief Remove a plant from the group
     * @param plant Pointer to SucculentProduct to remove
     */
    void remove(SucculentProduct* plant) override;
    
    /**
     * @brief Get total value of all plants in group
     * @return Sum of values from all children
     */
    double getTotalValue() const override;
};

#endif