#ifndef APPLE_H
#define APPLE_H
#include "Tree.h"

class Apple : public Tree {
public:
    Apple(std::string name, double price, std::string species = "Apple");
    virtual ~Apple();
    std::string getPlantType() const override;
};

#endif