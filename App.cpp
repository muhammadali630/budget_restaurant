#include "System.h"
#include "Restaurant.h"

bool System::App::_is_running;

int System::App::_return_value;

System::App::App() {

}
 
System::Registry System::App::_reg = System::Map_S2F({
	{"order", [](const System::Command& cmd) {
		Restaurant::Order::handle(cmd);
	}},
	{"menu", [](const System::Command& cmd) {
		Restaurant::Menu::handle(cmd);
	}},
	{"customer", [](const System::Command& cmd) {
		Restaurant::Customer::handle(cmd);
	}},
	{"quit", [](const System::Command&) {
		quit(0);
	}}
	});

int System::App::run() {
	_is_running = true;
	while (_is_running) {
		// ask for a command
		System::Command command;
		std::cin >> command;
		// run the command
		main_loop(command);
		//test_loop();
		// if exit conditions are met, quit
	}
	return _return_value;
}

void System::App::main_loop(Command command){
	if (command.is_empty()) return;
	_reg.initiate_sub_command(command);
} 

void System::App::test_loop(){
	// std::vector<Restaurant::Product> products = {
    // 	Restaurant::Product("Pizza", 12.99),
    // 	Restaurant::Product("Burger", 8.49),
    // 	Restaurant::Product("Salad", 6.75)
	// };
	// Restaurant::Menu menu(products);
	// std::cout<<menu;
	//quit(0);
	Restaurant::Menu menu;
	std::cout << menu;
}

void System::App::quit(int result) { 
	_return_value = result;
	_is_running = false;
}