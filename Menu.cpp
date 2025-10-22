#include "Restaurant.h"

System::Registry Restaurant::Menu::_reg = System::Map_S2F(
	{
	{"-display", [](const System::Command& cmd) {
		display_menu();
	}}
	}
);

Restaurant::Menu::Menu() {
	if (!System::File::exists("menu.log")) {
		std::cerr << "ERROR : menu.log not found" << std::endl;
		System::App::quit(1);
		return;
	}
	std::vector<std::string> lines = System::File::read_lines("menu.log");
	for (const std::string& line : lines) {
		std::stringstream ss(line);
		std::string name, price;
		ss >> name >> price;
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

const std::vector<Restaurant::Product>& Restaurant::Menu::get_menu() const{
	return _menu;
}

std::vector<Restaurant::Product>::const_iterator Restaurant::Menu::begin() const {
	return _menu.begin();
}
std::vector<Restaurant::Product>::const_iterator Restaurant::Menu::end() const {
	return _menu.end();
}

void Restaurant::Menu::handle(const System::Command& cmd) {
	_reg.initiate_sub_command(cmd);
}

std::ostream& Restaurant::operator<<(std::ostream& os, Restaurant::Menu& menu) {
	for (const auto& x : menu._menu)
		os << x << std::endl;
	return os;
}

void Restaurant::Menu::display_menu() {
	Menu menu;
	std::cout << menu;
}

std::pair<bool, int> Restaurant::Menu::find_in_menu(
	std::string str) {
	for (int i = 0;i < this->get_menu().size();i++) {
		if (str == this->get_menu()[i].get_name()) return { true ,i };
	}
	return { false , -1 };
}