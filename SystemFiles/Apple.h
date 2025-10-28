// Apple.h
#ifndef APPLE_H
#define APPLE_H
#include "Tree.h"

class Apple : public Tree {
public:
    Apple(std::string name, double price, std::string species = "Apple");
    ~Apple();
    std::string getPlantType() const;
};

#endif