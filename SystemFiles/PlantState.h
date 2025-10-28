/**
 * @file PlantState.h
 * @brief Base abstract class for plant state management in the State pattern
 * @author Rene Reddy
 * @date 26/09/2025
 * 
 * This file defines the PlantState abstract base class which represents different
 * states in a plant's lifecycle. It follows the State design pattern to manage
 * plant behavior transitions.
 */

#ifndef PLANTSTATE_H
#define PLANTSTATE_H

#include <string>

class PlantContext;

/**
 * @class PlantState
 * @brief Abstract base class representing a state in a plant's lifecycle
 * 
 * This class defines the interface for all concrete plant states. Each state
 * implements specific behavior for operations like growing, harvesting, and
 * checking readiness. The class maintains references to the plant context
 * and provides common functionality for state validation.
 */

class PlantState {
protected:
    PlantContext* context;
    PlantContext* fgrwContext;
    PlantContext* fcheckReadiness;
    PlantContext* fharvestContext;
    std::string fgetStateName;
    bool fisValid;
    bool fageDataValid;

public:
/**
     * @brief Default constructor
     */
    PlantState();
   /**
     * @brief Virtual destructor
     */ 
    virtual ~PlantState();
    /**
     * @brief Check if the plant is ready for the next state transition
     * @pure
     */
    virtual void checkReadiness() = 0;
    /**
     * @brief Perform harvest operation on the plant
     * @param ctx Pointer to the plant context
     * @pure
     */
    virtual void harvest(PlantContext* ctx) = 0;

     /**
     * @brief Perform growth operation on the plant
     * @param ctx Pointer to the plant context
     * @pure
     */
    virtual void grow(PlantContext* ctx) = 0;

    /**
     * @brief Get the name of the current state
     * @return String representing the state name
     * @pure
     */
    virtual std::string getStateName() = 0;
    /**
     * @brief Check if the current state is valid
     * @return True if state is valid, false otherwise
     * @pure
     */
    virtual bool isValid() = 0;
     /**
     * @brief Check if the age data for this state is valid
     * @return True if age data is valid, false otherwise
     * @pure
     */
    virtual bool ageDataValid() = 0;
    /**
     * @brief Set the plant context for this state
     * @param ctx Pointer to the plant context to set
     */
    void setContext(PlantContext* ctx);
};

#endif 