/**
 * @file PlantInventory.cpp
 * @brief Implementation of the PlantInventory class
 */
#include "PlantInventory.h"
#include "PlantIterator.h"
#include "CareIterator.h"
#include "PriceRangeIterator.h"
#include "CartIterator.h"
#include "Plant.h"
#include <algorithm>

PlantInventory::PlantInventory() : cartInventory(nullptr), isCart(false) {
    // Cart will be created on first use through getCartInventory()
    giftWraps = {"Black", "White"};
    pots = {"Black", "Brown", "White"};
    notes = {"White", "Pink", "Blue"};
}

PlantInventory::~PlantInventory() {
    // ownedPlants will be automatically deleted via unique_ptr
    ownedPlants.clear();
    nonOwnedPlants.clear();
    
    // Only delete cart if this is a main inventory
    if (!isCart && cartInventory != nullptr) {
        delete cartInventory;
        cartInventory = nullptr;
    }
}

Iterator* PlantInventory::createPlantIterator(PlantInventory* inventory) {
    return new PlantIterator(this);
}

Iterator* PlantInventory::createCareIterator(PlantInventory* inventory, const std::string& care) {
    return new CareIterator(this,care);
}

Iterator* PlantInventory::createPriceRangeIterator(PlantInventory* inventory, double min, double max) {
    return new PriceRangeIterator(this,min,max);
}

Iterator* PlantInventory::createCartIterator(PlantInventory* inventory) {
    return new CartIterator(this->cartInventory);
}

void PlantInventory::add(Plant* plant) {
    if (plant != nullptr) {
        ownedPlants.emplace_back(plant);
    }
}

void PlantInventory::addNonOwning(Plant* plant) {
    if (plant != nullptr) {
        nonOwnedPlants.push_back(plant);
    }
}

void PlantInventory::remove(Plant* plant) {
    // remove from ownedPlants
    auto it = std::find_if(ownedPlants.begin(), ownedPlants.end(),
                           [&](const std::unique_ptr<Plant>& p){ return p.get() == plant; });
    if (it != ownedPlants.end()) {
        ownedPlants.erase(it);
        // If this plant was in a customer's cart, remove the non-owning reference
        if (cartInventory != nullptr) {
            cartInventory->removeNonOwning(plant);
        }
        return;
    }
    // if not owned, try non-owned list
    removeNonOwning(plant);
}

void PlantInventory::removeNonOwning(Plant* plant) {
    auto it = std::find(nonOwnedPlants.begin(), nonOwnedPlants.end(), plant);
    if (it != nonOwnedPlants.end()) {
        nonOwnedPlants.erase(it);
    }
}

int PlantInventory::size() const {
    return static_cast<int>(ownedPlants.size() + nonOwnedPlants.size());
}

bool PlantInventory::isEmpty() const {
    return ownedPlants.empty() && nonOwnedPlants.empty();
}

Plant* PlantInventory::getPlant(int index) const {
    int ownedCount = static_cast<int>(ownedPlants.size());
    if (index >= 0 && index < ownedCount) {
        return ownedPlants[index].get();
    }
    int nonOwnedIndex = index - ownedCount;
    if (nonOwnedIndex >= 0 && nonOwnedIndex < static_cast<int>(nonOwnedPlants.size())) {
        return nonOwnedPlants[nonOwnedIndex];
    }
    return nullptr;
}

std::vector<Plant*> PlantInventory::getPlants() const {
    if (isCart) {
        // If this is a cart, return only non-owned plants
        return nonOwnedPlants;
    } else {
        // If this is main inventory, return both owned and non-owned plants
        std::vector<Plant*> result;
        result.reserve(ownedPlants.size() + nonOwnedPlants.size());
        for (const auto& up : ownedPlants) result.push_back(up.get());
        for (Plant* p : nonOwnedPlants) result.push_back(p);
        return result;
    }
}

