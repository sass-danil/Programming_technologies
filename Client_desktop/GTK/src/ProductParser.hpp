/*
 * ProductParser.hpp
 *
 *  Created on: Apr 11, 2024
 *      Author: danil
 */

#ifndef PRODUCTPARSER_HPP_
#define PRODUCTPARSER_HPP_

#include "ProductsList.hpp"

class Product_Parser {
	public:
		Product_Parser();


		void parse_products(Products_List* list, const char *filename);

		void add_products_to_box(Products_List *list, GtkWidget *box);


		virtual ~Product_Parser();
};

#endif /* PRODUCTPARSER_HPP_ */
