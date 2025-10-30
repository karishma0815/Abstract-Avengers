#include "PlantCareHandler.h"

PlantCareHandler::PlantCareHandler() : nextHandler(nullptr){

}

PlantCareHandler::~PlantCareHandler(){

}

void PlantCareHandler::setNext(PlantCareHandler *handler){
    nextHandler = handler;
}


