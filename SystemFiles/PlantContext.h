#ifndef PLANTCONTEXT_H
#define PLANTCONTEXT_H

#include "Plant.h"
#include <string>

class PlantState;

class PlantContext {
private:
    PlantState* currentState;
    std::string fplantType;
    std::string season;
    double fstateAge;
    double fstatPrice;
    Plant* plant;  

public:
    PlantContext(std::string type, std::string season, std::string species, double price);
    ~PlantContext();
    void transitionTo(PlantState* state);
    PlantState* getState();
    void harvest();
    void checkReadiness();
    void ingestPlantType(std::string type, PlantState* state);
    void ageState(int daysToAge);
    int getAge();
    double getStateAgePrice();
    std::string getPlantName();
    std::string getPlantType();
    std::string getSeason();
    std::string getCurrentStateName();
    bool isReadyForSale();
    Plant* getPlant();
    void setPlantType(const std::string& type);
    void setStateAge(double age);
    void setSeason(const std::string& s);
    void setStatePrice(double price);
};

#endif