#include "Restaurant.h"

System::Registry Restaurant::Order::_reg = System::Map_S2F(
    {
    {"-new", [](const System::Command& cmd) {
        new_order(cmd);
    }},
    {"-cancel", [](const System::Command& cmd) {
        change_order(Status::cancelled, cmd);
    }},
    {"-review", [](const System::Command& cmd) {
        review_order(cmd);
    }},
    {"-deliver", [](const System::Command& cmd) {
        change_order(Status::delivered, cmd);
    }},
    {"-change", [](const System::Command& cmd) {
        change_order(Status::changed ,cmd);
    }}
    }
);

void Restaurant::Order::_normalize(Order& order) {
    std::vector<std::pair<Product, unsigned int>> items;
    items.push_back(order._items[0]);
    for (int i = 1;i < order._items.size();i++) {
        bool found = false;
        for (int j = 0;j < items.size();j++) {
            if (items[j].first == order._items[i].first) { //repeated product
                items[j].second++;
                found = true;
                break;
            }
        }
        if (!found) items.push_back(order._items[i]); //is new!
    }
    order._items = items;
}

void Restaurant::Order::_save(Order& order) {
    std::string str = format_order(order);
    System::File::write("orders.log", str);
}

Restaurant::Order::Order() {

}

Restaurant::Order::Order(const System::Command& command) :
   _status(Status::in_progress) {
    if (command.end() < 3) {
        std::cerr << "ERROR : too few arguments";
        return;
    }
    _customer = (Customer(
        command[0], command[1], command[2]
    ));
    /*Restaurant::Menu menu;
    for (int i = 3;i <= command.end(); i++) {
        if (!Restaurant::u_find_in_menu(command[i], menu).first)
            continue;
        Product pdt = menu.get_menu()[Restaurant::u_find_in_menu(command[i], menu).second];
        if (i + 1 > command.end()) {
            if(Restaurant::u_find_in_menu(command[i], menu).first)
                _items.emplace_back(pdt, 1);
            continue;
        }
        unsigned int count = 1;
        if (System::u_is_number(command[i + 1])) {
            count = std::stoi(command[i + 1]);
            i++;
        }
        _items.emplace_back(pdt, count);
    }*/
    _items = Product::fill_product_list(
        System::Command::reduce(command, 3)
    );
    if (_items.empty()) {
        std::cerr << "ERROR : order is empty" << std::endl;
        return;
    }
    _normalize(*this);
}

//std::ostream& Restaurant::operator<<(std::ostream& os, const Order& order) {
//    for (const auto& x : order._items) {
//        const auto& pdt = x.first;
//        int quantity = x.second;
//        os << pdt.get_name() << " : "
//            << std::fixed << std::setprecision(2) << pdt.get_price()
//            << " $ (x" << quantity << "), ";
//    }
//    return os;
//}

void Restaurant::Order::handle(const System::Command& cmd) {
    _reg.initiate_sub_command(cmd);
}

void Restaurant::Order::new_order(const System::Command& cmd) {
    Order order(cmd);
    _save(order);
}

void Restaurant::Order::change_order(Status new_status, const System::Command& cmd) {
    if (cmd.is_empty()) {
        std::cerr << "ERROR : too few arguments" << std::endl;
        return;
    }
    if (not System::u_is_number(cmd[0])) {
        std::cerr << "ERROR : invalid command" << std::endl;
        return;
    }
    const unsigned int target_line = static_cast<const unsigned int>(std::stoi(cmd[0]));
    switch (new_status) {
    case Status::delivered:
        if (not(get_current_status(target_line) == Status::in_progress
            or get_current_status(target_line) == Status::changed)) {
            std::cerr << "ERROR : cancelled or already delivered" << std::endl;
            return;
        }
        System::File::modify_section(
            "orders.log",
            target_line,
            5,
            "delivered    "
        );
        break;
    case Status::cancelled:
        if (not(get_current_status(target_line) == Status::in_progress
            or get_current_status(target_line) == Status::changed)) {
            std::cerr << "ERROR : already cancelled or delivered" << std::endl;
            return;
        }
        System::File::modify_section(
            "orders.log",
            target_line,
            5,
            "cancelled    "
        );
        break;
    case Status::changed:
        std::vector<std::pair<Product, unsigned int>> items =
            Product::fill_product_list(
                System::Command::reduce(cmd, 1)
            );
        std::cout << System::Command::reduce(cmd, 1) << std::endl;
        if (items.empty()) {
            std::cerr << "ERROR : cannot put empty order" << std::endl;
            return;
        }
        System::File::modify_section(
            "orders.log",
            target_line,
            5,
            "changed      "
        );
        System::File::modify_section(
            "orders.log",
            target_line,
            6,
            Product::format_products(items).str()
        );
        break;
    }
}

//void Restaurant::Order::cancel_order(const System::Command& cmd) {
//    if (cmd.end() == 0 and System::u_is_number(cmd[0])) {
//        if (not System::File::exists("orders.log")) {
//            std::cerr << "ERROR : orders.log not found" << std::endl;
//            return;
//        }
//        int target_line = std::stoi(cmd[0]);
//        std::vector<std::string> lines = System::File::read_lines("orders.log");
//        if (target_line<1 or target_line> static_cast<int>(lines.size())) {
//            std::cerr << "ERROR : line number out of range" << std::endl;
//            return;
//        }
//        std::string line = lines[target_line - 1];
//        size_t last_pipe = line.rfind('|');
//        if (last_pipe == std::string::npos) {
//            std::cerr << "ERROR : malformed line" << std::endl;
//            return;
//        }
//        size_t second_last_pipe = line.rfind('|', last_pipe - 1);
//        if (second_last_pipe == std::string::npos) {
//            std::cerr << "ERROR : malformed line" << std::endl;
//            return;
//        }                                                                  
//        std::string updated_line = line.substr(0, second_last_pipe + 1) + "cancelled    " + line.substr(last_pipe);
//        System::File::modify_line("orders.log", target_line, updated_line);
//    }
//    else {
//        std::cerr << "ERROR : invalid command";
//    }
//}

//void Restaurant::Order::deliver_order(const System::Command& cmd) {
//    if (cmd.end() == 0 and System::u_is_number(cmd[0])) {
//        if (not System::File::exists("orders.log")) {
//            std::cerr << "ERROR : orders.log not found" << std::endl;
//            return;
//        }
//        int target_line = std::stoi(cmd[0]);
//        std::vector<std::string> lines = System::File::read_lines("orders.log");
//        if (target_line<1 or target_line> static_cast<int>(lines.size())) {
//            std::cerr << "ERROR : line number out of range" << std::endl;
//            return;
//        }
//        std::string line = lines[target_line - 1];
//        size_t last_pipe = line.rfind('|');
//        if (last_pipe == std::string::npos) {
//            std::cerr << "ERROR : malformed line" << std::endl;
//            return;
//        }
//        size_t second_last_pipe = line.rfind('|', last_pipe - 1);
//        if (second_last_pipe == std::string::npos) {
//            std::cerr << "ERROR : malformed line" << std::endl;
//            return;
//        }
//        std::string updated_line = line.substr(0, second_last_pipe + 1) + "delivered    " + line.substr(last_pipe);
//        System::File::modify_line("orders.log", target_line, updated_line);
//    }
//    else {
//        std::cerr<<"ERROR : invalid command";
//    }
//}

void Restaurant::Order::review_order(const System::Command& cmd) {
    if (not System::File::exists("orders.log")) {
        std::cerr << "ERROR : orders.log not found";
        return;
    }
    std::vector<std::string> lines = System::File::read_lines("orders.log");
    if (cmd.is_empty()) {
        int start = std::max(0, static_cast<int>(lines.size() - 10));
        for (int i = start; i < lines.size();i++)
            std::cout << lines[i] << std::endl;
    }
    else if (cmd.end() == 0 and System::u_is_number(cmd[0])) {
        int count = std::stoi(cmd[0]);
        int start = std::max(0, static_cast<int>(lines.size() - count));
        for (int i = start;i < lines.size();i++)
            std::cout << lines[i] << std::endl;
    }
    else std::cerr << "ERROR : invalid command" << std::endl;
}

Restaurant::Status Restaurant::Order::get_current_status(const unsigned int target_line) {
    if (not System::File::exists("orders.log")) {
        std::cerr << "ERROR : orders.log not found" << std::endl;
        return Status::invalid;
    }
    std::string line = System::File::read_line("orders.log", target_line);
    if (line.empty()) {
        std::cerr << "ERROR : invalid line" << std::endl;
        return Status::invalid;
    }
    size_t last_pipe = line.rfind('|');
    if (last_pipe == std::string::npos) return Status::invalid;
    size_t second_last_pipe = line.rfind('|', last_pipe - 1);
    if (second_last_pipe == std::string::npos) return Status::invalid;
    std::string status_str = line.substr(second_last_pipe + 1, last_pipe - second_last_pipe - 1);
    if (status_str == "in progress  ") return Status::in_progress;
    else if (status_str == "delivered    ") return Status::delivered;
    else if (status_str == "cancelled    ") return Status::cancelled;
    else return Status::invalid;
}

double Restaurant::Order::cost(Order& order) {
    double result = 0;
    for (const auto& x : order._items)
        result += x.first.get_price() * x.second;
    return result;
}

void Restaurant::Order::update_status(const short int stat) {
    switch (stat) {
    case 1:
        _status = Status::in_progress;
        break;
    case 2:
        _status = Status::delivered;
        break;
    case 3:
        _status = Status::cancelled;
        break;
    case 4:
        _status = Status::changed;
        break;
    default:
        std::cerr << "Invalid order status.";
        break;
    }
}

std::string Restaurant::Order::status() const {
    switch (_status) {
    case 1:
        return "in progress";
        break;
    case 2:
        return "delivered";
        break;
    case 3:
        return "cancelled";
        break;
    case 4:
        return "changed";
        break;
    default:
        std::cerr << "Error : invalid order status";
        break;
    }
}

std::string Restaurant::Order::format_order(Order& order) {
    unsigned int line_number =
        (!System::File::exists("orders.log") ?
            1 : System::File::count_lines("orders.log") + 1);
    std::ostringstream oss;
    oss << std::setw(8) << std::left << (std::to_string(line_number) + ".") << "|"
        << order._customer
        << std::setw(10) << std::left << ("$" + (static_cast<std::ostringstream&&>(
            std::ostringstream{} << std::fixed << std::setprecision(2) << cost(order)
            ).str())) << "|"
        << std::setw(12) << std::left << order.status() << " |"
        << std::left << Product::format_products(order._items).str();
    return oss.str();
}