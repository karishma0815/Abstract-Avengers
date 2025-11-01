#ifndef SUCCULENT_H
#define SUCCULENT_H

#include "Plant.h"
#include "SucculentProduct.h"
#include <string>

/**
 * @class Succulent
 * @brief Concrete product for succulents, inherits from Plant
 */
class Succulent : public Plant,public SucculentProduct {
protected:
    std::string species;
    std::string name;
    double price;
    
public:
    Succulent(std::string name, double price, std::string species);
    virtual ~Succulent();
    
    // Implement pure virtual functions from Plant
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
    
    // Succulent-specific methods
    virtual std::string getPlantType() const;
    std::string getSpecies() const;
    int getCount() const;
    double getTotalValue() const;

    virtual void water(double amount) override;
    virtual void fertilize(const std::string& fertilizerType) override;
    virtual void prune(int intensity) override;
    virtual void provideSunlight(int hours, const std::string& intensity) override;
    virtual std::string getCareInstructions() const override;
};

#endif
