#include"Plant.h"
Plant::Plant(const std::string& type) : type(type) {}

std::string Plant::getType() const {
    return type;
}