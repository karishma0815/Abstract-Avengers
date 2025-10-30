// Pine.h
#ifndef PINE_H
#define PINE_H
#include "Tree.h"

class Pine : public Tree {
public:
    Pine(std::string name, double price, std::string species = "Pine");
    virtual ~Pine();
    std::string getPlantType() const override;
};

#endif