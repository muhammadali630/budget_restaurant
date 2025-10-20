#include "System.h"
#include "Restaurant.h"

System::Registry::Registry() {

}

System::Registry::Registry(Map_S2F reg) : _sub_registry(reg) {

}

void System::Registry::initiate_sub_command(Command command){
	if (command.is_empty()) return;
	auto it = _sub_registry.find(command[0]);
	if (it != _sub_registry.end()) {
		it->second(Command::reduce(command, 1));
	}
	else std::cerr << "Invalid command" << std::endl;
}