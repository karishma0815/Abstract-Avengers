// Orchid.h
#ifndef ORCHID_H
#define ORCHID_H
#include "Succulent.h"

class Orchid : public Succulent {
public:
    Orchid(std::string name, double price, std::string species = "Orchid");
    ~Orchid();
    std::string getPlantType() const override;
};

#endif