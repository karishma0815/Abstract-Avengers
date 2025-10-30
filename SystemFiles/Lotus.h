// Lotus.h
#ifndef LOTUS_H
#define LOTUS_H
#include "Flower.h"
#include "Plant.h"

class Lotus : public Flower {
private:
    Plant* plant;   
public:
    Lotus(std::string name, double price, std::string species = "Lotus");
    virtual ~Lotus();
    std::string getPlantType() const override;
    Plant* getPlant() const;
};

#endif