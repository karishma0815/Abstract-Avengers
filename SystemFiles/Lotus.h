#ifndef LOTUS_H
#define LOTUS_H
#include "Flower.h"

class Lotus : public Flower {
public:
    Lotus(std::string name, double price, std::string species = "Lotus");
    virtual ~Lotus();
    std::string getPlantType() const override;
};

#endif