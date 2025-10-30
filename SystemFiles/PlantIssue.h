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
        
        /**
         * @brief this is a constructor that constructs a PlantIssue with specified parameters
         * @param severity this is the urgency level of the plant health problem
         * @param description this is the detailed description of the issue symptoms
         * @param plant this is a pointer to the plant experiencing the health problem
         * itcCreates a new plant issue object that can be processed through the Chain of Responsibility pattern by various gardening staff
         * members based on their expertise and the issue severity
         */
        PlantIssue(Severity severity, const std::string& description, Plant* plant);

        /**
         * @brief this function gets the severity level of the plant issue
         * @return the PlantIssue::Severity this is the severity level (LOW, MEDIUM, HIGH, or CRITICAL)
         * This method returns the urgency level of the plant health problem, which determines which staff member in the chain of responsibility should handle the issue
         */
        Severity getSeverity() const { return severity; }

        /**
         * @brief this function gets the detailed description of the plant issue
         * @return std::string A descriptive text explaining the symptoms and nature of the problem
         * This method provides a human-readable description of the plant health issue
         */
        std::string getDescription() const { return description; }

        /**
         * @brief this function gets the plant associated with this issue
         * @return this is a Plant* pointer to the plant experiencing the health problem
         * This method returns a pointer to the plant object that is affected by this issue or it returns null if no plant is associated with the problem
         */
        Plant* getPlant() const { return plant; }

    private:
        Severity severity;
        std::string description;
        Plant* plant;
};

#endif