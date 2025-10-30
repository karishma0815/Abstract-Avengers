// Cacti.h
#ifndef CACTI_H
#define CACTI_H
#include "Succulent.h"

class Cacti : public Succulent {
public:
    Cacti(std::string name, double price, std::string species = "Cacti");
    ~Cacti();
    std::string getPlantType() const override;
};

#endif