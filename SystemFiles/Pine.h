// Pine.h
#ifndef PINE_H
#define PINE_H
#include "Tree.h"
#include "Plant.h"  

class Pine : public Tree {
private:
    Plant* plant;
public:
    Pine(std::string name, double price, std::string species = "Pine");
    virtual ~Pine();
    std::string getPlantType() const;
    Plant* getPlant() const;
};

#endif