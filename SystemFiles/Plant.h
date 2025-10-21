#ifndef PLANT_H
#define PLANT_H

#include <string>

class Plant {
private:
    std::string name;
    bool fertilized;
    std::string plantID;
    int exposureSunlightHours;
    int lastWaterLevel;

public:
    Plant(std::string name, bool fert, std::string id, int sunHours, int waterLevel);
    

    std::string getName();
    bool isFertilized();
    std::string getPlantID();
    int getExposureSunlightHours();
    int getLastWaterLevel();
    void setName(const std::string& n);
    void setFertilized(bool fert);
    void setPlantID(const std::string& id);
    void setExposureSunlightHours(int hours);
    void setLastWaterLevel(int level);
};

#endif 