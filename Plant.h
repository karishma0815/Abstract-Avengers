#ifndef PlANT_H
#define PlANT_H

#include <string>

class Plant{
//implement plant class
public:
    Plant(const std::string& type);
   //for pricerangeiterator
    double getPrice() const;
    void setPrice(double price);
     //for careiterator/planiterator
    std::string getType() const;
    std::string getCareInstructions() const;//
    //set care instructions gets called when staff adds a 
    void setCareInstructions(const std::string& instructions);

private:
    std::string type;
    std::string careInstruc;

};
#endif // PlANT_H