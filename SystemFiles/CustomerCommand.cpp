#include"CustomerCommand.h"

/**
 * @file CustomerCommand.cpp
 * @brief Implementation of the CustomerCommand abstract class
 */

CustomerCommand::~CustomerCommand() {
    delete plant;
    delete cartInven;
}