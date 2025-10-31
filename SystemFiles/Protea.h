#ifndef PROTEA_H
#define PROTEA_H
#include "Flower.h"

class Protea : public Flower {
    private:
        static const double OPTIMAL_WATER;
        static const double MIN_WATER;
        static const int OPTIMAL_SUNLIGHT;
        static const int MIN_SUNLIGHT;
        static const int OPTIMAL_PRUNE_INTENSITY;
        static const std::string OPTIMAL_FERTILIZER;
public:
    Protea(std::string name, double price, std::string species = "Protea");
    virtual ~Protea();
    std::string getPlantType() const override;

    virtual void water(double amount) override;
    virtual void fertilize(const std::string& fertilizerType) override;
    virtual void prune(int intensity) override;
    virtual void provideSunlight(int hours, const std::string& intensity) override;
    virtual std::string getCareInstructions() const override;
    
    double getOptimalWater() const { return OPTIMAL_WATER; }
    double getMinWater() const { return MIN_WATER; }
    int getOptimalSunlight() const { return OPTIMAL_SUNLIGHT; }
    int getMinSunlight() const { return MIN_SUNLIGHT; }
    int getOptimalPruneIntensity() const { return OPTIMAL_PRUNE_INTENSITY; }
    std::string getOptimalFertilizer() const { return OPTIMAL_FERTILIZER; }
};

#endif