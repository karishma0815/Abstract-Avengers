#ifndef READYFORSALESTATE_H
#define READYFORSALESTATE_H

#include "PlantState.h"

class ReadyForSaleState : public PlantState {
private:
    int daysinState;
    double price;
    std::string season;
    std::string prepareSale;
    PlantContext* fwaitContext;
    PlantContext* fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    bool fisValid;
    int fgetDaysinState;
    double fgetPrice;

public:
    ReadyForSaleState();
    ~ReadyForSaleState();
    void checkReadiness() ;
    void harvest(PlantContext* ctx) ;
    void grow(PlantContext* ctx) ;
    std::string getStateName() ;
    bool isValid() ;
    bool ageDataValid() ;
    void wait(PlantContext* ctx);
    int getDaysinState();
    double getPrice();
    std::string prepareSaleForSale(double priceVal, std::string seasonVal);
    void setDaysinState(int days);
    void setPrice(double p);
    void setSeason(const std::string& s);
    void setPrepareSale(const std::string& prep);
};

#endif