#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <memory>

#include "PlantInventory.h"
#include "Iterator.h"                 // your Plant* iterator base
#include "CartIterator.h"             // your cart iterator for Plant*
#include "Director.h"
#include "ConcreteArrangementBuilder.h"
#include "ArrangementsIterator.h"     // new

// ----- small i/o helpers -----
static void clearCin() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
static int askInt(const std::string& prompt, int minV, int maxV) {
    while (true) {
        std::cout << prompt;
        int v; if (std::cin >> v && v >= minV && v <= maxV) { clearCin(); return v; }
        std::cout << "Invalid.\n"; clearCin();
    }
}
static double askDouble(const std::string& prompt, double minV = 0.0) {
    while (true) {
        std::cout << prompt;
        double v; if (std::cin >> v && v >= minV) { clearCin(); return v; }
        std::cout << "Invalid.\n"; clearCin();
    }
}
static std::string askStr(const std::string& prompt) {
    std::cout << prompt;
    std::string s; std::getline(std::cin, s);
    return s;
}
static void pause() { std::cout << "\nPress ENTER to continue..."; std::cin.get(); }

// ----- seeders (use your Plant ctor: name, fert, id, sunHours, waterLevel, price INT) -----
static void seedPrototypes(PlantInventory& store) {
    store.registerPrototype("Rose",   std::unique_ptr<Plant>(new Plant("Rose",   true,  "P-ROSE", 6, 3,  80)));
    store.registerPrototype("Orchid", std::unique_ptr<Plant>(new Plant("Orchid", false, "P-ORCH", 4, 2, 120)));
    store.registerPrototype("Lily",   std::unique_ptr<Plant>(new Plant("Lily",   true,  "P-LILY", 5, 3,  60)));
}

// Add a couple of STOCK items to inventory so the list isn’t empty at start
static void seedStock(PlantInventory& store) {
    // create owned plants directly in main inventory
    std::unique_ptr<Plant> p1(new Plant("Snake Plant", true, "STK-SNAKE", 6, 2, 120));
    Plant* r1 = p1.get(); store.add(r1); (void)p1.release();

    std::unique_ptr<Plant> p2(new Plant("Peace Lily", true, "STK-PLILY", 4, 3, 90));
    Plant* r2 = p2.get(); store.add(r2); (void)p2.release();
}

// ----- views -----
static void showInventory(PlantInventory& store) {
    std::cout << "\n=== INVENTORY (owned + non-owned) ===\n";
    std::vector<Plant*> items = store.getPlants();
    if (items.empty()) { std::cout << "(empty)\n"; return; }
    for (size_t i=0;i<items.size();++i) {
        Plant* p = items[i];
        std::cout << i << ") " << p->describe()
                  << " | price: " << p->priceFunc()
                  << " | ready: " << (p->readyForSale() ? "yes" : "no")
                  << "\n";
    }
}

static void showPrototypes(PlantInventory& store) {
    std::cout << "\n=== PROTOTYPE CATALOG ===\n";
    std::vector<std::string> keys = store.prototypeKeys();
    std::vector<const Plant*> protos = store.prototypeSnapshot();
    if (keys.empty()) { std::cout << "(empty)\n"; return; }
    for (size_t i=0;i<keys.size() && i<protos.size(); ++i) {
        const Item* it = protos[i]; // Plant* as Item*
        std::cout << i << ") [" << keys[i] << "] "
                  << it->describe()
                  << " | base: " << it->priceFunc()
                  << " | ready: " << (it->readyForSale() ? "yes" : "no")
                  << "\n";
    }
}

static void showCart(PlantInventory& store) {
    std::cout << "\n=========== CART ===========\n";

    // 1) plants in cart (Plant*)
    std::cout << "\nPLANTS:\n";
    PlantInventory* cartInv = store.getCartInventory();
    if (cartInv && !cartInv->isEmpty()) {
        CartIterator pit(cartInv);
        for (pit.first(); !pit.isDone(); pit.next()) {
            Plant* p = pit.currentItem();
            if (p) {
                std::cout << " - " << p->describe()
                          << " | price: " << p->priceFunc()
                          << " | ready: " << (p->readyForSale() ? "yes" : "no")
                          << "\n";
            }
        }
    } else {
        std::cout << " (none)\n";
    }

    // 2) arranged gifts (Item*)
    std::cout << "\nARRANGED GIFTS:\n";
    std::vector<const Item*> gifts = store.cartArrangementsSnapshot();
    if (!gifts.empty()) {
        ArrangementsIterator ait(gifts);
        for (ait.first(); !ait.isDone(); ait.next()) {
            const Item* it = ait.current();
            std::cout << " - " << it->describe()
                      << " | total: " << it->priceFunc()
                      << " | ready: " << (it->readyForSale() ? "yes" : "no")
                      << "\n";
        }
    } else {
        std::cout << " (none)\n";
    }

    std::cout << "============================\n";
}

