// Jade.cpp
#include "Jade.h"
#include "Plant.h"

Jade::Jade(std::string name, double price, std::string species)
    : Succulent(name, price, species) {
          // plant = new Plant(name, false, "JADE_" + std::to_string(rand() % 1000), 5, 2);

}

Jade::~Jade() {
    delete plant;
}

std::string Jade::getPlantType() const {
    return "Jade";
}

Plant* Jade::getPlant() const {
    return plant;
}