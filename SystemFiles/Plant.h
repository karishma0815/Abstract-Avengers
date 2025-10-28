#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant {
private:
    std::string name;
    bool fertilized;
    std::string plantID;
    int exposureSunlightHours;

    //changed to double
    double lastWaterLevel;

    //added
    bool isAlive;

public:
    Plant(std::string name, bool fert, std::string id, int sunHours, int waterLevel);
    

    std::string getName();
    bool isFertilized();
    std::string getPlantID();
    int getExposureSunlightHours();

    //changes to double
    double getLastWaterLevel();
    void setName(const std::string& n);
    void setFertilized(bool fert);
    void setPlantID(const std::string& id);
    void setExposureSunlightHours(int hours);
    void setLastWaterLevel(int level);

    //karishma added the functions
    bool getIsAlive() const;
    std::string getName() const;
    void water(double amount);
    void fertilize(const std::string& fertilizerType);
    void prune(int intensity);
    void provideSunlight(int hours, const std::string& intensity);
};

#endif 