PlantInventory* PlantInventory::getCartInventory() {
    // Lazy initialization of cart
    if (!isCart && cartInventory == nullptr) {
        cartInventory = new PlantInventory();
        cartInventory->isCart = true;
    }
    return cartInventory;
}

void PlantInventory::addToCart(Plant* plant) {
    if (!isCart) {  // Only main inventory can add to cart
        if (cartInventory == nullptr) {
            cartInventory = new PlantInventory();
            cartInventory->isCart = true;
        }
        cartInventory->addNonOwning(plant);  // Use non-owning reference for cart
    }
}

void PlantInventory::removeFromCart(Plant* plant) {
    if (!isCart && cartInventory != nullptr && plant != nullptr) {
        cartInventory->removeNonOwning(plant);  // Use non-owning remove for cart
    }
}

void PlantInventory::addGiftWrap(const std::string& color) {
    if (std::find(giftWraps.begin(), giftWraps.end(), color) == giftWraps.end()) {
        giftWraps.push_back(color);
    }
}

void PlantInventory::addPot(const std::string& color) {
    if (std::find(pots.begin(), pots.end(), color) == pots.end()) {
        pots.push_back(color);
    }
}

void PlantInventory::addNote(const std::string& color) {
    if (std::find(notes.begin(), notes.end(), color) == notes.end()) {
        notes.push_back(color);
    }
}

void PlantInventory::removeGiftWrap(const std::string& color) {
    auto it = std::find(giftWraps.begin(), giftWraps.end(), color);
    if (it != giftWraps.end()) {
        giftWraps.erase(it);
    }
}

void PlantInventory::removePot(const std::string& color) {
    auto it = std::find(pots.begin(), pots.end(), color);
    if (it != pots.end()) {
        pots.erase(it);
    }
}

void PlantInventory::removeNote(const std::string& color) {
    auto it = std::find(notes.begin(), notes.end(), color);
    if (it != notes.end()) {
        notes.erase(it);
    }
}

///you'll get free deco once a plant is bought.
void PlantInventory::displayAllOptions() const {
    std::cout << "\n╔════════════════════════════════════╗\n";
    std::cout << "  ║   Available Decoration Options     ║\n";
    std::cout << "  ╚════════════════════════════════════╝\n\n";
    
    std::cout << "🎁 Gift Wrap Colors:\n";
    for (size_t i = 0; i < giftWraps.size(); ++i) {
        std::cout << "   " << (i + 1) << ". " << giftWraps[i] << "\n";
    }
    
    std::cout << "\n🪴 Pot Colors:\n";
    for (size_t i = 0; i < pots.size(); ++i) {
        std::cout << "   " << (i + 1) << ". " << pots[i] << "\n";
    }
    
    std::cout << "\n📝 Note Colors:\n";
    for (size_t i = 0; i < notes.size(); ++i) {
        std::cout << "   " << (i + 1) << ". " << notes[i] << "\n";
    }
    
    std::cout << "\n════════════════════════════════════\n";
}

const std::vector<std::string>& PlantInventory::getGiftWraps() const{
    return giftWraps;
}

const std::vector<std::string>& PlantInventory::getPots() const{
    return pots;
}

const std::vector<std::string>& PlantInventory::getNotes() const{
    return notes;
}

//for prototype
void PlantInventory::registerPrototype(const std::string& key, std::unique_ptr<Plant> proto) 
{
    prototypes[key] = std::move(proto);
}

std::unique_ptr<Plant> PlantInventory::cloneOf(const std::string& key) const 
{
    auto it = prototypes.find(key);
    if (it == prototypes.end() || !it->second) return nullptr;
    return std::unique_ptr<Plant>(static_cast<Plant*>(it->second->clone().release()));
}

bool PlantInventory::hasPrototype(const std::string& key) const 
{
    return prototypes.find(key) != prototypes.end();
}

std::size_t PlantInventory::prototypeCount() const 
{ 
    return prototypes.size(); 
}

