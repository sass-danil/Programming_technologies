/*
 * ProductsList.cpp
 *
 *  Created on: Apr 11, 2024
 *      Author: danil
 */

#include "ProductParser.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "IconParser.hpp"


extern Icon_Parser* icons_parser;


std::string name_to_lower_case(std::string name){
	unsigned long int i;
	//For English
	std::transform(name.begin(), name.end(), name.begin(),
		[](unsigned int c){ return std::tolower(c); });

	//For Russian
	std::vector <std::string> lc = {"_", "а", "б", "в", "г", "д", "е", "е", "е", "ж", "з", "и", "й", "к", "л", "м", "н", "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
	std::vector <std::string> uc   = {" ", "А", "Б", "В", "Г", "Д", "Е", "ё", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь","Э", "Ю", "Я"};
	for (i = 0; i < uc.size(); i++) {
		while (name.find(uc[i]) != std::string::npos){
			name.replace(name.find(uc[i]), uc[i].length(), lc[i]);
		}
	}
	return name;
}


Products_List::Products_List() {

}


Product* Products_List::get_element(std::string name){
	unsigned long int i;
	name = name_to_lower_case(name);

	for (i = 0; i < this->products.size(); i++){
		if (this->products[i]->check_name(name)){
			return this->products[i];
		}
	}
	std::cout << "From Products_List: can't find " << name << std::endl;

	return nullptr;
}


void Products_List::add_product(Product* product){
	this->products.push_back(product);
}


void Products_List::delete_product(Product* product){
	unsigned long int i;
	for (i = 0; i < this->products.size(); i++){
		if (this->products[i] == product){
			Product* temp_prod = this->products.back();
			this->products.back() = product;
			this->products[i] = temp_prod;
			this->products.pop_back();
			gtk_widget_destroy(product->get_box());
			this->update_gui();
			return;
		}
	}
}


extern GtkWidget* products_list_box;
void Products_List::update_gui(){
	unsigned long int i;
	for (i = 0; i < this->products.size(); i++){
		if (gtk_widget_get_parent(this->products[i]->get_box()) == products_list_box)
			gtk_box_reorder_child(GTK_BOX(products_list_box), this->products[i]->get_box(), i);
		else{
			this->products[i]->update_box();
		}
	}
}


void Products_List::print_into_console(){
	unsigned long int i;
	std::cout << "Products.size = " << products.size() << std::endl;
	for (i = 0; i < this->products.size(); i++){
		this->products[i]->print_into_console();
	}
}


void Products_List::print_into_file(const char* filename){
	std::fstream f;
	f.open(filename, std::fstream::out);
	std::cout << "Saving products to file " << filename << std::endl;
	if (!(f.is_open())){
		std::cout << "Can't open file " << filename << std::endl;
	}

	f << "<products>" << std::endl;
	int counter = 0;
	tm date;
	unsigned long int i;
	for (i = 0; i < this->products.size(); i++){
		f << "<product_name>" << std::endl;
		f << this->products[i]->get_name() << std::endl;
		f << "</product_name>" << std::endl;

		f << "<icon_ID>" << std::endl;
		f << this->products[i]->get_icon_id() << std::endl;
		f << "</icon_ID>" << std::endl;

		f << "<product_ID>" << std::endl;
		f << counter++ << std::endl;
		f << "</product_ID>" << std::endl;

		f << "<unit_ID>" << std::endl;
		f << (int)this->products[i]->get_unit() << std::endl;
		f << "</unit_ID>" << std::endl;

		f << "<count>" << std::endl;
		f << this->products[i]->get_count() << std::endl;
		f << "</count>" << std::endl;

		f << "<add_date>" << std::endl;
		date = this->products[i]->get_add_date();
		f << date.tm_mday << "." << date.tm_mon << "." << date.tm_year + 1900 << std::endl;
		f << "</add_date>" << std::endl;

		f << "<death_date>" << std::endl;
		date = this->products[i]->get_death_date();
		f << date.tm_mday << "." << date.tm_mon << "." << date.tm_year + 1900 << std::endl;
		f << "</death_date>" << std::endl;

		f << std::endl;
	}

	f << "</products>" << std::endl;
	f.close();
}


Products_List::~Products_List() {
	// TODO Auto-generated destructor stub
}

