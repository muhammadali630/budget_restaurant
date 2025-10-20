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
	std::ifstream in(name);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(in, line)) {
		lines.push_back(line);
	}
	return lines;
}

std::string System::File::read_line( //requires an index , NOT a line number
	const std::string& name,
	const unsigned int index // index = line number - 1;
) {
	std::ifstream in(name);
	std::vector<std::string> lines;
	std::string line;
	while (std::getline(in, line)) {
		lines.push_back(line);
	}
	return lines[index];
}

bool System::File::exists(
	const std::string& name
) {
	std::ifstream file(name);
	return file.good();
}

unsigned int System::File::count_lines
(const std::string& name) {
	if (!exists(name)) {
		std::cerr << "Error : " << name << " nod found" << std::endl;
		return 0;
	}
	std::ifstream in(name);
	std::string line;
	unsigned int count = 0;
	while (std::getline(in, line)) count++;
	return count;
}

void System::File::modify_line(
	const std::string& name,
	const unsigned int line_number,
	const std::string& new_line
) {
	if (not exists(name)) {
		std::cerr << "ERROR : " << name << " not found" << std::endl;
		return;
	}
	std::vector<std::string> lines = read_lines(name);
	if (line_number<1 or line_number>static_cast<int>(lines.size())) {
		std::cerr << "ERROR : line number out of range" << std::endl;
		return;
	}
	lines[line_number - 1] = new_line;
	std::ofstream out(name, std::ios::trunc); //empty the file
	if (not out) {
		std::cerr << "FATAL ERROR : unable to write file" << std::endl;
		std::cerr << "FATAL ERROR : data lost" << std::endl;
		return;
	}
	for (const auto& line : lines)
		out << line << '\n';
}

void System::File::modify_section(
	const std::string& name,
	const unsigned int line_number,
	const unsigned int section_index,
	const std::string& new_value
) {
	if (!System::File::exists(name)) {
		std::cerr << "ERROR : " << name << " not found" << std::endl;
		return;
	}
	std::string line = System::File::read_line(name, line_number - 1);
	if (line.empty()) {
		std::cerr << "ERROR : line invalid" << std::endl;
		return;
	}
	std::vector<std::string> sections;
	std::stringstream ss(line);
	std::string section;
	while (std::getline(ss, section, '|')) {
		sections.push_back(section);
	}
	if (section_index >= sections.size()) {
		std::cerr << "ERROR : index out of range" << std::endl;
		return;
	}
	sections[section_index] = new_value;
	std::string new_line;
	for (int i = 0;i < sections.size();i++) {
		new_line += sections[i];
		if (i != sections.size() - 1) new_line += "|";
	}
	modify_line(name, line_number, new_line);
}

std::string System::File::get_section(
	const std::string name,
	const unsigned int line_number,
	const unsigned int section_index
) {
	if (!System::File::exists(name)) {
		std::cerr << "ERROR : " << name << " not found" << std::endl;
		return "";
	}
	std::string line = System::File::read_line(name, line_number - 1);
	if (line.empty()) {
		std::cerr << "ERROR : line invalid" << std::endl;
		return "";
	}
	std::vector<std::string> sections;
	std::stringstream ss(line);
	std::string section;
	while (std::getline(ss, section, '|')) {
		sections.push_back(section);
	}
	return sections[section_index];
}