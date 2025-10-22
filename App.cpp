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
	{"quit", [](const System::Command& cmd) {
		if (cmd.is_empty()) quit(0);
		else std::cerr << "ERROR : invalid command" << std::endl;
	}}
	});

int System::App::run() {
	_is_running = true;
	while (_is_running) {
		std::cout << ">";
		System::Command command;
		std::cin >> command; // ask for a command
		main_loop(command); // run the command
		//test_loop(); // test your app via test loop
	}
	return _return_value;
}

void System::App::main_loop(Command command){
	if (command.is_empty()) return;
	_reg.initiate_sub_command(command);
} 

void System::App::test_loop(){
	//test your app here
	return;
}

void System::App::quit(int result) { 
	_return_value = result;
	_is_running = false;
}