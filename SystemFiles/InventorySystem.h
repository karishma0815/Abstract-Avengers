#ifndef INVENTORYSYSTEM_H
#define INVENTORYSYSTEM_H

#include "PlantInventory.h"
#include "Iterator.h"
#include <string>

class InventorySystem {
private:
    PlantInventory* plantCollection;
    PlantInventory* growing;

public:
    InventorySystem();
    ~InventorySystem();
    
    void addPlant(Plant* plant, bool ready);
    void ageReadyForSale(Iterator* iterator);
    void ageGrowingIterator(Iterator* iterator);
    PlantInventory* getPlantCollection();
    PlantInventory* getGrowing();
};

#endif