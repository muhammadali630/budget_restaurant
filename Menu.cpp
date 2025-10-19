#include "Restaurant.h"

Restaurant::Menu::Menu(std::vector<Restaurant::Product> pdts) : _menu(pdts) {

}

Restaurant::Menu::Menu() = default;

void Restaurant::Menu::handle(const System::Command& cmd) {
	return;
}

std::ostream& Restaurant::operator<<(std::ostream& os, Restaurant::Menu& menu) {
	for (const auto& x : menu._menu)
		os << x << std::endl;
	return os;
}