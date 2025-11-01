#include "SucculentFactory.h"
#include "Succulent.h"
#include "Cacti.h"
#include "Jade.h"
#include "Orchid.h"

SucculentFactory::SucculentFactory() : productionCounter(0) {
}

SucculentFactory::~SucculentFactory() {
}

// SucculentProduct* SucculentFactory::createSucculent(std::string name, double price, int stock) {
//     productionCounter++;
//     // Create succulent with species based on counter for variety
//     std::string species;
//     switch (productionCounter % 4) {
//         case 0:
//             return new Succulent(name, price, "Echeveria");
//         case 1:
//             return new Jade(name + " Jade", price, "Jade Plant");
//         case 2:
//             return new Cacti(name + " Cactus", price, "Prickly Pear");
//         case 3:
//             return new Orchid(name + " Orchid", price, "Moth Orchid");
//         default:
//             return new Succulent(name, price, "Generic Succulent");
//     }
    
//     return new Succulent(name, price, species);
// }

SucculentProduct* SucculentFactory::createSucculent(std::string name, double price, std::string species, int stock) {
    productionCounter++;
    
    if (species == "Cacti") return new Cacti(name, price, species);
    if (species == "Jade") return new Jade(name, price, species);
    if (species == "Orchid") return new Orchid(name, price, species);
    
    return new Succulent(name, price, species);
}

TreeProduct* SucculentFactory::createTree(std::string name, double price, std::string species, int stock) {
    // SucculentFactory doesn't create trees
    return nullptr;
}

FlowerProduct* SucculentFactory::createFlower(std::string name, double price, std::string species, int stock) {
    // SucculentFactory doesn't create flowers
    return nullptr;
}

SucculentGroup* SucculentFactory::createSucculentGroup(std::string groupName) {
    return new SucculentGroup(groupName);
}

FlowerGroup* SucculentFactory::createFlowerGroup(std::string groupName) {
    // SucculentFactory doesn't create flower groups
    return nullptr;
}

TreeGroup* SucculentFactory::createTreeGroup(std::string groupName) {
    // SucculentFactory doesn't create tree groups
    return nullptr;
}