#include "PlantExpert.h"
#include "CustomerQuery.h"
#include <iostream>

void PlantExpert::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout << "Plant Expert: ";
        if(query.question.find("died") != std::string::npos || 
           query.question.find("dying") != std::string::npos ||
           query.type == CustomerQuery::COMPLAINT) {
            std::cout << "I'm sorry to hear about your plant! Let me help troubleshoot what might have happened. We stand behind our plants and can offer a replacement or store credit." << std::endl;
        } else if(query.question.find("water my cactus") != std::string::npos || 
                  query.question.find("cactus") != std::string::npos) {
            std::cout << "Cacti only need watering every 2-3 weeks. Overwatering is the most common mistake!" << std::endl;
        } else if(query.question.find("fern leaves turning yellow") != std::string::npos ||
                  query.question.find("fern") != std::string::npos) {
            std::cout << "Yellow leaves on ferns usually mean too much water or not enough humidity. Try misting daily and reducing watering frequency." << std::endl;
        } else if(query.question.find("fertilizer") != std::string::npos) {
            std::cout << "I recommend our organic slow-release fertilizer - it's perfect for most houseplants." << std::endl;
        } else if(query.question.find("soil for succulents") != std::string::npos ||
                  query.question.find("succulent soil") != std::string::npos ||
                  query.question.find("succulents") != std::string::npos) {
            std::cout << "Succulents need well-draining soil. Use our special cactus mix with extra perlite to prevent root rot." << std::endl;
        } else if(query.question.find("orchid") != std::string::npos) {
            std::cout << "For orchids, use a special orchid mix with bark chips for proper drainage and air circulation around the roots." << std::endl;
        } else if(query.question.find("propagate") != std::string::npos ||
                  query.question.find("snake plant") != std::string::npos) {
            std::cout << "Snake plants are easy to propagate! Cut a healthy leaf into sections and plant them in well-draining soil, or place in water until roots develop." << std::endl;
        } else {
            std::cout << "Based on my expertise, I'd recommend bringing in a photo or sample so I can give you the most accurate advice for your specific situation." << std::endl;
        }
    } else if(nextHandler != nullptr){
        std::cout << "Plant Expert: \"This requires management approval. Let me escalate this.\"" << std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout << "Plant Expert: \"I'm unable to resolve this issue without management input.\"" << std::endl;
    }
}

bool PlantExpert::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::CARE_ADVICE || 
           query.type == CustomerQuery::COMPLAINT ||
           query.question.find("plant") != std::string::npos ||
           query.question.find("care") != std::string::npos ||
           query.question.find("died") != std::string::npos ||
           query.question.find("dying") != std::string::npos ||
           query.question.find("health") != std::string::npos;
}
