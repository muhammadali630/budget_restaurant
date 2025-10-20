#pragma once
#include "System.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

namespace Restaurant {

	class Customer {
		std::string _first_name;
		std::string _last_name;
		std::string _student_num;
	public:
		Customer(std::string first, std::string last, std::string number);
		Customer();
		friend std::ostream& operator<<(std::ostream& os, const Customer& ctm);
		void history();
	};

	class Product {
		std::string _name;
		double _price;
	public:
		Product(std::string name, double price);
		std::string get_name() const;
		double get_price() const;
		friend std::ostream& operator<<(std::ostream& os , const Product& pdt);
		bool operator==(const Product&pdt);
		static std::vector<std::pair<Product, unsigned int>> fill_product_list(const System::Command& cmd);
		static std::ostringstream format_products(
			std::vector<std::pair<Product, unsigned int>> items
		);
	};

	class Menu {
		std::vector<Product> _menu;
	public:
		//Menu(std::vector<Product> pdts);
		Menu();
		std::vector<Product> get_menu();
		std::vector<Product>::const_iterator begin() const;
		std::vector<Product>::const_iterator end() const;
		friend std::ostream& operator<<(std::ostream& os, Menu& menu);
		static void handle(const System::Command& cmd);
	};

	enum Status {
		invalid = 0,
		in_progress = 1,
		delivered = 2,
		cancelled = 3,
		changed = 4,
	};

	class Order {
		static System::Registry _reg;
		Restaurant::Customer _customer;
		std::vector<std::pair<Product, unsigned int>> _items;
		Status _status;
		static void _normalize(Order& order);
		static void _save(Order& order);
	public:
		Order();
		Order(const System::Command& cmd);
		//friend std::ostream& operator<<(std::ostream& os, const Order& order);
		static void handle(const System::Command& cmd);
		static void new_order(const System::Command& cmd);
		static void change_order(Status new_status, const System::Command& cmd);
		static Status get_current_status(const unsigned int target_line);
		void update_status(const short int stat);
		static void review_order(const System::Command& cmd);
		static double cost(Order& order);
		std::string status() const;
		static std::string format_order(Order& order);
	};

	std::pair<bool, int> u_find_in_menu(
		std::string str, Menu& menu
	);
}