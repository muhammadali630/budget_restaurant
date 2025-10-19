#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <functional>
#include <unordered_map>

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
		std::string operator[](int index);
		std::vector<std::string> get_args() const;
		bool is_empty() const;
	};

	using Map_S2F = std::unordered_map <
			std::string,
			std::function<void(const Command& cmd)>>;

	class Registry {
		static Map_S2F _registry;
		Map_S2F _sub_registry;
	public:
		Registry(Map_S2F cmd);
		Registry();
		void initiate_command(Command command);
		void initiate_sub_command(Command command);
	};

	class App {
		bool _is_running;
		int _return_value;
	public:
		App();
		int run();
		void main_loop(Command command);
		void test_loop();
		void quit(int result);
	};

	class File {
	public:
		static void write(
			const std::string& name,
			const std::string& content);
		static std::vector<std::string> read_lines(
			const std::string& name
		);
		bool exists(const std::string& name) const;
	};

}