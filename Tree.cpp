
#include "Tree.h"

Tree::Tree(std::string name, double price, std::string species)
    : TreeProduct(name, price), species(species) {
}

Tree::~Tree() {
}

int Tree::getCount() const {
    return 1;
}

std::string Tree::getSpecies() const {
    return species;
}

double Tree::getTotalValue() const {
    return price;
}