/*
 * ProductsList.hpp
 *
 *  Created on: Apr 11, 2024
 *      Author: danil
 */

#ifndef PRODUCTSLIST_HPP_
#define PRODUCTSLIST_HPP_

#include "Product.hpp"

class Products_List {
	public:
		Products_List();


		unsigned long int get_size(){ return this->products.size(); }

		Product* get_element(unsigned long int i){ return this->products[i]; }

		Product* get_element(std::string name);


		void add_product(Product* product);

		void delete_product(Product* product);

		void update_gui();

		void print_into_console();

		void print_into_file(const char* filename);

		virtual ~Products_List();

	public:
		std::vector<Product*> products;
};

#endif /* PRODUCTSLIST_HPP_ */
