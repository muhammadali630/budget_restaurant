#include "Restaurant.h"

Restaurant::Customer::Customer(
    std::string first,
     std::string last,
      std::string number) : 
      _first_name(first),
      _last_name(last),
      _student_num(number){

      }

Restaurant::Customer::Customer() {

}

std::ostream& Restaurant::operator<<(std::ostream& os, const Customer& ctm) {
    os << std::setw(10) << std::left << ctm._first_name << " |"
        << std::setw(10) << std::left << ctm._last_name << " |"
        << std::setw(10) << std::left << ctm._student_num << " |";
    return os;
}