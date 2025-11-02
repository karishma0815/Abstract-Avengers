#include "PlantSpecialist.h"
#include "PlantIssue.h"
#include <iostream>

void PlantSpecialist::handleIssue(const PlantIssue &issue){
    if(canHandle(issue)){
        std::cout << " Plant Specialist handling CRITICAL issue: " << issue.getDescription() << " (Severity: CRITICAL)" << std::endl;
    } else{
        std::cout << " Error: Plant Specialist cannot handle this issue severity: " << issue.getDescription() << std::endl;
    }
}

bool PlantSpecialist::canHandle(const PlantIssue &issue) const{
    return issue.getSeverity() == PlantIssue::CRITICAL;
}
