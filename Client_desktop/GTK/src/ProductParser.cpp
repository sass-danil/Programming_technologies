/*
 * ProductParser.cpp
 *
 *  Created on: Apr 11, 2024
 *      Author: danil
 */

#include "ProductParser.hpp"
#include <iostream>
#include <fstream>
#include "IconParser.hpp"

extern Icon_Parser* icons_parser;

Product_Parser::Product_Parser() {
	// TODO Auto-generated constructor stub

}


void Product_Parser::parse_products(Products_List* list, const char *filename){
	std::setlocale(LC_NUMERIC, "POSIX");
	std::fstream f(filename);
	std::cout << "Parsing products from file " << filename << std::endl;
	if (!(f.is_open())){
		std::cout << "Can't open file " << filename << std::endl;
	}

	Product *temp_product = nullptr;

	std::string buffer;
	while (std::getline(f, buffer)){
		if (buffer == "<product_name>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at product_name reading" << std::endl;
				break;
			}
			else{
				if (temp_product != nullptr){
					list->add_product(temp_product);
				}

				temp_product = new Product(buffer);
			}
		}
		else if (buffer == "<icon_ID>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at icon ID reading" << std::endl;
				break;
			}
			temp_product->set_icon(icons_parser->get_icon(stoi(buffer)));
			temp_product->set_icon_id(stoi(buffer));
		}
		else if (buffer == "<product_ID>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at product ID reading" << std::endl;
				break;
			}
			temp_product->set_id(stoi(buffer));
		}
		else if (buffer == "<unit_ID>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at unit_ID reading" << std::endl;
				break;
			}
			temp_product->set_unit(stoi(buffer));
		}
		else if (buffer == "<count>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at count reading" << std::endl;
				break;
			}
			temp_product->set_count(buffer);
		}
		else if (buffer == "<add_date>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at add_date reading" << std::endl;
				break;
			}
			temp_product->set_add_date(buffer);
		}
		else if (buffer == "<death_date>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at death_date reading" << std::endl;
				break;
			}
			temp_product->set_death_date(buffer);
		}
		else if (buffer == "</products>"){
			list->add_product(temp_product);
			break;
		}
	}

	f.close();
}


void Product_Parser::add_products_to_box(Products_List *list, GtkWidget *box){
	unsigned long int i;
	list->update_gui();
	for (i = 0; i < list->get_size(); i++){
		gtk_box_pack_start(GTK_BOX(box), list->get_element(i)->get_box(), false, false, 3);
		std::cout << "Product " << i << " added to box" << std::endl;
	}
}


Product_Parser::~Product_Parser() {
	// TODO Auto-generated destructor stub
}

