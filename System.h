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
		Command(std::string input);
		Command();
		friend std::ostream& operator<<(std::ostream& os, const Command& command);
		friend std::istream& operator>>(std::istream& is, Command& command);
		std::string operator[](int index);
		std::vector<std::string> get_args() const;
		bool is_empty() const;
	};

	class Registry {
		static std::unordered_map <
			std::string,
			std::function<void(const std::vector<std::string>& args)>>
			_registry;
	public:
		Registry();
		void initiate_command(Command command);
	};

	class App {
		bool _is_running;
		int _return_value;
		void _call_function(System::Command command);
	public:
		App();
		int run();
		void quit(int result);
	};

	class File {
		
	};

}