#include"WaterRecomm.h"

WaterRecomm::WaterRecomm(){}

WaterRecomm::~WaterRecomm(){}

void WaterRecomm::recommend(){
    std::cout<<" Recommendation Strategy: Watering Needs\n";
    std::cout<<"  1. Low Water Plants:\n";
    std::cout<<"   Succulents\n";
    std::cout<<"   Cacti\n";
    std::cout<<"   ZZ Plant \n\n";

    std::cout<<"  2. Medium Water Plant:\n";
    std::cout<<"   Spider Plant\n";
    std::cout<<"   Pothos\n";
    std::cout<<"   Peace Lily\n\n";

    std::cout<<"  3. High Water Plants: \n";
    std::cout<<"   Ferns\n";
    std::cout<<"   Calatheas\n";
    std::cout<<"   Boston Fern\n\n";
}