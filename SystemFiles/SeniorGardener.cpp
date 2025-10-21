#include "SeniorGardener.h"
#include "PlantIssue.h"
#include <iostream>

void SeniorGardener::handleIssue(const PlantIssue &issue){
    return issue.severity == PlantIssue::HIGH;
}

bool SeniorGardener::canHandle(const PlantIssue &issue) const{
    if(canHandle(issue)){
        std::cout<<"Senior Gardener handling: "<<issue.description<<" (Severity: HIGH)"<<std::endl;
    } else if(nextHandler != nullptr){
        std::cout<<"Senior Gardener escalating CRITICAL issue to Plant Specialist..."<<std::endl;
        nextHandler->handleIssue(issue);
    } else{
        std::cout<<"Error: No specialist available for CRITICAL issue: "<<issue.description<<std::endl;
    }
}
