#ifndef ITERATOR_H
#define ITERATOR_H

#include "Plant.h"

class Iterator {
public:
    virtual ~Iterator() {}
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual Plant* currentItem() = 0;
};

#endif