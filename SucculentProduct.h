#ifndef SUCCULENTPRODUCT_H
#define SUCCULENTPRODUCT_H

#include <string>

/**
 * @class SucculentProduct
 * @brief Abstract product and component for succulent hierarchy
 * Serves as both the product from Abstract Factory and Component in Composite pattern
 */
class SucculentProduct {
protected:
    std::string name;
    double price;
    
public:
    /**
     * @brief Constructor
     * @param name Name of the succulent product
     * @param price Price of the succulent product
     */
    SucculentProduct(std::string name, double price);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~SucculentProduct();
    
    /**
     * @brief Get the plant type
     * @return String representing the plant type
     */
    virtual std::string getPlantType() const;
    
    /**
     * @brief Get the count of plants
     * @return Number of plants (1 for leaf, sum for composite)
     */
    virtual int getCount() const = 0;
    
    /**
     * @brief Get the name of the product
     * @return Product name
     */
    virtual std::string getName() const;
    
    /**
     * @brief Add a plant to the collection (composite operation)
     * @param plant Pointer to SucculentProduct to add
     */
    virtual void add(SucculentProduct* plant);
    
    /**
     * @brief Remove a plant from the collection (composite operation)
     * @param plant Pointer to SucculentProduct to remove
     */
    virtual void remove(SucculentProduct* plant);
    
    /**
     * @brief Get total value of this product/group
     * @return Total price value
     */
    virtual double getTotalValue() const = 0;
};

#endif