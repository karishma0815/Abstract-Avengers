#include "PlantIssue.h"

PlantIssue::PlantIssue(Severity severity, const std::string &description, Plant *plant) : severity(severity), description(description), plant(plant){
    
}

