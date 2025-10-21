#include "CustomerQueryHandler.h"

CustomerQueryHandler::CustomerQueryHandler() : nextHandler(nullptr){

}

CustomerQueryHandler::~CustomerQueryHandler(){

}

void CustomerQueryHandler::setNext(CustomerQueryHandler *handler){
    nextHandler = handler;
}


