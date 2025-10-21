#ifndef PLANTSTATE_H
#define PLANTSTATE_H

#include <string>

class PlantContext;

class PlantState {
protected:
    PlantContext* context;
    PlantContext* fgrwContext;
    PlantContext* fcheckReadiness;
    PlantContext* fharvestContext;
    std::string fgetStateName;
    bool fisValid;
    bool fageDataValid;

public:
    PlantState();
    virtual ~PlantState();
    virtual void checkReadiness() = 0;
    virtual void harvest(PlantContext* ctx) = 0;
    virtual void grow(PlantContext* ctx) = 0;
    virtual std::string getStateName() = 0;
    virtual bool isValid() = 0;
    virtual bool ageDataValid() = 0;
    void setContext(PlantContext* ctx);
};

#endif 