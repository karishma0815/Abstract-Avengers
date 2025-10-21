/**
 * @file PlantCareHandler.h
 * @brief this is the definition of PlantCareHandler class for Chain of Responsibility pattern
 * @author Karishma Boodhoo
 * @date 13-10-2025
 */

#ifndef PLANTCAREHANDLER_H
#define PLANTCAREHANDLER_H

class PlantIssue;

/**
 * @class PlantCareHandler
 * @brief this is an abstract base class for handling plant health issues in Chain of Responsibility pattern
 * This class defines the interface for handlers in the plant care escalation chain.
 * Each concrete handler decides whether it can process a plant health issue or should pass it to the next handler in the chain. This allows routing of plant
 * care problems to the most appropriate gardening staff based on expertise levels and issue severity.
 */

class PlantCareHandler{
    protected:
        PlantCareHandler* nextHandler;
    public:
        /**
         * @brief this is a constructor that constructs a PlantCareHandler
         */
        PlantCareHandler();

        /**
         * @brief this is a virtual destructor for cleanup of derived classes
         */
        virtual ~PlantCareHandler();

        /**
         * @brief this function sets the next handler in the plant care chain
         * @param handler this is a pointer to the next handler to receive unhandled plant issues
         * it establishes the next handler in the responsibility chain. If this handler cannot process a plant health issue, 
         * it will be passed to the specified next handler for further evaluation
         */
        void setNext(PlantCareHandler* handler);

        /**
         * @brief this function processes a plant health issue
         * @param issue this is the plant health issue to handle
         * it attempts to diagnose and treat the plant health issue. If this handler
         * cannot resolve the issue, it passes the issue to the next handler in the chain if one exists.
         */
        virtual void handleIssue(const PlantIssue& issue) = 0;

        /**
         * @brief this function determines if this handler can process the given plant issue
         * @param issue this is the plant health issue to check
         * @return it returns true if this handler can treat the issue otherwise false
         * Each concrete handler implements this method to decide whether it has the expertise and resources to handle the specific type and severity
         * of plant health problem
         */
        virtual bool canHandle(const PlantIssue& issue) const = 0;
};

#endif