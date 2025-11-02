/**
 * @file MatureState.h
 * @brief Concrete state class representing the mature stage of a plant
 * @author Rene Reddy
 * @date 26/09/2025
 * 
 * This file defines the MatureState class which represents a fully mature
 * plant. It manages sale readiness evaluation, seasonal considerations,
 * and determines when the plant is prime for sale.
 */

#ifndef MATURESTATE_H
#define MATURESTATE_H

#include "PlantState.h"

/**
 * @class MatureState
 * @brief Represents the mature state in a plant's lifecycle
 * 
 * MatureState represents a fully grown plant that is being evaluated for
 * sale. This state tracks the maturity period, evaluates sale readiness
 * based on season and market conditions, and determines when the plant
 * should transition to the ReadyForSale state.
 */

class MatureState : public PlantState {
private:
    int daysinState;
    bool isPrimeForSale;
    bool isInInSeason;
    std::string maturedStateSeason;
    PlantContext* fwaitContext;
    PlantContext* fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    bool fisValid;
    int fgetDaysinState;
    bool fisPrimeForSale;
    std::string fevaluateSaleReadiness;

public:
    /**
     * @brief Default constructor for MatureState
     */
    MatureState();

    /**
     * @brief Destructor for MatureState
     */
    ~MatureState();

    /**
     * @brief Check if mature plant is ready for sale
     */
    void checkReadiness() ;
    /**
     * @brief Perform harvest operation on mature plant
     * @param ctx Pointer to the plant context
     */
    bool harvest(PlantContext* ctx) ;

    /**
     * @brief Perform growth operation (typically minimal in mature state)
     * @param ctx Pointer to the plant context
     */
    void grow(PlantContext* ctx) ;
    /**
     * @brief Get the name of this state
     * @return String "Mature" or similar identifier
     */
    std::string getStateName() ;

    /**
     * @brief Check if the mature state is valid
     * @return True if state is valid, false otherwise
     */
    bool isValid() ;
    /**
     * @brief Check if age data is valid for this mature state
     * @return True if age data is valid, false otherwise
     */
    bool ageDataValid() ;
    /**
     * @brief Wait operation for mature state
     * @param ctx Pointer to the plant context
     */
    void wait(PlantContext* ctx);

    /**
     * @brief Get the number of days in mature state
     * @return Number of days
     */
    int getDaysinState();

    /**
     * @brief Check if plant is prime for sale
     * @return True if prime for sale, false otherwise
     */
    bool getIsPrimeForSale();

    /**
     * @brief Evaluate sale readiness based on current season
     * @param currentSeason Current season identifier (as integer)
     * @return String describing sale readiness status
     */
    std::string evaluateSaleReadiness(int currentSeason);

    /**
     * @brief Set the number of days in state
     * @param days Number of days to set
     */
    void setDaysinState(int days);
    /**
     * @brief Set whether plant is prime for sale
     * @param prime Prime for sale status
     */
    void setIsPrimeForSale(bool prime);
    /**
     * @brief Set whether plant is in season
     * @param season In-season status to set
     */
    void setIsInInSeason(bool season);

    /**
     * @brief Set the season when plant matured
     * @param season Matured season identifier
     */
    void setMaturedStateSeason(const std::string& season);
};

#endif 