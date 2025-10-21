#include "Gardener.h"
#include <iostream>

Gardener::Gardener(const std::string &name, int id, InventoryMediator *med, const std::string &expertise) : Staff(name, id, med), expertise(expertise){

}

std::string Gardener::getRole() const{
    return "Gardener (" + expertise + ")";
}

void Gardener::careForPlants(){
    std::cout<<getName()<<" is caring for plants with expertise in "<<expertise<<std::endl;
}


