// Cacti.h
#ifndef CACTI_H
#define CACTI_H
#include "Succulent.h"
#include "Plant.h"

class Cacti : public Succulent {
private:
    Plant* plant;
public:
    Cacti(std::string name, double price, std::string species = "Cacti");
    virtual ~Cacti();
    std::string getPlantType() const override;
    Plant* getPlant() const;

};

#endif