/**
 * @file ReadyForSaleState.h
 * @brief Concrete state class representing a plant ready for sale
 * @author Rene Reddy
 * @date 26/09/2025
 * 
 * This file defines the ReadyForSaleState class which represents a plant
 * that has been prepared and is ready to be sold. It manages pricing,
 * seasonal information, and sale preparation.
 */

#ifndef READYFORSALESTATE_H
#define READYFORSALESTATE_H

#include "PlantState.h"

/**
 * @class ReadyForSaleState
 * @brief Represents the ready-for-sale state in a plant's lifecycle
 * 
 * ReadyForSaleState represents a plant that has been evaluated, priced,
 * and prepared for sale. This state manages the final sale preparation,
 * tracks how long the plant has been available for sale, and handles
 * the transition to the sold state.
 */

class ReadyForSaleState : public PlantState {
private:
    int daysinState;
    double price;
    std::string season;
    std::string prepareSale;
    PlantContext* fwaitContext;
    PlantContext* fgrwContext;
    PlantContext* fharvestContext;
    PlantContext* fcheckReadiness;
    std::string fgetStateName;
    bool fisValid;
    int fgetDaysinState;
    double fgetPrice;

public:
/**
     * @brief Default constructor for ReadyForSaleState
     */

    ReadyForSaleState();

    /**
     * @brief Destructor for ReadyForSaleState
     */
    ~ReadyForSaleState();
     /**
     * @brief Check if plant is still ready for sale (not expired)
     */
    void checkReadiness() ;
     /**
     * @brief Perform harvest/sale operation, transitioning to sold state
     * @param ctx Pointer to the plant context
     */
    bool harvest(PlantContext* ctx) ;
     /**
     * @brief Perform growth operation (typically none in ready-for-sale state)
     * @param ctx Pointer to the plant context
     */
    void grow(PlantContext* ctx) ;
    /**
     * @brief Get the name of this state
     * @return String "ReadyForSale" or similar identifier
     */
    std::string getStateName() ;
    /**
     * @brief Check if the ready-for-sale state is valid
     * @return True if state is valid, false otherwise
     */
    bool isValid() ;

   /**
     * @brief Check if age data is valid for this state
     * @return True if age data is valid, false otherwise
     */ 
    bool ageDataValid() ;
    /**
     * @brief Wait operation for ready-for-sale state
     * @param ctx Pointer to the plant context
     */
    void wait(PlantContext* ctx);
    /**
     * @brief Get the number of days in ready-for-sale state
     * @return Number of days
     */
    int getDaysinState();
    /**
     * @brief Get the sale price of the plant
     * @return Price value
     */
    double getPrice();

    /**
     * @brief Prepare the plant for sale with pricing and season info
     * @param priceVal Price to set for the plant
     * @param seasonVal Season identifier
     * @return String describing sale preparation status
     */
    std::string prepareSaleForSale(double priceVal, std::string seasonVal);
    /**
     * @brief Set the number of days in state
     * @param days Number of days to set
     */
    void setDaysinState(int days);

    /**
     * @brief Set the sale price
     * @param p Price value to set
     */
    void setPrice(double p);

    /**
     * @brief Set the season
     * @param s Season identifier to set
     */
    void setSeason(const std::string& s);

     /**
     * @brief Set the sale preparation status
     * @param prep Preparation status string
     */
    void setPrepareSale(const std::string& prep);
};

#endif