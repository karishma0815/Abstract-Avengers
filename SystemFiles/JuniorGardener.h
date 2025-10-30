/**
 * @file JuniorGardener.h
 * @brief this is the definition of JuniorGardener class for basic plant care issue handling
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef JUNIORGARDENER_H
#define JUNIORGARDENER_H

#include "PlantCareHandler.h"

/**
 * @class JuniorGardener
 * @brief this is the entry level plant care handler for basic plant health issues
 * This class represents junior gardening staff in the Chain of Responsibility pattern for plant care. Junior gardeners handle routine plant maintenance
 * issues and escalate more complex problems to senior staff members. They serve as the first point of contact in the chain
 */

class JuniorGardener : public PlantCareHandler{
    public:
        /**
         * @brief this function processes plant health issues within the handlers expertise
         * @param issue this is the plant issue to be handled
         * it attempts to resolve basic plant care issues. If the issue exceeds the junior gardener's capabilities, 
         * it is passed to the next handler in the plant care chain
         */
        void handleIssue(const PlantIssue& issue);

        /**
         * @brief this function determines if this handler can process the given plant issue
         * @param issue this is the plant issue to evaluate
         * @return this is true if this handler can resolve the issue otherwise false
         * Junior gardeners can handle low to medium severity plant issues such as routine watering needs, basic pruning, and minor nutrient
         * deficiencies. Complex health issues are escalated to more experienced staff
         */
        bool canHandle(const PlantIssue& issue) const;
};

#endif