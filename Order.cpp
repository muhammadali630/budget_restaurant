#include "Restaurant.h"

void Restaurant::Order::handle(std::vector<std::string> args) {
	for (const auto& x : args) std::cout << x << std::endl;
}