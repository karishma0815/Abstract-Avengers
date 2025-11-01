#include "PlantInventory.h"
#include <cassert>
#include <iostream>

void testDecorations() {
    std::cout << "\n=== Testing Decoration Management ===\n" << std::endl;
    
    PlantInventory inventory;
    
    // Test initial state
    std::cout << "Initial decoration options:" << std::endl;
    std::cout << "Gift wraps: " << inventory.getGiftWraps().size() << " options" << std::endl;
    std::cout << "Pots: " << inventory.getPots().size() << " options" << std::endl;
    std::cout << "Notes: " << inventory.getNotes().size() << " options" << std::endl;
    
    // Test adding new options
    std::cout << "\nAdding new decoration options..." << std::endl;
    inventory.addGiftWrap("Red");
    inventory.addGiftWrap("Gold");
    inventory.addPot("Blue");
    inventory.addPot("Green");
    inventory.addNote("Yellow");
    inventory.addNote("Purple");
    
    // Test duplicate additions (should not add duplicates)
    std::cout << "Testing duplicate prevention..." << std::endl;
    inventory.addGiftWrap("Red");  // Attempting to add duplicate
    
    // Display current options
    std::cout << "\nCurrent decoration options after additions:" << std::endl;
    std::cout << "Gift wraps:" << std::endl;
    for (const auto& wrap : inventory.getGiftWraps()) {
        std::cout << "- " << wrap << std::endl;
    }
    
    std::cout << "\nPots:" << std::endl;
    for (const auto& pot : inventory.getPots()) {
        std::cout << "- " << pot << std::endl;
    }
    
    std::cout << "\nNotes:" << std::endl;
    for (const auto& note : inventory.getNotes()) {
        std::cout << "- " << note << std::endl;
    }
    
    // Test removal
    std::cout << "\nTesting removal functionality..." << std::endl;
    inventory.removeGiftWrap("Red");
    inventory.removePot("Blue");
    inventory.removeNote("Yellow");
    
    // Test removing non-existent items (should handle gracefully)
    std::cout << "Testing removal of non-existent items..." << std::endl;
    inventory.removeGiftWrap("NonExistent");
    
    // Display final state
    std::cout << "\nFinal decoration options after removals:" << std::endl;
    inventory.displayAllOptions();
    
    // Verify counts
    std::cout << "\nFinal counts:" << std::endl;
    std::cout << "Gift wraps: " << inventory.getGiftWraps().size() << " options" << std::endl;
    std::cout << "Pots: " << inventory.getPots().size() << " options" << std::endl;
    std::cout << "Notes: " << inventory.getNotes().size() << " options" << std::endl;
}

int main() {
    testDecorations();
    return 0;
}