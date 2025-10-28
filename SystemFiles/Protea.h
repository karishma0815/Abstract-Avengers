// Protea.h
#ifndef PROTEA_H
#define PROTEA_H
#include "Flower.h"

class Protea : public Flower {
public:
    Protea(std::string name, double price, std::string species = "Protea");
    ~Protea();
    std::string getPlantType() const override;
};

#endif