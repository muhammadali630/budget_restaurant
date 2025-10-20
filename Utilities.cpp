#include "System.h"
#include "Restaurant.h"

bool System::u_is_number(std::string str) {
	for (const auto& x : str)
		if (!std::isdigit(x) and x !='.') return false;
	return true;
}

std::pair<bool, int> Restaurant::u_find_in_menu(
	std::string str, Restaurant::Menu& menu) {
	for (int i = 0;i < menu.get_menu().size();i++) {
		if (str == menu.get_menu()[i].get_name()) return { true ,i };
	}
	return { false , -1 };
}

std::string System::u_remove_spaces(std::string str) {
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end()); //shout out to Copilot
	return str;
}