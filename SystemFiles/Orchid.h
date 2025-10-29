// Orchid.h
#ifndef ORCHID_H
#define ORCHID_H
#include "Succulent.h"
#include "Plant.h"

class Orchid : public Succulent {
private:
    Plant* plant;  
public:
    Orchid(std::string name, double price, std::string species = "Orchid");
    virtual ~Orchid();
    std::string getPlantType() const override;
    Plant* getPlant() const;
};

#endif