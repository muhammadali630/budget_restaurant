#include "System.h"
#include "Restaurant.h"

//System::Registry::Registry() {
//	_registry["order"] = [](const Command& cmd) {
//		Restaurant::Order order;
//		order.handle(cmd);
//		};
//	_registry["menu"] = [](const Command& cmd) {
//		Restaurant::Menu menu;
//		menu.handle(cmd);
//		};
//}

System::Registry::Registry() {

}

System::Registry::Registry(Map_S2F reg) : _sub_registry(reg) {

}

//void System::Registry::initiate_command(System::Command command) {
//	if (command.is_empty()) return;
//	auto it = _registry.find(command[0]);
//	if (it != _registry.end()) {
//		std::vector<std::string> args = command.get_args();
//		args.erase(args.begin()); // find a better way later
//		it->second(Command(args));
//	}
//	else std::cerr << "Invalid command";
//}

void System::Registry::initiate_sub_command(Command command){
	if (command.is_empty()) return;
	auto it = _sub_registry.find(command[0]);
	if (it != _sub_registry.end()) {
		std::vector<std::string> args = command.get_args();
		args.erase(args.begin()); // find a better way later
		it->second(Command(args));
	}
	else std::cerr << "Invalid command";
}