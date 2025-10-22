#include "System.h"

System::Command::Command(const std::vector<std::string>& args) : _arg_vector(args){
	
}

System::Command::Command(std::string input) {
	_split(input);
}

System::Command::Command() = default;

void System::Command::_split(std::string _user_input) {
	for (const auto& x : _user_input) {
		if (x == '|') {
			std::cerr << "ERROR : forbidden character : | (pipe)" << std::endl;
			return;
		}
	}
	for (auto& x : _user_input)
		x = std::tolower(static_cast<unsigned char>(x));
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

std::string System::Command::operator[](int index) const {
	if (index < 0 or index >= static_cast<int>(_arg_vector.size())) {
		std::cerr << "error : command index out of bounds" << std::endl;
		return "";
	}
	return _arg_vector.at(index);
}

std::vector<std::string> System::Command::get_args() const {
	return _arg_vector;
}

bool System::Command::is_empty() const { return _arg_vector.empty(); }

unsigned int System::Command::end() const {
	return _arg_vector.size() - 1;
} // returns the last valid index inside command[]

System::Command System::Command::reduce(const Command& cmd, const unsigned int index) {
	//sub command starting at index (index)
	std::vector<std::string> new_arg_vector;
	for (int i = index;i <= cmd.end();i++) {
		new_arg_vector.push_back(cmd[i]);
	}
	return Command(new_arg_vector);
}