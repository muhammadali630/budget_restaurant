#include "Restaurant.h"

Restaurant::Product::Product(std::string name , double price) : 
    _name(name) , _price (price){

}

std::string Restaurant::Product::get_name() const {
    return _name;
}

double Restaurant::Product::get_price() const {
    return _price;
}

std::ostream& Restaurant::operator<<(std::ostream& os, const Restaurant::Product& pdt){
    os << std::left << pdt._name << " : " << std::left << pdt._price << " $";
    return os;
}

bool Restaurant::Product::operator== (const Product& pdt) {
    return (this->_name == pdt._name and this->_price == pdt._price);
}

std::vector<std::pair<Restaurant::Product, unsigned int>> 
Restaurant::Product::fill_product_list(const System::Command& cmd) {
    std::vector<std::pair<Restaurant::Product, unsigned int>> items;
    Restaurant::Menu menu;
    for (int i = 0;i <= cmd.end(); i++) {
        if (!menu.find_in_menu(cmd[i]).first)
            continue;
        Product pdt = menu.get_menu()[menu.find_in_menu(cmd[i]).second];
        if (i + 1 > cmd.end()) {
            if (menu.find_in_menu(cmd[i]).first)
                items.emplace_back(pdt, 1);
            continue;
        }
        unsigned int count = 1;
        if (System::u_is_number(cmd[i + 1])) {
            count = std::stoi(cmd[i + 1]);
            i++;
        }
        items.emplace_back(pdt, count);
    }
    return items;
}

std::string Restaurant::Product::format_products(
    std::vector<std::pair<Product, unsigned int>> items
) {
    std::ostringstream oss;
    for (const auto& x : items) {
        const auto& pdt = x.first;
        int quantity = x.second;
        oss << pdt.get_name() << " : "
            << std::fixed << std::setprecision(2) << pdt.get_price()
            << " $ (x" << quantity << "), ";
    }
    return oss.str();
}