/**
 * @file SoldState.h
 * @brief Concrete state class representing a sold plant (terminal state)
 * @author Rene Reddy
 * @date 26/09/2025
 * 
 * This file defines the SoldState class which represents the final state
 * in a plant's lifecycle after it has been sold. It records the sale
 * transaction details including date, price, and season.
 */

#ifndef SOLDSTATE_H
#define SOLDSTATE_H

#include "PlantState.h"

/**
 * @class SoldState
 * @brief Represents the sold state in a plant's lifecycle (terminal state)
 * 
 * SoldState is the final state in the plant lifecycle, reached after a
 * successful sale. This state records transaction information including
 * the sale date, final price, and season. Once in this state, no further
 * transitions occur as the plant has left the system.
 */

class SoldState : public PlantState {
private:
    std::string saleDte;
    double soldPrice;
    std::string soldSeason;
    double fsoldSequence;
    std::string fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    double fgetSoldPrice;
    std::string fgetData;

public:

    /**
     * @brief Default constructor for SoldState
     */
    SoldState();
   
    /**
     * @brief Destructor for SoldState
     */
    ~SoldState();

  /**
     * @brief Check readiness (no operation in sold state)
     */
    void checkReadiness() ;

     /**
     * @brief Perform harvest operation (no operation in sold state)
     * @param ctx Pointer to the plant context
     */
    bool harvest(PlantContext* ctx) ;

     /**
     * @brief Perform growth operation (no operation in sold state)
     * @param ctx Pointer to the plant context
     */
    void grow(PlantContext* ctx) ;
    /**
     * @brief Get the name of this state
     * @return String "Sold" or similar identifier
     */
    std::string getStateName() ;

    /**
     * @brief Check if the sold state is valid
     * @return True if state is valid, false otherwise
     */
    bool isValid() ;

     /**
     * @brief Check if age data is valid for this state
     * @return True if age data is valid, false otherwise
     */
    bool ageDataValid() ;

     /**
     * @brief Process the sale sequence with transaction details
     * @param price Final sale price
     * @param date Sale date
     * @param season Season when sold
     * @return Sequence number or transaction identifier
     */
    double soldSequence(double price, std::string date, std::string season);

     /**
     * @brief Get the final sold price
     * @return Sold price value
     */
    double getSoldPrice();

    /**
     * @brief Get the sale transaction data
     * @return String containing sale data
     */
    std::string getData();

     /**
     * @brief Set the sale date
     * @param date Sale date string
     */
    void setSaleDte(const std::string& date);

    /**
     * @brief Set the sold price
     * @param price Final sale price
     */
    void setSoldPrice(double price);

     /**
     * @brief Set the season when sold
     * @param season Season identifier
     */
    void setSoldSeason(const std::string& season);
};

#endif