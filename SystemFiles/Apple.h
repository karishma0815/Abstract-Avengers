// Apple.h
#ifndef APPLE_H
#define APPLE_H
#include "Tree.h"
#include "Plant.h"

class Apple : public Tree {
private:
    Plant* plant;
public:
    Apple(std::string name, double price, std::string species = "Apple");
    virtual ~Apple();
    std::string getPlantType() const;
    Plant* getPlant() const;
};

#endif