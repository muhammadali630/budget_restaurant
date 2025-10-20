#include "Restaurant.h"

System::Registry Restaurant::Customer::_reg = System::Map_S2F(
    {
    {"-history", [](const System::Command& cmd) {
        history(cmd);
    }}
    }
);

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

void Restaurant::Customer::handle(const System::Command& cmd) {
    _reg.initiate_sub_command(cmd);
}

void Restaurant::Customer::history(const System::Command& cmd) {
    if (cmd.end() != 2) {
        std::cerr << "ERROR : invalid command" << std::endl;
        return;
    }
    Customer ctm(cmd[0], cmd[1], cmd[2]);
    unsigned int count = 0;
    for (int i = 1;i <= System::File::count_lines("orders.log");i++) {
        if (System::u_remove_spaces(System::File::get_section("orders.log", i, 1)) == ctm._first_name
            and System::u_remove_spaces(System::File::get_section("orders.log", i, 2)) == ctm._last_name
            and System::u_remove_spaces(System::File::get_section("orders.log", i, 3)) == ctm._student_num) {
            count++;
            std::cout << System::File::read_line("orders.log", i - 1) << std::endl;
        }
    }
    std::cout << "total " << count << " orders" << std::endl;
}