// ----- main menu -----
int main() {
    PlantInventory store;
    seedPrototypes(store);
    seedStock(store);

    bool running = true;
    while (running) {
        std::cout << "\n==============================\n";
        std::cout << " PLANT SHOP - INTERACTIVE TEST\n";
        std::cout << "==============================\n";
        std::cout << "1) View Inventory\n";
        std::cout << "2) View Prototype Catalog\n";
        std::cout << "3) Add Prototype CLONE to Inventory\n";
        std::cout << "4) Add Prototype as DECORATED GIFT to Cart\n";
        std::cout << "5) Add EXISTING Inventory Item to Cart\n";
        std::cout << "6) Add SINGLE plain Plant to Cart (no prototype)\n";
        std::cout << "7) Build CUSTOM Arrangement (no prototype)\n";
        std::cout << "8) View Cart\n";
        std::cout << "0) Exit\n";

        int ch = askInt("Select: ", 0, 8);
        switch (ch) {
            case 1: showInventory(store); pause(); break;
            case 2: showPrototypes(store); pause(); break;

            case 3: { // clone a prototype into inventory
                std::vector<std::string> keys = store.prototypeKeys();
                if (keys.empty()) { std::cout << "No prototypes.\n"; pause(); break; }
                showPrototypes(store);
                int idx = askInt("Index to clone into inventory: ", 0, (int)keys.size()-1);
                bool ok = store.addCloneToInventory(keys[idx]);
                std::cout << (ok ? "Cloned.\n" : "Clone failed.\n");
                pause();
                break;
            }

            case 4: { // build decorated gift from prototype
                std::vector<std::string> keys = store.prototypeKeys();
                if (keys.empty()) { std::cout << "No prototypes.\n"; pause(); break; }
                showPrototypes(store);
                int idx = askInt("Prototype index: ", 0, (int)keys.size()-1);

                double potExtra = askDouble("Pot extra (e.g., 15): ", 0.0);
                std::string potColor = askStr("Pot color: ");
                double wrapExtra = askDouble("Wrap extra (e.g., 10): ", 0.0);
                std::string wrapMsg  = askStr("Wrap message: ");
                double noteExtra = askDouble("Note extra (e.g., 5): ", 0.0);
                std::string noteText = askStr("Note text: ");

                ConcreteArrangementBuilder builder;
                Director director;
                bool ok = store.buildGiftAndAddToCart(keys[idx],
                                                      potExtra, potColor,
                                                      wrapExtra, wrapMsg,
                                                      noteExtra, noteText,
                                                      director, builder);
                std::cout << (ok ? "Gift added to cart.\n" : "Build failed.\n");
                pause();
                break;
            }

            case 5: { // add an existing inventory Plant* to cart
                std::vector<Plant*> items = store.getPlants();
                if (items.empty()) { std::cout << "Inventory empty.\n"; pause(); break; }
                showInventory(store);
                int idx = askInt("Inventory index to add to cart: ", 0, (int)items.size()-1);
                store.addToCart(items[(size_t)idx]); // non-owning ref
                std::cout << "Added to cart.\n";
                pause();
                break;
            }

            case 6: { // single plain plant without prototype
                std::string name = askStr("Name: ");
                bool fert = askInt("Fertilised? (0/1): ", 0, 1) == 1;
                std::string id = askStr("ID: ");
                int sun = askInt("Sun hours: ", 0, 24);
                int water = askInt("Water level (0-5): ", 0, 5);
                int price = askInt("Price (int): ", 0, 100000);

                // own it in inventory then add cart ref
                std::unique_ptr<Plant> up(new Plant(name, fert, id, sun, water, price));
                Plant* raw = up.get(); store.add(raw); (void)up.release();
                store.addToCart(raw);

                std::cout << "Single plant added to cart.\n";
                pause();
                break;
            }

            case 7: { // custom arrangement from scratch (no prototype)
                std::string name = askStr("Base plant name: ");
                bool fert = askInt("Fertilised? (0/1): ", 0, 1) == 1;
                std::string id = askStr("ID: ");
                int sun = askInt("Sun hours: ", 0, 24);
                int water = askInt("Water level (0-5): ", 0, 5);
                int price = askInt("Base price (int): ", 0, 100000);

                double potExtra = askDouble("Pot extra: ", 0.0);
                std::string potColor = askStr("Pot color: ");
                double wrapExtra = askDouble("Wrap extra: ", 0.0);
                std::string wrapMsg  = askStr("Wrap message: ");
                double noteExtra = askDouble("Note extra: ", 0.0);
                std::string noteText = askStr("Note text: ");

                ConcreteArrangementBuilder builder;
                Director director;

                // Build from an ephemeral base Plant (not added to inventory)
                Plant base(name, fert, id, sun, water, price);
                director.setBuilder(&builder);
                std::unique_ptr<Item> gift =
                    director.buildGiftWithNote(base, potExtra, potColor,
                                                     wrapExtra, wrapMsg,
                                                     noteExtra, noteText);
                if (gift) {
                    store.addArrangementToCart(std::move(gift));
                    std::cout << "Custom arrangement added to cart.\n";
                } else {
                    std::cout << "Build failed.\n";
                }
                pause();
                break;
            }

            case 8: showCart(store); pause(); break;
            case 0: running = false; break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
