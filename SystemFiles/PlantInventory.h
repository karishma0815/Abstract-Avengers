/**
 * @file PlantInventory.h
 * @brief Concrete Aggregate implementation using vector
 */

#ifndef PLANTINVENTORY_H
#define PLANTINVENTORY_H

#include "PlantContainer.h"
#include <vector>
#include <memory>
#include<iostream>
#include <unordered_map> 
#include "Director.h"
#include "ArrangementBuilder.h"
#include "PlantAsItemAdapter.h"

/**
 * @class PlantInventory
 * @brief Concrete aggregate that stores plants in a vector
 * 
 * Implements the PlantCollection interface to maintain a collection
 * of plants and create appropriate iterators
 */
class PlantInventory : public PlantContainer {
public:
    /**
     * @brief Constructs a PlantInventory
     */
    PlantInventory();
    /**
     * @brief Destructor
     */
    ~PlantInventory();
    /**
     * @brief Creates an iterator for this inventory
     * @return Pointer to a new PlantIterator object
     */
    Iterator* createPlantIterator(PlantInventory* inventory) override;

    Iterator* createPriceRangeIterator(PlantInventory* inventory, double min, double max) override;

    /**
     * @brief Creates a cart iterator for this container
     * @return Pointer to a new CartIterator object
     */
    Iterator* createCartIterator(PlantInventory* inventory) override;
    /**
     * @brief Adds a plant to the inventory
     * @param plant Pointer to the Plant to add
     */
    void add(Plant* plant) override;
    // Adds a non-owning reference to a plant (useful for carts)
    void addNonOwning(Plant* plant);
    /**
     * @brief Removes a plant from the inventory
     * @param plant Pointer to the Plant to remove
     */
    void remove(Plant* plant) override;
    
    // Remove a non-owning reference (does not delete the plant)
    void removeNonOwning(Plant* plant);
    /**
     * @brief Gets the number of plants in the inventory
     * @return The size of the inventory
     */
    int size() const override;
    /**
     * @brief Checks if the inventory is empty
     * @return True if empty, false otherwise
     */
    bool isEmpty() const override;
    /**
     * @brief Gets a plant at a specific index
     * @param index The index of the plant
     * @return Pointer to the Plant at the given index
     */
    Plant* getPlant(int index) const;
    /**
     * @brief Gets a snapshot list of raw Plant* pointers for iteration
     * @return A vector of raw Plant* pointers (owned and non-owned)
     */
    std::vector<Plant*> getPlants() const;

    //addTOCart function can be added here if needed
    PlantInventory* getCartInventory();
    
    void addToCart(Plant* plant) ;

    void removeFromCart(Plant* plant);

   /**
 * @file DecorationInventory.h
 * @brief Manages dynamic decoration inventory
 */

    void addGiftWrap(const std::string& color);

    void addPot(const std::string& color);

    void addNote(const std::string& color);
    
    // Remove decoration options
    void removeGiftWrap(const std::string& color);

    void removePot(const std::string& color);

    void removeNote(const std::string& color);
    
    /// @brief Get Giftwrap options(for the customer)
    /// @return
    const std::vector<std::string>& getGiftWraps() const; 

    const std::vector<std::string>& getPots() const ;

    const std::vector<std::string>& getNotes() const;
    
    /// @brief Display all decorations

    void displayAllOptions() const;

    // ----- BUILT (DECORATED) ARRANGEMENTS IN CART -----
    void addArrangementToCart(std::unique_ptr<Item> item);
    std::vector<const Item*> cartArrangementsSnapshot() const;
    bool buildGiftFromPlantAndAddToCart(Plant& plant,
                                                    double potExtra,  const std::string& potColor,
                                                    double wrapExtra, const std::string& wrapMessage,
                                                    double noteExtra, const std::string& noteText,
                                                    Director& director, ArrangementBuilder& builder);


    private:
    // Owned plant storage
    std::vector<std::unique_ptr<Plant>> ownedPlants;
    // Non-owning references (e.g., shopping cart references)
    std::vector<Plant*> nonOwnedPlants;
    PlantInventory* cartInventory;///Inventory representing the customer's cart
    bool isCart;  /// Whether this inventory is a cart (non-owning container)
    std::vector<std::string> giftWraps;
    std::vector<std::string> pots;
    std::vector<std::string> notes;

    std::vector<std::unique_ptr<Item>> cartArrangements_;
};

#endif 