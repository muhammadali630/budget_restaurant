#pragma once
#include "System.h"
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

namespace Restaurant {

	class Customer {
		static System::Registry _reg;
		std::string _first_name;
		std::string _last_name;
		std::string _student_num;
	public:
		Customer(std::string first, std::string last, std::string number);
		Customer();
		friend std::ostream& operator<<(std::ostream& os, const Customer& ctm);
		static void handle(const System::Command& cmd);
		static void history(const System::Command& cmd);
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
		static std::string format_products(
			std::vector<std::pair<Product, unsigned int>> items
		);
	};

	class Menu {
		static System::Registry _reg;
		std::vector<Product> _menu;
	public:
		Menu();
		const std::vector<Product>& get_menu() const;
		std::vector<Product>::const_iterator begin() const;
		std::vector<Product>::const_iterator end() const;
		friend std::ostream& operator<<(std::ostream& os, Menu& menu);
		static void handle(const System::Command& cmd);
		static void display_menu();
		std::pair<bool, int> find_in_menu(std::string str);
	};

	enum Status {
		invalid = 0,
		in_progress = 1,
		delivered = 2,
		cancelled = 3,
		changed = 4,
	};

	inline std::string status_to_string(Status s);

	class Order {
		static std::string ORDER_LOG_FILE;
		static System::Registry _reg;
		Restaurant::Customer _customer;
		std::vector<std::pair<Product, unsigned int>> _items;
		Status _status;
		void _normalize();
		void _save();
	public:
		Order(const System::Command& cmd);
		static void handle(const System::Command& cmd);
		static void new_order(const System::Command& cmd);
		static void change_order(Status new_status, const System::Command& cmd);
		static Status get_current_status(const unsigned int target_line);
		void update_status(Status);
		static void review_order(const System::Command& cmd);
		double cost();
		std::string status() const;
		std::string format_order();
	};

}