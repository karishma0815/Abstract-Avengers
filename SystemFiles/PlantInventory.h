#ifndef PLANTINVENTORY_H
#define PLANTINVENTORY_H

#include "Aggregate.h"
#include "Plant.h"
#include <vector>
#include <string>

class PlantInventory : public Aggregate {
private:
    std::vector<Plant*> plants;

public:
    PlantInventory();
    ~PlantInventory();
    
    Iterator* createIterator();
    void addPlant(Plant* plant);
    int getSize() const;
    Plant* getPlantAt(int index) const;
};

#endif