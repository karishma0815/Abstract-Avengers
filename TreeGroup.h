#ifndef TREEGROUP_H
#define TREEGROUP_H

#include "TreeProduct.h"
#include <vector>

/**
 * @class TreeGroup
 * @brief Composite class for grouping tree products
 */
class TreeGroup : public TreeProduct {
private:
    std::vector<TreeProduct*> plants;
    
public:
    TreeGroup(std::string groupName);
    ~TreeGroup() override;
    
    int getCount() const override;
    void add(TreeProduct* plant) override;
    void remove(TreeProduct* plant) override;
    double getTotalValue() const override;
};

#endif