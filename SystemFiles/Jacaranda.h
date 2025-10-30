// Jacaranda.h
#ifndef JACARANDA_H
#define JACARANDA_H
#include "Tree.h"

class Jacaranda : public Tree {
public:
    Jacaranda(std::string name, double price, std::string species = "Jacaranda");
    ~Jacaranda();
    std::string getPlantType() const;
};

#endif