#include "System.h"
#include "Restaurant.h"

System::App::App() = default;

int System::App::run() {
	_is_running = true;
	while (_is_running) {
		// ask for a command
		System::Command command;
		std::cin >> command;
		// run the command
		//main_loop(command);
		main_loop(command);
		// if exit conditions are met, quit
	}
	return _return_value;
}

void System::App::main_loop(Command command){
	if (command.is_empty()) return;
	System::Registry reg;
	reg.initiate_command(command);
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
}

void System::App::quit(int result) { 
	_return_value = result;
	_is_running = false;
}