std::vector<const Plant*> PlantInventory::prototypeSnapshot() const 
{
    std::vector<const Plant*> out;
    out.reserve(prototypes.size());
    for (const auto& kv : prototypes) out.push_back(kv.second.get());
    return out;
}

std::vector<std::string> PlantInventory::prototypeKeys() const 
{
    std::vector<std::string> out;
    out.reserve(prototypes.size());
    for (const auto& kv : prototypes) out.push_back(kv.first);
    return out;
}

const Item* PlantInventory::getPrototypePtr(const std::string& key) const 
{
    auto it = prototypes.find(key);
    if (it == prototypes.end() || !it->second) return nullptr;
    return it->second.get(); // Plant* as Item*
}

// ===== helpers =====
bool PlantInventory::addCloneToInventory(const std::string& key) 
{
    auto clone = cloneOf(key);
    if (!clone) return false;
    Plant* raw = clone.get();
    add(raw);              // existing add() takes ownership (unique_ptr)
    (void)clone.release(); // prevent double delete
    return true;
}

bool PlantInventory::addCloneToCart(const std::string& key) 
{
    auto clone = cloneOf(key);
    if (!clone) return false;
    Plant* raw = clone.get();
    add(raw);              // store owns lifetime
    (void)clone.release();
    addToCart(raw);        // non-owning ref into cart
    return true;
}

// ===== Built (decorated) arrangements in CART =====
void PlantInventory::addArrangementToCart(std::unique_ptr<Item> item) 
{
    if (item) cartArrangements_.push_back(std::move(item));
}

std::vector<const Item*> PlantInventory::cartArrangementsSnapshot() const 
{
    std::vector<const Item*> out;
    out.reserve(cartArrangements_.size());
    for (const auto& up : cartArrangements_) out.push_back(up.get());
    return out;
}

// ===== One-shot build from prototype key & add to cart =====
bool PlantInventory::buildGiftAndAddToCart(const std::string& key,
                                           double potExtra,  const std::string& potColor,
                                           double wrapExtra, const std::string& wrapMessage,
                                           double noteExtra, const std::string& noteText,
                                           Director& director, ArrangementBuilder& builder)
{
    auto* proto = getPrototypePtr(key);
    if (!proto) return false;

    director.setBuilder(&builder);
    auto product = director.buildGiftWithNote(*proto,
                                              potExtra,  potColor,
                                              wrapExtra, wrapMessage,
                                              noteExtra, noteText);
    if (!product) return false;

    addArrangementToCart(std::move(product));
    return true;
}

bool PlantInventory::buildCustomAndAddToCart(const std::string& name,
                                             bool fert,
                                             const std::string& id,
                                             int sunHours,
                                             int waterLevel,
                                             int price,
                                             double potExtra,  const std::string& potColor,
                                             double wrapExtra, const std::string& wrapMessage,
                                             double noteExtra, const std::string& noteText,
                                             Director& director, ArrangementBuilder& builder)
{
    // 1) make a temporary base Item (not added to inventory)
    Plant base(name, fert, id, sunHours, waterLevel, price);

    // 2) build decoration chain
    director.setBuilder(&builder);
    std::unique_ptr<Item> gift =
        director.buildGiftWithNote(base, potExtra, potColor,
                                         wrapExtra, wrapMessage,
                                         noteExtra, noteText);
    if (!gift) return false;

    // 3) store in arranged-items bucket
    addArrangementToCart(std::move(gift));
    return true;
}

bool PlantInventory::addSinglePlantToCart(const std::string& name,
                                          bool fert,
                                          const std::string& id,
                                          int sunHours,
                                          int waterLevel,
                                          int price)
{
    // own in main inventory
    std::unique_ptr<Plant> up(new Plant(name, fert, id, sunHours, waterLevel, price));
    Plant* raw = up.get();
    add(raw);                 // transfers ownership to ownedPlants
    (void)up.release();

    // put a non-owning reference into the cart
    addToCart(raw);
    return true;
}
