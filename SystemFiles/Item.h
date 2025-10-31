/*Abstract Avengers*/

/**
 * @file Item.h
 * @brief Base sales-floor product interface 
 * @author Taskeen Abdoola
 * @date 2025-10-10
 */

#ifndef ITEM_H
#define ITEM_H

#include <memory>
#include <string>

class Item 
{
public:
   /** @brief Virtual destructor. */
  virtual ~Item() {}

  /** @brief Final price of this item (including all decorations). */
  virtual double priceFunc() const = 0;

  /** @brief Human-readable description for receipts/UI. */
  virtual std::string describe() const = 0;

  /** @brief Whether this item can be sold right now. */
  virtual bool readyForSale() const = 0;

  /**
   * @brief Prototype: deep copy this item (including any decoration chain).
   * @return Newly allocated deep copy.
   */
  virtual std::unique_ptr<Item> clone() const = 0;
};

#endif