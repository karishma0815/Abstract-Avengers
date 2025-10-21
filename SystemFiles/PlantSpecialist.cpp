#include "PlantSpecialist.h"
#include "PlantIssue.h"
#include <iostream>

void PlantSpecialist::handleIssue(const PlantIssue &issue){
    return issue.severity == PlantIssue::CRITICAL;
}

bool PlantSpecialist::canHandle(const PlantIssue &issue) const{
    if(canHandle(issue)){
        std::cout<<"Plant Specialist handling CRITICAL issue: "<<issue.description<<" (Severity: CRITICAL)"<<std::endl;
    } else{
        std::cout<<"Error: Plant Specialist cannot handle this issue severity: "<<issue.description<<std::endl;
    }
}
