#include "CustomerQuery.h"

CustomerQuery::CustomerQuery(Type type, const std::string &question, Customer *customer) : type(type), question(question), customer(customer){
    
}