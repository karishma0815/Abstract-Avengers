/**
 * @file Plant.h
 * @brief Abstract plant entity class defining interface for plant attributes
 * @author Rene Reddy
 * @date 26/09/2025
 * 
 * This file defines the abstract Plant class which represents the interface
 * for plant attributes including name, fertilization status, identification,
 * sunlight exposure, and water level.
 */

#ifndef PLANT_H
#define PLANT_H

#include <string>
#include <memory>
#include "Item.h"

/**
 * @class Plant
 * @brief Abstract base class representing a plant entity interface
 * 
 * The Plant class defines the interface for fundamental plant information 
 * such as name, fertilization status, unique identifier, sunlight exposure 
 * hours, and last recorded water level. All getters and setters are pure 
 * virtual functions that must be implemented by derived classes.
 */
class Plant {
protected:
    std::string name;
    bool fertilized;
    std::string plantID;
    int exposureSunlightHours;

    //changed to double
    double lastWaterLevel;
    std::string careInstruc;
    double price;


    //added
    bool isAlive;
    double base;
    bool ready;

public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Plant() = default;
    Plant(std::string name, bool fert, std::string id, int sunHours, int waterLevel,double price);
    
    /**
     * @brief Get the name of the plant
     * @return Plant name as string
     */
    virtual std::string getName() = 0;

    /**
     * @brief Check if the plant has been fertilized
     * @return True if fertilized, false otherwise
     */
    virtual bool isFertilized() = 0;

    /**
     * @brief Get the unique plant identifier
     * @return Plant ID as string
     */
    virtual std::string getPlantID() = 0;

    /**
     * @brief Get the sunlight exposure hours
     * @return Number of hours of sunlight exposure
     */
    virtual int getExposureSunlightHours() = 0;

    /**
     * @brief Get the last recorded water level
     * @return Water level value
     */
    virtual int getLastWaterLevel() = 0;

    /**
     * @brief Set the name of the plant
     * @param n New name for the plant
     */
    virtual void setName(const std::string& n) = 0;

    /**
     * @brief Set the fertilization status
     * @param fert Fertilization status to set
     */
    virtual void setFertilized(bool fert) = 0;

    /**
     * @brief Set the plant identifier
     * @param id New plant ID
     */
    virtual void setPlantID(const std::string& id) = 0;

    /**
     * @brief Set the sunlight exposure hours
     * @param hours Number of sunlight exposure hours
     */
    virtual void setExposureSunlightHours(int hours) = 0;

    /**
     * @brief Set the water level
     * @param level Water level value to set
     */
    virtual void setLastWaterLevel(int level) = 0;
    //void setLastWaterLevel(int level);
    double getPrice() const;
    void setPrice(double price);
    //this is for careiterator
    virtual std::string getCareInstructions() const = 0;

    //this is for when staff wants to set care instructions
    void setCareInstructions(const std::string& instructions);
    
     virtual std::string getPlantType() const = 0;
    //karishma added the functions
    bool getIsAlive() const;
    virtual void water(double amount) = 0;
    virtual void fertilize(const std::string& fertilizerType) = 0;
    virtual void prune(int intensity) = 0;
    virtual void provideSunlight(int hours, const std::string& intensity) = 0;

    //taskeen added
    // Item API
    double priceFunc() const;
    std::string describe() const;
    bool readyForSale() const;
};
#endif