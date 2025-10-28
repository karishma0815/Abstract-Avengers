#ifndef STOCKINVENTORY_H
#define STOCKINVENTORY_H

#include <vector>
#include <string>
#include <map>

class StockInventory {
private:
    std::map<std::string, int> plantTypeCount;
    std::map<std::string, double> plantTypeValue;
    
public:
    StockInventory();
    ~StockInventory();
    
    void updateInventory(const std::string& plantType, int quantity, double value);
    void removeFromInventory(const std::string& plantType, int quantity, double value);
    
    int getTypeCount(const std::string& plantType) const;
    double getTypeValue(const std::string& plantType) const;
    std::map<std::string, int> getAllTypeCounts() const;
    std::map<std::string, double> getAllTypeValues() const;
    
    void displayInventorySummary() const;
};

#endif