#include "System.h"
#include "Restaurant.h"

bool System::u_is_number(std::string str) {
	for (const auto& x : str)
		if (!std::isdigit(x) and x !='.') return false;
	return true;
}



std::string System::u_remove_spaces(std::string str) {
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end()); //shout out to Copilot
	return str;
}

inline std::string Restaurant::status_to_string(Status s) {
	switch (s) {
	case Restaurant::invalid: return "invalid";
	case Restaurant::in_progress: return "in progress";
	case Restaurant::delivered: return "delivered";
	case Restaurant::cancelled: return "cancelled";
	case Restaurant::changed: return "changed";
	default: return "unknown";
	}
}