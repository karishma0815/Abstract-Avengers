/**
 * @file FloweringState.h
 * @brief Concrete state class representing the flowering stage of a plant
 * @author Rene Reddy
 * @date 26/09/2025
 * 
 * This file defines the FloweringState class which represents the flowering
 * growth stage. It manages season-dependent flowering attributes and tracks
 * the duration and readiness of the flowering period.
 */

#ifndef FLOWERINGSTATE_H
#define FLOWERINGSTATE_H

#include "PlantState.h"
/**
 * @class FloweringState
 * @brief Represents the flowering state in a plant's lifecycle
 * 
 * FloweringState manages the flowering period of a plant, tracking seasonal
 * dependencies, days in flowering state, and determining readiness for
 * transition to the next state. Flowering is often season-dependent and
 * requires specific conditions to be met.
 */
class FloweringState : public PlantState {
private:
    int daysinState;
    int requestDays;
    bool isInSeason;
    std::string currentSeason;
    std::string floweringStrtSeason;
    PlantContext* fwaitContext;
    PlantContext* fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    bool fisValid;
    int fgetDaysinState;
    bool fisinSeason;
    int fincreaseDay;

public:

    /**
     * @brief Default constructor for FloweringState
     */
    FloweringState();

     /**
     * @brief Destructor for FloweringState
     */
    ~FloweringState();
    /**
     * @brief Check if plant is ready to transition from flowering state
     */
    void checkReadiness() ;
    /**
     * @brief Perform harvest operation during flowering
     * @param ctx Pointer to the plant context
     */
    void harvest(PlantContext* ctx) ;

     /**
     * @brief Perform growth operation during flowering
     * @param ctx Pointer to the plant context
     */
    void grow(PlantContext* ctx) ;
    /**
     * @brief Get the name of this state
     * @return String "Flowering" or similar identifier
     */
    std::string getStateName() ;
    /**
     * @brief Check if the flowering state is valid
     * @return True if state is valid, false otherwise
     */
    bool isValid() ;

    /**
     * @brief Check if age data is valid for this flowering state
     * @return True if age data is valid, false otherwise
     */
    bool ageDataValid();

    /**
     * @brief Wait operation for flowering state
     * @param ctx Pointer to the plant context
     */
    void wait(PlantContext* ctx);

    /**
     * @brief Get the number of days in flowering state
     * @return Number of days
     */
    int getDaysinState();

    
    /**
     * @brief Check if plant is in flowering season
     * @return True if in season, false otherwise
     */
    bool getIsInSeason();
    /**
     * @brief Increment the day counter for flowering state
     */
    void increaseDay();

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
     * @brief Set whether plant is in flowering season
     * @param season Season status to set
     */
    void setIsInSeason(bool season);
    /**
     * @brief Set the current season
     * @param season Season identifier to set
     */
    void setCurrentSeason(const std::string& season);
    /**
     * @brief Set the season when flowering started
     * @param season Starting season identifier
     */
    void setFloweringStrtSeason(const std::string& season);
};

#endif 