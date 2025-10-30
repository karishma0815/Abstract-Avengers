#ifndef JACARANDA_H
#define JACARANDA_H
#include "Tree.h"

class Jacaranda : public Tree {
public:
    Jacaranda(std::string name, double price, std::string species = "Jacaranda");
    virtual ~Jacaranda();
    std::string getPlantType() const override;
};

#endif