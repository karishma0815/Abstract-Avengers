#include "JuniorGardener.h"
#include "PlantIssue.h"
#include <iostream>

void JuniorGardener::handleIssue(const PlantIssue &issue){
    if(canHandle(issue)){
        std::cout << " Junior Gardener handling: " << issue.getDescription() << " (Severity: LOW/MEDIUM)" << std::endl;
    } else if(nextHandler != nullptr){
        std::cout << " Junior Gardener escalating issue to Senior Gardener..." << std::endl;
        nextHandler->handleIssue(issue);
    } else{
        std::cout << " Error: No handler available for: " << issue.getDescription() << std::endl;
    }
}

bool JuniorGardener::canHandle(const PlantIssue &issue) const{
    return issue.getSeverity() <= PlantIssue::MEDIUM;
}
