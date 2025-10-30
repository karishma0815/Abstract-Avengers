// Protea.h
#ifndef PROTEA_H
#define PROTEA_H
#include "Flower.h"
#include "Plant.h"  

class Protea : public Flower {
private:
    Plant* plant;   
public:
    Protea(std::string name, double price, std::string species = "Protea");
    virtual ~Protea();
    std::string getPlantType() const override;
    Plant* getPlant() const;
};

#endif