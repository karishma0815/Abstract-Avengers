#include "StaffNotificationObserver.h"
#include <iostream>
#include <ctime>

StaffNotificationObserver::StaffNotificationObserver(bool enabled) 
    : enableNotifications(enabled) {
}

StaffNotificationObserver::~StaffNotificationObserver() {
}

void StaffNotificationObserver::update(std::string plantType, int quantity, std::string action) {
    // Create timestamped notification message
    std::time_t now = std::time(nullptr);
    std::string timestamp = std::ctime(&now);
    timestamp.pop_back(); // Remove trailing newline
    
    std::string notification = "[" + timestamp + "] STAFF: " + 
                              std::to_string(quantity) + " " + 
                              plantType + "(s) " + action;
    
    notificationLog.push_back(notification);
    
    // Display if notifications are enabled
    if (enableNotifications) {
        std::cout << "|< |< " << notification << std::endl;
    }
}

void StaffNotificationObserver::toggleNotifications(bool enabled) {
    enableNotifications = enabled;
}

std::vector<std::string> StaffNotificationObserver::getNotificationLog() const {
    return notificationLog;
}

void StaffNotificationObserver::clearLog() {
    notificationLog.clear();
}

void StaffNotificationObserver::displayLog() const {
    std::cout << "\n=== STAFF NOTIFICATION LOG ===" << std::endl;
    if (notificationLog.empty()) {
        std::cout << "No notifications recorded." << std::endl;
    } else {
        for (size_t i = 0; i < notificationLog.size(); ++i) {
            std::cout << (i + 1) << ". " << notificationLog[i] << std::endl;
        }
    }
}

int StaffNotificationObserver::getLogSize() const {
    return notificationLog.size();
}