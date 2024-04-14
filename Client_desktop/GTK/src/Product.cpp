/*
 * Product.cpp
 *
 *  Created on: Apr 11, 2024
 *      Author: danil
 */

#include "Product.hpp"
#include <iostream>
#include <map>
#include "IconParser.hpp"


extern std::map<char, std::string> measures_map;
extern Icon_Parser* icons_parser;


extern std::string name_to_lower_case(std::string name);


Product::Product() {
	this->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
	this->icon = NULL;
	this->product_label = gtk_label_new("");
	this->add_date_label = gtk_label_new("");
	this->death_date_label = gtk_label_new("");
	this->count_label = gtk_label_new("");
	this->unit = 0;
	this->product_id = -1;
	this->count = 0;
	this->icon_id = 0;
}


Product::Product(std::string product_name) : Product(){
	gtk_label_set_text(GTK_LABEL(this->product_label), product_name.c_str());
	this->product_names.push_back(name_to_lower_case(product_name));
	icons_parser->append_icon_names_to_vector(icons_parser->get_icon_name_id(this->product_names[0]), &(this->product_names));
}



void Product::set_icon_id(int id){
	this->icon_id = id;
}



void Product::set_count(std::string count){
	this->count = stof(count);
}


void Product::set_add_date(std::string date){
	sscanf(date.c_str(), "%d.%d.%d", &this->add_date.tm_mday, &this->add_date.tm_mon, &this->add_date.tm_year);
	this->add_date.tm_year -= 1900;
}


void Product::set_death_date(std::string date){
	sscanf(date.c_str(), "%d.%d.%d", &this->death_date.tm_mday, &this->death_date.tm_mon, &this->death_date.tm_year);
	this->death_date.tm_year -= 1900;
}



bool Product::check_name(std::string name){
	unsigned long int i;
	for (i = 0; i < this->product_names.size(); i++){
		if (name == this->product_names[i]){
			return true;
		}
	}

	return false;
}



void Product::update_box(){
	GtkWidget *new_icon = gtk_image_new_from_pixbuf(gtk_image_get_pixbuf(GTK_IMAGE(this->icon)));
	gtk_box_pack_start(GTK_BOX(this->box), new_icon, false, false, 3);
	gtk_box_pack_start(GTK_BOX(this->box), this->product_label, false, false, 3);

	char s[15];
	sprintf(s, "%d.%d.%d", this->add_date.tm_mday, this->add_date.tm_mon, this->add_date.tm_year + 1900);
	gtk_label_set_text(GTK_LABEL(this->add_date_label), (std::string("Was added ") + s).c_str());
	gtk_box_pack_start(GTK_BOX(this->box), this->add_date_label, false, false, 3);

	sprintf(s, "%d.%d.%d", this->death_date.tm_mday, this->death_date.tm_mon, this->death_date.tm_year + 1900);
	gtk_label_set_text(GTK_LABEL(this->death_date_label), (std::string("Death date: ") + s).c_str());
	gtk_box_pack_start(GTK_BOX(this->box), this->death_date_label, false, false, 3);

	sprintf(s, "%.3f", this->count);
	gtk_label_set_text(GTK_LABEL(this->count_label), (std::string(s) + " " + measures_map[this->unit]).c_str());
	gtk_box_pack_start(GTK_BOX(this->box), this->count_label, false, false, 3);
}



void Product::print_into_console(){
	std::cout << "product_names :" << gtk_label_get_text(GTK_LABEL(this->product_label)) << std::endl;
	unsigned int long i;
	for (i = 0; i < this->product_names.size(); i++){
		std::cout << "\t" << this->product_names[i] << std::endl;
	}
	std::cout << "product_ID " << this->product_id << std::endl;
	std::cout << "unit_ID " << (int)this->unit << ": " << measures_map[this->unit] << std::endl;
	std::cout << "Count " << this->count << std::endl;
	std::cout << "add_date " << this->add_date.tm_mday << "." << this->add_date.tm_mon << "." << this->add_date.tm_year + 1900 << std::endl;
	std::cout << "death_date " << this->death_date.tm_mday << "." << this->death_date.tm_mon << "." << this->death_date.tm_year + 1900 << std::endl;
}



Product::~Product() {
	// TODO Auto-generated destructor stub
}

