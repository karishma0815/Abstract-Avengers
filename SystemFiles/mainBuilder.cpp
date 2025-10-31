#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <memory>

#include "PlantInventory.h"
#include "PlantItem.h"
#include "ConcreteArrangementBuilder.h"
#include "Director.h"

// ---------- Small input helpers ----------
int readIntInRange(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        int x;
        if (std::cin >> x && x >= lo && x <= hi) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Invalid input. Please enter a number between " << lo << " and " << hi << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double readDouble(const std::string& prompt, double lo = 0.0) {
    while (true) {
        std::cout << prompt;
        double x;
        if (std::cin >> x && x >= lo) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Invalid input. Please enter a number >= " << lo << ".\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

// ---------- Seeding arrangement bases (Item-world) ----------
void seedArrangementPrototypes(PlantInventory& store) {
    store.registerArrangementPrototype("Rose",   std::unique_ptr<Item>(new PlantItem("Rose",   80.0, true)));
    store.registerArrangementPrototype("Orchid", std::unique_ptr<Item>(new PlantItem("Orchid",120.0, true)));
    store.registerArrangementPrototype("Lily",   std::unique_ptr<Item>(new PlantItem("Lily",   60.0, true)));
}

// ---------- UI helpers ----------
void showPrototypes(PlantInventory& store) {
    std::cout << "\n=== Available Arrangement Prototypes ===\n";
    auto keys = store.arrangementPrototypeKeys();
    if (keys.empty()) {
        std::cout << "(none)\n";
        return;
    }
    for (size_t i = 0; i < keys.size(); ++i) {
        std::cout << "  " << (i + 1) << ") " << keys[i] << "\n";
    }
}

void showDecorationOptions(PlantInventory& store) {
    store.displayAllOptions();
}

void showCartArrangements(PlantInventory& store) {
    std::cout << "\n=== 🛒 Cart: Arrangements ===\n";
    auto items = store.cartArrangementsSnapshot();
    if (items.empty()) {
        std::cout << "(cart is empty)\n";
        return;
    }
    int idx = 1;
    for (auto* it : items) {
        std::cout << "  " << idx++ << ") " 
                  << it->describe()
                  << " | total: " << it->priceFunc()
                  << " | ready: " << (it->readyForSale() ? "yes" : "no")
                  << "\n";
    }
}

// ---------- Build flows ----------
void buildFromPrototypeFlow(PlantInventory& store) {
    auto keys = store.arrangementPrototypeKeys();
    if (keys.empty()) {
        std::cout << "No prototypes registered yet.\n";
        return;
    }

    std::cout << "\nChoose a base prototype:\n";
    for (size_t i = 0; i < keys.size(); ++i) {
        std::cout << "  " << (i + 1) << ") " << keys[i] << "\n";
    }
    int choice = readIntInRange("Enter number: ", 1, (int)keys.size());
    std::string key = keys[(size_t)choice - 1];

    // Let the user set pot/wrap/note
    std::cout << "\n-- Decorations --\n";
    showDecorationOptions(store);

    double potExtra   = readDouble("\nPot surcharge (e.g., 10): R");
    std::string potColor = readLine("Pot color: ");

    double wrapExtra  = readDouble("Wrap surcharge (e.g., 12): R");
    std::string wrapMsg  = readLine("Wrap message: ");

    double noteExtra  = readDouble("Note surcharge (e.g., 5): R");
    std::string noteText = readLine("Note text: ");

    ConcreteArrangementBuilder builder;
    Director director;

    bool ok = store.buildGiftAndAddToCart(key,
                                          potExtra,  potColor,
                                          wrapExtra, wrapMsg,
                                          noteExtra, noteText,
                                          director,  builder);
    if (ok) {
        std::cout << "Added decorated arrangement from \"" << key << "\" to cart.\n";
    } else {
        std::cout << "Failed to build arrangement from prototype.\n";
    }
}

void buildCustomFromScratchFlow(PlantInventory& store) {
    std::cout << "\n=== Build Custom Arrangement (No Prototype) ===\n";
    std::string name  = readLine("Base name (e.g., Custom Aloe): ");
    double basePrice  = readDouble("Base price (e.g., 150): R");

    std::cout << "\n-- Decorations --\n";
    showDecorationOptions(store);

    double potExtra   = readDouble("\nPot surcharge (e.g., 10): R");
    std::string potColor = readLine("Pot color: ");

    double wrapExtra  = readDouble("Wrap surcharge (e.g., 12): R");
    std::string wrapMsg  = readLine("Wrap message: ");

    double noteExtra  = readDouble("Note surcharge (e.g., 5): R");
    std::string noteText = readLine("Note text: ");

    // We’ll build via the director using a temporary PlantItem as the base Item.
    ConcreteArrangementBuilder builder;
    Director director;
    director.setBuilder(&builder);

    // Either call a Director helper you have (e.g., buildGiftWithNote),
    // or just drive the builder explicitly:
    builder.reset();
    PlantItem tempBase(name, basePrice, /*ready*/ true);
    builder.buildBasePlant(tempBase);
    builder.buildPot(potExtra, potColor);
    builder.buildWrap(wrapExtra, wrapMsg);
    builder.buildNote(noteExtra, noteText);

    std::unique_ptr<Item> gift = builder.getResult();
    if (gift) {
        store.addArrangementToCart(std::move(gift));
        std::cout << "Added custom arrangement to cart.\n";
    } else {
        std::cout << "Failed to build custom arrangement.\n";
    }
}

// ---------- Main menu ----------
void printMenu() {
    std::cout << "\n================ MENU ================\n"
              << "1) List arrangement prototypes\n"
              << "2) Build from prototype\n"
              << "3) Build custom arrangement (no prototype)\n"
              << "4) Show cart (arrangements)\n"
              << "5) Show decoration options\n"
              << "0) Exit\n"
              << "======================================\n";
}

int main() {
    std::cout << "===== Interactive Arrangement Test =====\n";

    PlantInventory store;
    seedArrangementPrototypes(store);  // seed Item-bases the customer can choose

    bool running = true;
    while (running) {
        printMenu();
        int cmd = readIntInRange("Choose an option: ", 0, 5);
        switch (cmd) {
        case 1: showPrototypes(store); break;
        case 2: buildFromPrototypeFlow(store); break;
        case 3: buildCustomFromScratchFlow(store); break;
        case 4: showCartArrangements(store); break;
        case 5: showDecorationOptions(store); break;
        case 0: running = false; break;
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}
