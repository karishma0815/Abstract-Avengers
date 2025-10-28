// Jade.h
#ifndef JADE_H
#define JADE_H
#include "Succulent.h"

class Jade : public Succulent {
public:
    Jade(std::string name, double price, std::string species = "Jade Plant");
    ~Jade();
    std::string getPlantType() const override;
};

#endif