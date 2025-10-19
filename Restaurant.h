#pragma once
#include "System.h"
#include <iostream>
#include <vector>

namespace Restaurant {

	class Product {
		std::string _name;
		double _price;
	public:
		Product(std::string name, double price);
		friend std::ostream& operator<<(std::ostream& os , const Product& pdt);
	};

	class Menu {
		std::vector<Product> _menu;
	public:
		Menu(std::vector<Product> pdts);
		Menu();
		friend std::ostream& operator<<(std::ostream& os, Menu& menu);
		void handle(const System::Command& cmd);
	};

	enum Status {
		in_progress = 1,
		delivered = 2 ,
		cancelled = 3,
		changed = 4,
	};

	class Order {
		Customer _customer;
		std::vector<std::string> _items;
		System::Registry _reg;
		Status _status;
	public:
		Order();
		void handle(const System::Command& cmd);
		void new_order(const System::Command& cmd);
		void change_order();
		void deliver_order();
		void cancel_order();
		void update_status(const short int stat);
		short int status() const;

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


//next episode:
