// Jacaranda.h
#ifndef JACARANDA_H
#define JACARANDA_H
#include "Tree.h"
#include "Plant.h"

class Jacaranda : public Tree {
private:
    Plant* plant;  // Composition relationship with Plant class
public:
    Jacaranda(std::string name, double price, std::string species = "Jacaranda");
    virtual ~Jacaranda();
    std::string getPlantType() const;
    Plant* getPlant() const;
};

#endif