#include "System.h"

System::App::App() = default;

int System::App::run() {
	_is_running = true;
	while (_is_running) {
		// ask for a command
		System::Command command;
		std::cin >> command;
		// run the command
		_call_function(command);
		// if exit conditions are met, quit
	}
	return _return_value;
}

void System::App::quit(int result) { 
	_return_value = result;
	_is_running = false;
}

void System::App::_call_function(Command command){
	if (command.is_empty()) return;
	System::Registry reg;
	reg.initiate_command(command);
}
