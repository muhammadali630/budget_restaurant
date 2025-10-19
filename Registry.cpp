#include "System.h"
#include "Restaurant.h"

System::Map_S2F System::Registry::_registry;

System::Registry::Registry() {
	_registry["order"] = [](const std::vector<std::string>& args) {
		Restaurant::Order order;
		order.handle(args);
		};
	_registry["menu"] = [](const std::vector<std::string>& args) {
		Restaurant::Menu menu;
		menu.handle(args);
		};
}

System::Registry::Registry(Map_S2F reg) : _sub_registry(reg) {

}

void System::Registry::initiate_command(System::Command command) {
	if (command.is_empty()) return;
	auto it = _registry.find(command[0]);
	if (it != _registry.end()) {
		std::vector<std::string> args = command.get_args();
		args.erase(args.begin()); // find a better way later
		it->second(args);
	}
	else std::cerr << "Invalid command";
}

void System::Registry::initiate_sub_command(Command command){
		if (command.is_empty()) return;
	auto it = _sub_registry.find(command[0]);
	if (it != _sub_registry.end()) {
		std::vector<std::string> args = command.get_args();
		args.erase(args.begin()); // find a better way later
		it->second(args);
	}
	else std::cerr << "Invalid command";
}