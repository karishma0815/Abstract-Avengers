// Pine.h
#ifndef PINE_H
#define PINE_H
#include "Tree.h"

class Pine : public Tree {
    private:
        static const double OPTIMAL_WATER;
        static const double MIN_WATER;
        static const double MAX_WATER;
        
        static const int OPTIMAL_SUNLIGHT;
        static const int MIN_SUNLIGHT;
        static const int MAX_SUNLIGHT;
        
        static const int OPTIMAL_PRUNE_INTENSITY;
        static const int MAX_PRUNE_INTENSITY;
public:
    Pine(std::string name, double price, std::string species = "Pine");
    virtual ~Pine();
    std::string getPlantType() const override;

    virtual void water(double amount) override;
    virtual void fertilize(const std::string& fertilizerType) override;
    virtual void prune(int intensity) override;
    virtual void provideSunlight(int hours, const std::string& intensity) override;
    virtual std::string getCareInstructions() const override;

    double getOptimalWater() const { return OPTIMAL_WATER; }
    double getMinWater() const { return MIN_WATER; }
    double getMaxWater() const { return MAX_WATER; }
    int getOptimalSunlight() const { return OPTIMAL_SUNLIGHT; }
    int getMinSunlight() const { return MIN_SUNLIGHT; }
    int getMaxSunlight() const { return MAX_SUNLIGHT; }
    int getOptimalPruneIntensity() const { return OPTIMAL_PRUNE_INTENSITY; }
    int getMaxPruneIntensity() const { return MAX_PRUNE_INTENSITY; }
    std::string getOptimalFertilizer() const { return "low-nitrogen"; }
};

#endif