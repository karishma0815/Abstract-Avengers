/**
 * @file Plant.h
 * @brief Basic plant entity class containing core plant attributes
 * @author Rene Reddy
 * @date 26/09/2025
 * 
 * This file defines the Plant class which represents the basic attributes
 * of a plant including its name, fertilization status, identification,
 * sunlight exposure, and water level.
 */

#ifndef PLANT_H
#define PLANT_H

#include <string>

/**
 * @class Plant
 * @brief Represents a plant entity with its basic attributes
 * 
 * The Plant class encapsulates fundamental plant information such as name,
 * fertilization status, unique identifier, sunlight exposure hours, and
 * last recorded water level. This class provides getters and setters for
 * all plant attributes.
 */


class Plant {
private:
    std::string name;
    bool fertilized;
    std::string plantID;
    int exposureSunlightHours;

    //changed to double
    double lastWaterLevel;
    std::string careInstruc;
    int price;


    //added
    bool isAlive;

public:
/**
     * @brief Construct a new Plant object
     * @param name Name of the plant
     * @param fert Fertilization status
     * @param id Unique plant identifier
     * @param sunHours Hours of sunlight exposure
     * @param waterLevel Last water level measurement
     */
    Plant(std::string name, bool fert, std::string id, int sunHours, int waterLevel,int price);
    
    /**
     * @brief Get the name of the plant
     * @return Plant name as string
     */
    std::string getName();

     /**
     * @brief Check if the plant has been fertilized
     * @return True if fertilized, false otherwise
     */
    bool isFertilized();

    /**
     * @brief Get the unique plant identifier
     * @return Plant ID as string
     */
    std::string getPlantID();
    /**
     * @brief Get the sunlight exposure hours
     * @return Number of hours of sunlight exposure
     */
    int getExposureSunlightHours();

    /**
     * @brief Get the last recorded water level
     * @return Water level value
     */

    //changes to double
    double getLastWaterLevel();
     /**
     * @brief Set the name of the plant
     * @param n New name for the plant
     */
    void setName(const std::string& n);

     /**
     * @brief Set the fertilization status
     * @param fert Fertilization status to set
     */
    void setFertilized(bool fert);

    /**
     * @brief Set the plant identifier
     * @param id New plant ID
     */
    void setPlantID(const std::string& id);

    /**
     * @brief Set the sunlight exposure hours
     * @param hours Number of sunlight exposure hours
     */
    void setExposureSunlightHours(int hours);

     /**
     * @brief Set the water level
     * @param level Water level value to set
     */
    void setLastWaterLevel(int level);
    double getPrice() const;
    void setPrice(double price);
    //this is for careiterator
    std::string getCareInstructions() const;

    //this is for when staff wants to set care instructions
    void setCareInstructions(const std::string& instructions);


    //karishma added the functions
    bool getIsAlive() const;
    std::string getName() const;
    void water(double amount);
    void fertilize(const std::string& fertilizerType);
    void prune(int intensity);
    void provideSunlight(int hours, const std::string& intensity);
};

#endif 