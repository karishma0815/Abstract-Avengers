// Jacaranda.cpp
#include "Jacaranda.h"

Jacaranda::Jacaranda(std::string name, double price, std::string species)
    : Tree(name, price, species) {
}

Jacaranda::~Jacaranda() {
}

std::string Jacaranda::getPlantType() const{
    return "Jacaranda";
}