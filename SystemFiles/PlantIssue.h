/**
 * @file PlantIssue.h
 * @brief this is thedDefinition of PlantIssue class for representing plant health problems
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef PLANTISSUE_H
#define PLANTISSUE_H

#include <string>

class Plant;

/**
 * @class PlantIssue
 * @brief it represents a plant health problem or maintenance requirement
 * This class encapsulates plant health issues with their severity level, description, and associated plant. It serves as the Request object in
 * the Chain of Responsibility pattern for plant care, flowing through different gardening staff handlers until an appropriate expert processes it
 */

class PlantIssue{
    public:
        /**
         * @brief this is the enumeration of plant issue severity levels
         * it defines the urgency and complexity levels of plant health problems that determine which staff member should handle them in the plant
         * care escalation chain
         */
        enum Severity { LOW, MEDIUM, HIGH, CRITICAL };
        Severity severity;
        std::string description;
        Plant* plant;
        
        /**
         * @brief this is a constructor that constructs a PlantIssue with specified parameters
         * @param severity this is the urgency level of the plant health problem
         * @param description this is the detailed description of the issue symptoms
         * @param plant this is a pointer to the plant experiencing the health problem
         * itcCreates a new plant issue object that can be processed through the Chain of Responsibility pattern by various gardening staff
         * members based on their expertise and the issue severity
         */
        PlantIssue(Severity severity, const std::string& description, Plant* plant);
};

#endif