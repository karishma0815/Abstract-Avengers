/**
 * @file PlantSpecialist.h
 * @brief this is the definition of PlantSpecialist class for critical plant health issues
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef PLANTSPECIALIST_H
#define PLANTSPECIALIST_H

#include "PlantCareHandler.h"

/**
 * @class PlantSpecialist
 * @brief it is an expert handler for critical and complex plant health problems
 * this class represents senior specialists in the Chain of Responsibility pattern for plant care. Plant specialists handle the most severe and complex
 * plant health issues, including critical diseases, rare plant problems, and emergency care situations that exceed the capabilities of regular gardening staff
 */

class PlantSpecialist : public PlantCareHandler{
    public:
        /**
         * @brief this function processes critical plant health issues
         * @param issue this is the plant issue to be handled
         * it provides expert diagnosis and treatment for severe plant health problems including complex diseases, critical conditions, and rare plant issues.
         * Serves as the final escalation point in the plant care chain for issues that cannot be resolved by junior or senior gardeners
         */
        void handleIssue(const PlantIssue& issue);

        /**
         * @brief this function determines if this handler can process the given plant issue
         * @param issue this is the the plant issue to evaluate
         * @return it returns true if this handler can treat the issue otherwise false
         * the plant specialists handle only critical severity plant issues that require advanced knowledge and specialized treatment, 
         * less severe issues are handled earlier in the chain.
         */
        bool canHandle(const PlantIssue& issue) const;
};

#endif