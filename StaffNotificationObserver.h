#ifndef STAFFNOTIFICATIONOBSERVER_H
#define STAFFNOTIFICATIONOBSERVER_H

#include "StockObserver.h"
#include <vector>
#include <string>

/**
 * @class StaffNotificationObserver
 * @brief Concrete observer that logs stock changes for staff
 */
class StaffNotificationObserver : public StockObserver {
private:
    std::vector<std::string> notificationLog;
    bool enableNotifications;
    
public:
    /**
     * @brief Constructor
     * @param enabled Whether notifications are enabled (default true)
     */
    StaffNotificationObserver(bool enabled = true);
    
    /**
     * @brief Destructor
     */
    ~StaffNotificationObserver() override;
    
    /**
     * @brief Update method - logs stock changes
     * @param plantType Type of plant
     * @param quantity Quantity changed
     * @param action "added" or "removed"
     */
    void update(std::string plantType, int quantity, std::string action) override;
    
    /**
     * @brief Toggle notifications on/off
     * @param enabled True to enable, false to disable
     */
    void toggleNotifications(bool enabled);
    
    /**
     * @brief Get the notification log
     * @return Vector of notification strings
     */
    std::vector<std::string> getNotificationLog() const;
    
    /**
     * @brief Clear the notification log
     */
    void clearLog();
    
    /**
     * @brief Display all logged notifications
     */
    void displayLog() const;
    
    /**
     * @brief Get the number of logged notifications
     * @return Size of the log
     */
    int getLogSize() const;
};

#endif