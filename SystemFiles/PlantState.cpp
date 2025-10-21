#include "PlantState.h"

PlantState::PlantState() 
    : context(nullptr), fgrwContext(nullptr), fcheckReadiness(nullptr),
      fharvestContext(nullptr), fgetStateName(""), fisValid(true), 
      fageDataValid(true) {}

PlantState::~PlantState() {}

void PlantState::setContext(PlantContext* ctx) {
    context = ctx;
}