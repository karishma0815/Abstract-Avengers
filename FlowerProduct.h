#ifndef FLOWERPRODUCT_H
#define FLOWERPRODUCT_H

#include <string>

/**
 * @class FlowerProduct
 * @brief Abstract product and component for flower hierarchy
 */
class FlowerProduct {
protected:
    std::string name;
    double price;
    
public:
    FlowerProduct(std::string name, double price);
    virtual ~FlowerProduct();
    
    virtual std::string getPlantType() const;
    virtual int getCount() const = 0;
    virtual std::string getName() const;
    virtual void add(FlowerProduct* plant);
    virtual void remove(FlowerProduct* plant);
    virtual double getTotalValue() const = 0;
};

#endif