#ifndef STOCKMANAGER_H
#define STOCKMANAGER_H

#include "StockObserver.h"
#include "SucculentProduct.h"
#include "FlowerProduct.h"
#include "TreeProduct.h"
#include "StockInventory.h"
#include <vector>
#include <string>

/**
 * @class StockManager
 * @brief Subject in Observer pattern - manages plant stock and notifies observers
 */
class StockManager {
private:
    std::vector<StockObserver*> observers;
    std::vector<SucculentProduct*> succulentStock;
    std::vector<FlowerProduct*> flowerStock;
    std::vector<TreeProduct*> treeStock;
    StockInventory inventory;
    
    /**
     * @brief Notify all observers of stock change
     * @param plantType Type of plant
     * @param quantity Quantity changed
     * @param action "added" or "removed"
     */




    void notify(std::string plantType, int quantity, std::string action);
    
public:
    /**
     * @brief Constructor
     */
    StockManager();
    
    /**
     * @brief Destructor - cleans up all stock
     */
    ~StockManager();
    
    /**
     * @brief Attach an observer
     * @param observer Observer to attach
     */
    void attach(StockObserver* observer);
    
    /**
     * @brief Detach an observer
     * @param observer Observer to detach
     */
    void detach(StockObserver* observer);
    
    // Succulent management
    /**
     * @brief Add succulent to stock
     * @param plant Succulent product to add
     * @param quantity Quantity (default from plant's getCount())
     */
    void addSucculent(SucculentProduct* plant);
    
    /**
     * @brief Remove succulent from stock by index
     * @param index Index of succulent to remove
     */
    void removeSucculent(int index);
    
    /**
     * @brief Get succulent at index
     * @param index Index of succulent
     * @return Pointer to SucculentProduct
     */
    SucculentProduct* getSucculent(int index) const;
    
    /**
     * @brief Get size of succulent stock
     * @return Number of succulent items in stock
     */
    int getSucculentStockSize() const;
    
    // Flower management
    /**
     * @brief Add flower to stock
     * @param plant Flower product to add
     */
    void addFlower(FlowerProduct* plant);
    
    /**
     * @brief Remove flower from stock by index
     * @param index Index of flower to remove
     */
    void removeFlower(int index);
    
    /**
     * @brief Get flower at index
     * @param index Index of flower
     * @return Pointer to FlowerProduct
     */
    FlowerProduct* getFlower(int index) const;
    
    /**
     * @brief Get size of flower stock
     * @return Number of flower items in stock
     */
    int getFlowerStockSize() const;
    
    // Tree management
    /**
     * @brief Add tree to stock
     * @param plant Tree product to add
     */
    void addTree(TreeProduct* plant);
    
    /**
     * @brief Remove tree from stock by index
     * @param index Index of tree to remove
     */
    void removeTree(int index);
    
    /**
     * @brief Get tree at index
     * @param index Index of tree
     * @return Pointer to TreeProduct
     */
    TreeProduct* getTree(int index) const;
    
    /**
     * @brief Get size of tree stock
     * @return Number of tree items in stock
     */
    int getTreeStockSize() const;
    
    // General methods
    /**
     * @brief Display all stock
     */
    void displayAllStock() const;
    
    /**
     * @brief Get total stock count
     * @return Total number of all plants
     */
    int getTotalStockCount() const;
    
    /**
     * @brief Get total stock value
     * @return Total value of all stock
     */
    double getTotalStockValue() const;
    
    /**
     * @brief Get all succulent stock
     * @return Vector of SucculentProduct pointers
     */
    std::vector<SucculentProduct*> getSucculentStock() const;
    
    /**
     * @brief Get all flower stock
     * @return Vector of FlowerProduct pointers
     */
    std::vector<FlowerProduct*> getFlowerStock() const;
    
    /**
     * @brief Get all tree stock
     * @return Vector of TreeProduct pointers
     */
    std::vector<TreeProduct*> getTreeStock() const;



    //this new method here
//void StockManager::displayInventoryBreakdown() const;
    void displayInventoryBreakdown() const;
};




#endif