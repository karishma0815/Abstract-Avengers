/**
 * @file PlantContext.h
 * @brief Context class managing plant state transitions and plant information
 * @author Rene Reddy
 * @date 26/09/2025
 * 
 * This file defines the PlantContext class which serves as the context in the
 * State design pattern. It manages the current state of a plant, handles state
 * transitions, and maintains plant-specific data.
 */

#ifndef PLANTCONTEXT_H
#define PLANTCONTEXT_H

#include "Plant.h"
#include <string>

class PlantState;
/**
 * @class PlantContext
 * @brief Context class that maintains plant state and coordinates state transitions
 * 
 * PlantContext is the main coordinator for plant lifecycle management. It maintains
 * a reference to the current state, delegates state-specific operations to the
 * current state object, and manages plant attributes like type, season, age, and price.
 */
class PlantContext {
private:
    PlantState* currentState;
    std::string fplantType;
    std::string season;
    double fstateAge;
    double fstatPrice;
    Plant* plant;  

public:

    /**
     * @brief Construct a new PlantContext object
     * @param plantInstance Pointer to a concrete Plant object (e.g., Rose, Tulip)
     * @param type Plant type identifier
     * @param season Current season
     * @param price Initial price of the plant
     */
    PlantContext(const std::string& type, const std::string& name, double price, const std::string& species);


     /**
     * @brief Destructor that cleans up allocated resources
     */
    ~PlantContext();
    /**
     * @brief Transition to a new plant state
     * @param state Pointer to the new state to transition to
     */
    void transitionTo(PlantState* state);
    /**
     * @brief Get the current state of the plant
     * @return Pointer to the current PlantState object
     */
    PlantState* getState();

    /**
     * @brief Delegate harvest operation to the current state
     */
    void harvest();
     /**
     * @brief Delegate readiness check to the current state
     */
    void checkReadiness();
    /**
     * @brief Ingest plant type and update state accordingly
     * @param type Plant type to ingest
     * @param state State to update with the plant type
     */
    void ingestPlantType(std::string type, PlantState* state);

    /**
     * @brief Age the plant by a specified number of days
     * @param daysToAge Number of days to age the plant
     */
    void ageState(int daysToAge);

     /**
     * @brief Get the current age of the plant
     * @return Age in days
     */
    int getAge();
    /**
     * @brief Get the price associated with the current state and age
     * @return Price value
     */
    double getStateAgePrice();
    /**
     * @brief Get the name of the plant
     * @return Plant name as string
     */
    std::string getPlantName();
     /**
     * @brief Get the type of the plant
     * @return Plant type as string
     */
    std::string getPlantType();
    /**
     * @brief Get the current season
     * @return Season as string
     */
    std::string getSeason();
    
    /**
     * @brief Get the name of the current state
     * @return Current state name as string
     */
    std::string getCurrentStateName();
    /**
     * @brief Check if the plant is ready for sale
     * @return True if ready for sale, false otherwise
     */
    bool isReadyForSale();
     /**
     * @brief Get the Plant object associated with this context
     * @return Pointer to the Plant object
     */
    Plant* getPlant();
    /**
     * @brief Set the plant type
     * @param type Plant type to set
     */
    void setPlantType(const std::string& type);
    /**
     * @brief Set the state age
     * @param age Age value to set
     */
    void setStateAge(double age);
    /**
     * @brief Set the current season
     * @param s Season to set
     */
    void setSeason(const std::string& s);
    /**
     * @brief Set the state price
     * @param price Price value to set
     */
    void setStatePrice(double price);
};

#endif