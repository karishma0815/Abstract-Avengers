#include "PlantExpert.h"
#include "CustomerQuery.h"
#include "WaterRecomm.h"
#include "SunlightRecomm.h"
#include <iostream>

void PlantExpert::handleQuery(const CustomerQuery &query){
    if(canHandle(query)){
        std::cout << " Plant Expert: ";
        
        // Use WaterRecomm for watering-related questions
        if(query.question.find("water") != std::string::npos || 
           query.question.find("watering") != std::string::npos ||
           query.question.find("hydrate") != std::string::npos) {
            WaterRecomm waterAdvisor;
            waterAdvisor.recommend();
        }
        // Use SunlightRecomm for light-related questions
        else if(query.question.find("sunlight") != std::string::npos || 
                query.question.find("light") != std::string::npos ||
                query.question.find("sun") != std::string::npos ||
                query.question.find("bright") != std::string::npos ||
                query.question.find("dark") != std::string::npos) {
            SunlightRecomm lightAdvisor;
            lightAdvisor.recommend();
        }
        // Handle other plant care questions
        else if(query.question.find("died") != std::string::npos || 
               query.question.find("dying") != std::string::npos ||
               query.type == CustomerQuery::COMPLAINT) {
            std::cout << " I'm sorry to hear about your plant! Let me help troubleshoot what might have happened. We stand behind our plants and can offer a replacement or store credit." << std::endl;
        } else if(query.question.find("fertilizer") != std::string::npos) {
            std::cout << " I recommend our organic slow-release fertilizer - it's perfect for most houseplants." << std::endl;
        } else if(query.question.find("soil") != std::string::npos) {
            std::cout << " For most plants, use our premium potting mix. For succulents and cacti, use our special well-draining soil mix." << std::endl;
        } else if(query.question.find("propagate") != std::string::npos) {
            std::cout << " Many plants can be propagated from cuttings! Bring in your plant and I'll show you the best method." << std::endl;
        } else {
            std::cout << " Based on my expertise, I'd recommend bringing in a photo or sample so I can give you the most accurate advice for your specific situation." << std::endl;
        }
    } else if(nextHandler != nullptr){
        std::cout << " Plant Expert: \"This requires management approval. Let me escalate this.\"" << std::endl;
        nextHandler->handleQuery(query);
    } else{
        std::cout << " Plant Expert: \"I'm unable to resolve this issue without management input.\"" << std::endl;
    }
}

bool PlantExpert::canHandle(const CustomerQuery &query) const{
    return query.type == CustomerQuery::CARE_ADVICE || 
           query.type == CustomerQuery::COMPLAINT ||
           query.question.find("plant") != std::string::npos ||
           query.question.find("care") != std::string::npos ||
           query.question.find("died") != std::string::npos ||
           query.question.find("dying") != std::string::npos ||
           query.question.find("health") != std::string::npos ||
           query.question.find("water") != std::string::npos ||
           query.question.find("light") != std::string::npos ||
           query.question.find("sun") != std::string::npos;
}