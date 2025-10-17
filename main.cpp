#include <iostream>
#include "Restaurant.h"
#include "System.h"

int main() {
	//std::cout << "Hello IUT";
	/*std::string temp;
	std::getline(std::cin, temp);
	System::Command command(temp);
	std::cout << command << std::endl;
	std::cout << command[0];*/
	System::App app;
	return app.run();
}