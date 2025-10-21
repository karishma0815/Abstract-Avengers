#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H

#include "PlantState.h"

class SeedlingState : public PlantState {
private:
    int daysinState;
    int requestDays;
    bool hasReceivedProperCare;
    int minDaysInState;
    PlantContext* fwaitContext;
    PlantContext* fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    bool fisValid;
    int fgetDaysinState;
    int frequiredDaysInState;

public:
    SeedlingState();
    ~SeedlingState();
    void checkReadiness() ;
    void harvest(PlantContext* ctx) ;
    void grow(PlantContext* ctx) ;
    std::string getStateName();
    bool isValid() ;
    bool ageDataValid() ;
    void wait(PlantContext* ctx);
    int getDaysinState();
    int getRequiredDaysInState();
    void setDaysinState(int days);
    void setRequestDays(int days);
    void setHasReceivedProperCare(bool care);
    void setMinDaysInState(int days);
};

#endif 