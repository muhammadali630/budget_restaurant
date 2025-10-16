#pragma once
#include <iostream>
#include <vector>

namespace Restaurant {

	class Product {
		std::string _name;
		double _price;
	public:
		Product(std::string name, double price);
	};

	class Menu {
		std::vector<Product> _menu;
	public:
		Menu();
	};

	class Order {
	public:
		void new_order();
		void change_order();
		void deliver_order();
		void cancel_order();

	};

	class Customer {
		std::string _first_name;
		std::string _last_name;
		std::string _student_num;
	public:
		Customer(std::string first, std::string last, std::string number);
		void history();
	};

}