#include "System.h"

void System::File::write(
	const std::string& name, 
	const std::string& content) {
	std::ofstream out(name, std::ios::app);
	if (out) out << content << "\n";
}

std::vector<std::string> System::File::read_lines(
	const std::string& name
) {
	std::ifstream in;
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(in, line)) {
		lines.push_back(line);
	}
	return lines;
}

bool System::File::exists(
	const std::string& name
) const {
	std::ifstream file(name);
	return file.good();
}