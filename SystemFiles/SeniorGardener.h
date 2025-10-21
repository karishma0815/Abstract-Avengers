/**
 * @file SeniorGardener.h
 * @brief this is the definition of SeniorGardener class for complex plant health issues
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef SENIORGARDENER_H
#define SENIORGARDENER_H

#include "PlantCareHandler.h"

/**
 * @class SeniorGardener
 * @brief this is an experienced plant care handler for moderate to serious plant health issues
 * this class represents senior gardening staff in the Chain of Responsibility pattern for plant care. Senior gardeners handle complex plant health problems
 * the capabilities of junior staff but don't require specialist intervention
 */

class SeniorGardener : public PlantCareHandler{
    public:
        /**
         * @brief this function processes complex plant health issues
         * @param issue this is the plant issue to be handled
         * it diagnoses and treats moderate to high severity plant health problems and it escalates critical plant emergencies to plant specialists
         * when advanced expertise is required
         */
        void handleIssue(const PlantIssue& issue);

        /**
         * @brief this function determines if this handler can process the given plant issue
         * @param issue this is the plant issue to evaluate
         * @return it returns true if this handler can treat the issue otherwise false
         * the senior gardeners handle medium to high severity plant issues but escalate critical emergencies to plant specialists who have
         * advanced expertise for the most complex cases
         */
        bool canHandle(const PlantIssue& issue) const;
};

#endif