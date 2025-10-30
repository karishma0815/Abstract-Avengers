// Rose.cpp
#include "Rose.h"
#include "Plant.h"

Rose::Rose(std::string name, double price, std::string species)
    : Flower(name, price, species) {
              //  plant = new Plant(name, false, "ROSE_", std::to_string(rand()), 6, 3);

}

Rose::~Rose() {
    delete plant;
}

std::string Rose::getPlantType() const {
    return "Rose";
}

Plant* Rose::getPlant() {
    return plant;
}