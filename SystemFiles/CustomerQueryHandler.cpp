#include "CustomerQueryHandler.h"

CustomerQueryHandler::CustomerQueryHandler() : nextHandler(nullptr){

}

CustomerQueryHandler::~CustomerQueryHandler(){
    // Delete the next handler in the chain (if any) to free the whole chain
    // This assumes ownership semantics: the head owns the rest of the chain.
    ///just delete this if give you
    /*if (nextHandler) {
        delete nextHandler;
        nextHandler = nullptr;
    }*/
}

void CustomerQueryHandler::setNext(CustomerQueryHandler *handler){
    nextHandler = handler;
}


