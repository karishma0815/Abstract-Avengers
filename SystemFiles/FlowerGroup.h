#ifndef FLOWERGROUP_H
#define FLOWERGROUP_H

#include "FlowerProduct.h"
#include <vector>

/**
 * @class FlowerGroup
 * @brief Composite class for grouping flower products
 */
class FlowerGroup : public FlowerProduct {
private:
    std::vector<FlowerProduct*> plants;
    
public:
    FlowerGroup(std::string groupName);
    ~FlowerGroup() override;
    
    int getCount() const override;
    void add(FlowerProduct* plant) override;
    void remove(FlowerProduct* plant) override;
    double getTotalValue() const override;
};

#endif