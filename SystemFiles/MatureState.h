#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantState.h"

class MatureState : public PlantState {
private:
    int daysinState;
    bool isPrimeForSale;
    bool isInInSeason;
    std::string maturedStateSeason;
    PlantContext* fwaitContext;
    PlantContext* fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    bool fisValid;
    int fgetDaysinState;
    bool fisPrimeForSale;
    std::string fevaluateSaleReadiness;

public:
    MatureState();
    ~MatureState();
    void checkReadiness() ;
    void harvest(PlantContext* ctx) ;
    void grow(PlantContext* ctx) ;
    std::string getStateName() ;
    bool isValid() ;
    bool ageDataValid() ;
    void wait(PlantContext* ctx);
    int getDaysinState();
    bool getIsPrimeForSale();
    std::string evaluateSaleReadiness(int currentSeason);
    void setDaysinState(int days);
    void setIsPrimeForSale(bool prime);
    void setIsInInSeason(bool season);
    void setMaturedStateSeason(const std::string& season);
};

#endif 