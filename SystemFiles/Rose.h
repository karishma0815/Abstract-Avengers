// Rose.h
#ifndef ROSE_H
#define ROSE_H
#include "Flower.h"

class Rose : public Flower {
public:
    Rose(std::string name, double price, std::string species = "Rose");
    virtual ~Rose();
    std::string getPlantType() const override;
};

#endif

