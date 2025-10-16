#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

namespace System {

	class App {
	public:
		int run();
	};

	class Command {
		std::string _user_input;
		std::stringstream _main_stream;
	public:
		Command(std::string input);
	};
	
	class File {
		
	};

}