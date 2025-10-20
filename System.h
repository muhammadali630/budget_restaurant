#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <functional>
#include <unordered_map>
#include <utility>
#include <iomanip>

namespace System {

	class Command {
		std::vector<std::string> _arg_vector;
		void _split(std::string _user_input);
	public:
		Command(const std::vector<std::string>& args);
		Command(std::string input);
		Command();
		friend std::ostream& operator<<(std::ostream& os, const Command& command);
		friend std::istream& operator>>(std::istream& is, Command& command);
		std::string operator[](int index) const;
		std::vector<std::string> get_args() const;
		bool is_empty() const;
		unsigned int end() const;
		static Command reduce(
			const Command& cmd, 
			const unsigned int index
		);
	};

	using Map_S2F = std::unordered_map <
			std::string,
			std::function<void(const Command& cmd)>>;

	class Registry {
		Map_S2F _sub_registry;
	public:
		Registry(Map_S2F cmd);
		Registry();
		void initiate_sub_command(Command command);
	};

	class App {
		static Registry _reg;
		static bool _is_running;
		static int _return_value;
	public:
		App();
		int run();
		void main_loop(Command command);
		void test_loop();
		static void quit(int result);
	};

	class File {
	public:
		static void write(
			const std::string& name,
			const std::string& content);
		static std::vector<std::string> read_lines(
			const std::string& name
		);
		static std::string read_line(
			const std::string& name,
			const unsigned int index
		);
		static bool exists(const std::string& name);
		static unsigned int count_lines
		(const std::string& name);
		static void modify_line(
			const std::string& name,
			const unsigned int line_number,
			const std::string& new_line
		);
		static void modify_section(
			const std::string& name,
			const unsigned int line_number,
			const unsigned int section_index,
			const std::string& new_value
		);
		static std::string get_section(
			const std::string name,
			const unsigned int line_number,
			const unsigned int section_index
		);
	};

	bool u_is_number(std::string str);

	std::string u_remove_spaces(std::string str);
}