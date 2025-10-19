#include"Command.h"

/**
 * @file Command.cpp
 * @brief Implementation of the Command abstract class
 */

Command::~Command() {
    delete plant;
    delete cartInven;
}