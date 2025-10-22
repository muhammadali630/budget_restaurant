#include "Restaurant.h"

std::string Restaurant::Order::ORDER_LOG_FILE = "orders.log";

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

void Restaurant::Order::_normalize() {
    std::vector<std::pair<Product, unsigned int>> items;
    items.push_back(this->_items[0]);
    for (int i = 1;i < this->_items.size();i++) {
        bool found = false;
        for (int j = 0;j < items.size();j++) {
            if (items[j].first == this->_items[i].first) { //repeated product
                items[j].second++;
                found = true;
                break;
            }
        }
        if (!found) items.push_back(this->_items[i]); //is new!
    }
    this->_items = items;
}

void Restaurant::Order::_save() {
    std::string str = this->format_order();
    System::File::write(ORDER_LOG_FILE, str);
}

Restaurant::Order::Order(const System::Command& command) :
   _status(Status::in_progress) {
    if (command.end() < 3) {
        std::cerr << "ERROR : too few arguments" << std::endl;
        return;
    }
    _customer = (Customer(
        command[0], command[1], command[2]
    ));
    _items = Product::fill_product_list(
        System::Command::reduce(command, 3)
    );
    if (_items.empty()) {
        std::cerr << "ERROR : order is empty" << std::endl;
        return;
    }
    _normalize();
}

void Restaurant::Order::handle(const System::Command& cmd) {
    _reg.initiate_sub_command(cmd);
}

void Restaurant::Order::new_order(const System::Command& cmd) {
    Order order(cmd);
    order._save();
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
            std::cout << get_current_status(target_line) << std::endl;
            return;
        }
        System::File::modify_section(
            ORDER_LOG_FILE,
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
            ORDER_LOG_FILE,
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
        if (items.empty()) {
            std::cerr << "ERROR : cannot put empty order" << std::endl;
            return;
        }
        System::File::modify_section(
            ORDER_LOG_FILE,
            target_line,
            5,
            "changed      "
        );
        System::File::modify_section(
            ORDER_LOG_FILE,
            target_line,
            6,
            Product::format_products(items)
        );
        break;
    }
}

void Restaurant::Order::review_order(const System::Command& cmd) {
    if (not System::File::exists(ORDER_LOG_FILE)) {
        std::cerr << "ERROR : orders.log not found" << std::endl;
        return;
    }
    std::vector<std::string> lines = System::File::read_lines(ORDER_LOG_FILE);
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
    if (not System::File::exists(ORDER_LOG_FILE)) {
        std::cerr << "ERROR : orders.log not found" << std::endl;
        return Status::invalid;
    }
    std::string status_str = System::File::get_section(ORDER_LOG_FILE, target_line, 5);
    if (System::u_remove_spaces(status_str) == "inprogress") return Status::in_progress;
    else if (System::u_remove_spaces(status_str) == "delivered") return Status::delivered;
    else if (System::u_remove_spaces(status_str) == "cancelled") return Status::cancelled;
    else if (System::u_remove_spaces(status_str) == "changed") return Status::changed;
    else return Status::invalid;
}

double Restaurant::Order::cost() {
    double result = 0;
    for (const auto& x : this->_items)
        result += x.first.get_price() * x.second;
    return result;
}

void Restaurant::Order::update_status(const Status s) {
    _status = s;
}

std::string Restaurant::Order::status() const {
    switch (_status) {
    case Status::in_progress:
        return "in progress";
        break;
    case Status::delivered:
        return "delivered";
        break;
    case Status::cancelled:
        return "cancelled";
        break;
    case Status::changed:
        return "changed";
        break;
    default:
        return "invalid";
        break;
    }
}

std::string Restaurant::Order::format_order() {
    unsigned int line_number =
        (!System::File::exists(ORDER_LOG_FILE) ?
            1 : System::File::count_lines(ORDER_LOG_FILE) + 1);
    std::ostringstream oss;
    oss << std::setw(8) << std::left << (std::to_string(line_number) + ".") << "|"
        << this->_customer
        << std::setw(10) << std::left << ("$" + (static_cast<std::ostringstream&&>(
            std::ostringstream{} << std::fixed << std::setprecision(2) << this->cost()
            ).str())) << "|"
        << std::setw(12) << std::left << this->status() << " |"
        << std::left << Product::format_products(this->_items);
    return oss.str();
}