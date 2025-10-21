#ifndef INVENTORYOBSERVER_H
#define INVENTORYOBSERVER_H

#include "StockObserver.h"
#include <map>
#include <string>

/**
 * @class InventoryObserver
 * @brief Concrete observer that tracks inventory levels
 */
class InventoryObserver : public StockObserver {
private:
    std::map<std::string, int> inventoryLevels;
    int lowStockThreshold;
    
public:
    /**
     * @brief Constructor
     * @param threshold Low stock alert threshold (default 5)
     */
    InventoryObserver(int threshold = 5);
    
    /**
     * @brief Destructor
     */
    ~InventoryObserver() override;
    
    /**
     * @brief Update inventory levels when notified
     * @param plantType Type of plant
     * @param quantity Quantity changed
     * @param action "added" or "removed"
     */
    void update(std::string plantType, int quantity, std::string action) override;
    
    /**
     * @brief Get current stock level for a plant type
     * @param plantType Type of plant to query
     * @return Current stock level
     */
    int getStockLevel(std::string plantType) const;
    
    /**
     * @brief Set the low stock threshold
     * @param threshold New threshold value
     */
    void setLowStockThreshold(int threshold);
    
    /**
     * @brief Display all inventory levels
     */
    void displayInventory() const;
    
    /**
     * @brief Get total inventory count across all types
     * @return Total number of plants in inventory
     */
    int getTotalInventoryCount() const;
};

#endif