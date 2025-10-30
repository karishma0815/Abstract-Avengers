/**
 * @file SeedlingState.h
 * @brief Concrete state class representing the seedling stage of a plant
 * @author Rene Reddy
 * @date 26/09/2025
 * 
 * This file defines the SeedlingState class which represents the initial
 * growth stage of a plant. It manages seedling-specific attributes like
 * days in state, care status, and minimum required days.
 */

#ifndef SEEDLINGSTATE_H
#define SEEDLINGSTATE_H

#include "PlantState.h"

/**
 * @class SeedlingState
 * @brief Represents the seedling state in a plant's lifecycle
 * 
 * SeedlingState is the initial growth state where a plant requires specific
 * care and must remain for a minimum number of days. This state tracks
 * the duration in state, care received, and determines when the plant is
 * ready to transition to the next growth stage.
 */
class SeedlingState : public PlantState {
private:
    int daysinState;
    int requestDays;
    bool hasReceivedProperCare;
    int minDaysInState;
    PlantContext* fwaitContext;
    PlantContext* fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    bool fisValid;
    int fgetDaysinState;
    int frequiredDaysInState;

public:
/**
     * @brief Default constructor for SeedlingState
     */
    SeedlingState();
    /**
     * @brief Destructor for SeedlingState
     */
    ~SeedlingState();

    /**
     * @brief Check if seedling is ready to transition to next state
     */
    void checkReadiness() ;
    /**
     * @brief Perform harvest operation (typically not allowed in seedling state)
     * @param ctx Pointer to the plant context
     */
    void harvest(PlantContext* ctx) ;
    /**
     * @brief Perform growth operation on the seedling
     * @param ctx Pointer to the plant context
     */
    void grow(PlantContext* ctx) ;
     /**
     * @brief Get the name of this state
     * @return String "Seedling" or similar identifier
     */
    std::string getStateName();
     /**
     * @brief Check if the seedling state is valid
     * @return True if state is valid, false otherwise
     */
    bool isValid() ;
      /**
     * @brief Check if age data is valid for this seedling
     * @return True if age data is valid, false otherwise
     */
    bool ageDataValid() ;
     /**
     * @brief Wait operation for seedling state
     * @param ctx Pointer to the plant context
     */
    void wait(PlantContext* ctx);
    /**
     * @brief Get the number of days in seedling state
     * @return Number of days
     */
    int getDaysinState();
    /**
     * @brief Get the required number of days in state
     * @return Required days
     */
    int getRequiredDaysInState();
    /**
     * @brief Set the number of days in state
     * @param days Number of days to set
     */
    void setDaysinState(int days);
     /**
     * @brief Set the requested number of days
     * @param days Requested days to set
     */
    void setRequestDays(int days);
    /**
     * @brief Set whether proper care has been received
     * @param care Care status to set
     */
    void setHasReceivedProperCare(bool care);
    
    /**
     * @brief Set the minimum required days in state
     * @param days Minimum days to set
     */
    void setMinDaysInState(int days);
};

#endif 