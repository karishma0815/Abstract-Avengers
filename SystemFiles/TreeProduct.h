#ifndef TREEPRODUCT_H
#define TREEPRODUCT_H

#include <string>

/**
 * @class TreeProduct
 * @brief Abstract product and component for tree hierarchy
 */
class TreeProduct {
protected:
    std::string name;
    double price;
    
public:
    TreeProduct(std::string name, double price);
    virtual ~TreeProduct();
    
    virtual std::string getPlantType() const = 0;
    virtual int getCount() const = 0;
    virtual std::string getName() const;
    virtual void add(TreeProduct* plant);
    virtual void remove(TreeProduct* plant);
    virtual double getTotalValue() const = 0;
    virtual double getPrice() const;
};

#endif