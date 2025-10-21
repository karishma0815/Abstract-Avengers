#ifndef SOLDSTATE_H
#define SOLDSTATE_H

#include "PlantState.h"

class SoldState : public PlantState {
private:
    std::string saleDte;
    double soldPrice;
    std::string soldSeason;
    double fsoldSequence;
    std::string fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    double fgetSoldPrice;
    std::string fgetData;

public:
    SoldState();
    ~SoldState();
    void checkReadiness() ;
    void harvest(PlantContext* ctx) ;
    void grow(PlantContext* ctx) ;
    std::string getStateName() ;
    bool isValid() ;
    bool ageDataValid() ;
    double soldSequence(double price, std::string date, std::string season);
    double getSoldPrice();
    std::string getData();
    void setSaleDte(const std::string& date);
    void setSoldPrice(double price);
    void setSoldSeason(const std::string& season);
};

#endif