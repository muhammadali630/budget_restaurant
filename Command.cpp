#include "System.h"

System::Command::Command(const std::vector<std::string>& args) : _arg_vector(args){
	
}

System::Command::Command(std::string input) {
	_split(input);
}

System::Command::Command() = default; // Java programmers be like

void System::Command::_split(std::string _user_input) {
	std::stringstream ss(_user_input);
	std::string word;
	while (ss >> word)
		_arg_vector.push_back(word);
}

std::ostream& System::operator<<(std::ostream& os, const System::Command& command) {
	for (const auto& x : command._arg_vector)
		os << x << " ";
	return os;
}


std::istream& System::operator>>(std::istream& is, System::Command& command) {
	std::string line;
	std::getline(is, line);
	command._split(line);
	return is;
}

std::string System::Command::operator[](int index) {
	return this->_arg_vector[index];
}

std::vector<std::string> System::Command::get_args() const {
	return _arg_vector;
}

bool System::Command::is_empty() const { return _arg_vector.empty(); }