#include"CustomerCommand.h"

/**
 * @file CustomerCommand.cpp
 * @brief Implementation of the CustomerCommand abstract class
 */

CustomerCommand::~CustomerCommand() {
    // The command does not own the plant or the inventory pointers
    // (they are passed in at execute time). Do not delete them here
    // to avoid double-free or deleting uninitialised pointers.
}