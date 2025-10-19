#include "Restaurant.h"

Restaurant::Product::Product(std::string name , double price) : 
    _name(name) , _price (price){

}

std::ostream& Restaurant::operator<<(std::ostream& os, const Restaurant::Product& pdt){
    os<<pdt._name<<" : "<<pdt._price<<" $";
    return os;
}