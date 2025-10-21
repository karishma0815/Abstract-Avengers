#include "JuniorGardener.h"
#include "PlantIssue.h"
#include <iostream>

void JuniorGardener::handleIssue(const PlantIssue &issue){
    return issue.severity <= PlantIssue::MEDIUM;
}

bool JuniorGardener::canHandle(const PlantIssue &issue) const{
    if(canHandle(issue)){
        std::cout<<"Junior Gardener handling: " << issue.description<<" (Severity: LOW/MEDIUM)"<<std::endl;
    } else if(nextHandler != nullptr){
        std::cout<<"Junior Gardener escalating issue to Senior Gardener..."<<std::endl;
        nextHandler->handleIssue(issue);
    } else{
        std::cout<<"Error: No handler available for: "<<issue.description<<std::endl;
    }
}
