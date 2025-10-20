#include "Restaurant.h"

//Restaurant::Menu::Menu(std::vector<Restaurant::Product> pdts) : _menu(pdts) {
//
//}

Restaurant::Menu::Menu() {
	if (!System::File::exists("menu.log")) {
		std::cerr << "ERROR : menu.log not found";
		System::App::quit(1);
		return;
	}
	std::vector<std::string> lines = System::File::read_lines("menu.log");
	for (const std::string& line : lines) {
		/*std::istringstream iss(line);
		std::string name;
		double price;*/
		std::stringstream ss(line);
		std::string name, price;
		ss >> name >> price;

		/*if (iss >> name >> price) {
			_menu.emplace_back(Restaurant::Product(name,price));
		}*/
		if (System::u_is_number(price)) {
			_menu.push_back(Restaurant::Product(name, std::stod(price)));
		}
		else {
			std::cerr << "ERROR : invalid line in menu.log" << std::endl
				<< "line : " << line;
			System::App::quit(1);
		}
	}
}

std::vector<Restaurant::Product> Restaurant::Menu::get_menu() {
	return _menu;
}

std::vector<Restaurant::Product>::const_iterator Restaurant::Menu::begin() const {
	return _menu.begin();
}
std::vector<Restaurant::Product>::const_iterator Restaurant::Menu::end() const {
	return _menu.end();
}

void Restaurant::Menu::handle(const System::Command& cmd) {
	return;
}

std::ostream& Restaurant::operator<<(std::ostream& os, Restaurant::Menu& menu) {
	for (const auto& x : menu._menu)
		os << x << std::endl;
	return os;
}