/**
 * @file NurseryInventoryMediator.h
 * @brief this is the definition of NurseryInventoryMediator class for concrete inventory coordination
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef NURSERYINVENTORYMEDIATOR_H
#define NURSERYINVENTORYMEDIATOR_H

#include "InventoryMediator.h"
#include <vector>
#include <string>
#include <unordered_map>

class Staff;
class Plant;

/**
 * @class NurseryInventoryMediator
 * @brief this is the concrete mediator implementation for nursery inventory coordination this class implements the Mediator pattern to coordinate inventory operations
 * between different staff members in the nursery. It maintains stock levels for both greenhouse and sales floor locations and processes inventory events
 * such as plant movements, sales and deliveries
 */

class NurseryInventoryMediator : public InventoryMediator{
    private:
        std::unordered_map<std::string, int> salesFloorStock;
        
        const std::unordered_map<std::string, int> INITIAL_SALES_FLOOR_STOCK = {
            {"rose", 50}, {"protea", 30}, {"lotus", 20},
            {"orchid", 40}, {"jade", 35}, {"cacti", 25},
            {"apple", 15}, {"pine", 10}, {"jacaranda", 12}
        };
        
        std::string getPlantId(Plant *plant) const;
        
        void autoRestockIfNeeded(const std::string& plantId);
    public:
        /**
         * @brief this is a constructor that constructs a NurseryInventoryMediator with initial stock levels
         */
        NurseryInventoryMediator();

        /**
         * @brief this function processes inventory events and coordinates staff communications
         * @param sender this is the staff member triggering the event
         * @param event this is the type of inventory event
         * @param plant this is the plant affected by the event
         * @param quantity this is the quantity involved in the event
         * it handles various inventory events including plant movements between greenhouse and sales floor, sales transactions, new deliveries,
         * and stock checks. Updates internal stock levels and provides coordination between gardening and sales staff.
         */
        void notify(Staff* sender, const std::string& event, Plant* plant, int quantity);

        /**
         * @brief this function updates internal inventory levels
         * @param plant this is the plant being tracked (for future extensibility)
         * @param greenhouseQuantity these are for the changes in greenhouse stock quantity
         * @param salesFloorQuantity these are for the changes in sales floor stock quantity
         * it modifies the greenhouse and sales floor stock levels while ensuring quantities are not negative. This method encapsulates the core
         * inventory update logic used by various event handlers
         */
        void updateInventory(Plant* plant, int salesFloorQuantity);

        /**
         * @brief this function gets the current greenhouse stock level
         * @param plant this is the plant to check for
         * @return int this is the current greenhouse stock quantity
         */
        int getGreenhouseStock(Plant* plant) const;

        /**
         * @brief this function gets the current sales floor stock level
         * @param plant this is the plant to check for
         * @return int this is the current sales floor stock quantity
         */
        int getSalesFloorStock(Plant* plant) const;

        /**
         * @brief Manual restocking from greenhouse to sales floor
         * @param plant Plant to restock
         * @param quantity Quantity to move from greenhouse to sales floor
         */
        void restockFromGreenhouse(Plant* plant, int quantity);
        
        /**
         * @brief Check if plant can be sold from sales floor
         * @param plant Plant to check
         * @return True if sales floor has stock
         */
        bool canSellFromSalesFloor(Plant* plant);
};

#endif