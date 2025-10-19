#include "Restaurant.h"

Restaurant::Order::Order() = default;

Restaurant::Order::Order() : _reg(
	System::Map_S2F (
		{
        {"-new", [&](const System::Command& cmd) {
            new_order(cmd);
        }},
        {"-cancel", [](const System::Command& cmd) {
            std::cout << "You canceled your order with args" << std::endl;
            std::cout << cmd << std::endl;
        }}
    }
	)
) {

}

void Restaurant::Order::handle(const System::Command& cmd) {
    _reg.initiate_sub_command(cmd);
}

void Restaurant::Order::new_order(const System::Command& cmd) {
    
}