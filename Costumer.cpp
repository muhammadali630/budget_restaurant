#include "Restaurant.h"

Restaurant::Customer::Costumer(
    std::string first,
     std::string last,
      std::string number) : 
      _first_name(first),
      _last_name(last),
      _student_num(number){

      }

std::ostream& Restaurant::operator<<(
    std::ostream& os, Customer& ctm
){
    os<<ctm._first_name<<" "
    <<ctm._last_name<<" "
    <<ctm._first_name;
    return os;
}