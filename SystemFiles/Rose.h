// Rose.h
#ifndef ROSE_H
#define ROSE_H
#include "Flower.h"
#include "Plant.h"

class Rose : public Flower {

private:
    Plant* plant;
public:
    Rose(std::string name, double price, std::string species = "Rose");
    virtual ~Rose();
    std::string getPlantType() const override;
    Plant* getPlant();
};

#endif