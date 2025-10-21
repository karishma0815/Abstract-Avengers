#ifndef PLANTITERATOR_H
#define PLANTITERATOR_H

#include "Iterator.h"
#include "PlantInventory.h"

class PlantIterator : public Iterator {
private:
    PlantInventory* plantInventory;
    int current;

public:
    PlantIterator(PlantInventory* inventory);
    void first() ;
    void next() ;
    bool isDone() ;
    Plant* currentItem() ;
};

#endif