#ifndef STOCKOBSERVER_H
#define STOCKOBSERVER_H

#include <string>

/**
 * @class StockObserver
 * @brief Observer interface for stock management notifications
 */
class StockObserver {
public:
    /**
     * @brief Constructor
     */
    StockObserver();
    
    /**
     * @brief Virtual destructor
     */
    virtual ~StockObserver();
    
    /**
     * @brief Update method called when stock changes
     * @param plantType Type of plant that changed
     * @param quantity Number of plants added/removed
     * @param action Action performed ("added" or "removed")
     */
    virtual void update(std::string plantType, int quantity, std::string action) = 0;
};

#endif