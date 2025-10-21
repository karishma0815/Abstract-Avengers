#ifndef FLOWERINGSTATE_H
#define FLOWERINGSTATE_H

#include "PlantState.h"

class FloweringState : public PlantState {
private:
    int daysinState;
    int requestDays;
    bool isInSeason;
    std::string currentSeason;
    std::string floweringStrtSeason;
    PlantContext* fwaitContext;
    PlantContext* fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    bool fisValid;
    int fgetDaysinState;
    bool fisinSeason;
    int fincreaseDay;

public:
    FloweringState();
    ~FloweringState();
    void checkReadiness() ;
    void harvest(PlantContext* ctx) ;
    void grow(PlantContext* ctx) ;
    std::string getStateName() ;
    bool isValid() ;
    bool ageDataValid();
    void wait(PlantContext* ctx);
    int getDaysinState();
    bool getIsInSeason();
    void increaseDay();
    void setDaysinState(int days);
    void setRequestDays(int days);
    void setIsInSeason(bool season);
    void setCurrentSeason(const std::string& season);
    void setFloweringStrtSeason(const std::string& season);
};

#endif 