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
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Plant() = default;
    
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
};

#endif