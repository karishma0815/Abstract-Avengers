#include "SucculentProduct.h"

SucculentProduct::SucculentProduct(std::string name, double price) 
    : name(name), price(price) {
}

SucculentProduct::~SucculentProduct() {
}

std::string SucculentProduct::getPlantType() const {
    return "Succulent";
}

std::string SucculentProduct::getName() const {
    return name;
}

void SucculentProduct::add(SucculentProduct* plant) {
    // Default implementation - does nothing for leaves
}

void SucculentProduct::remove(SucculentProduct* plant) {
    // Default implementation - does nothing for leaves
}