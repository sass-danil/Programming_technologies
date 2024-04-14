/*
 * IconParser.cpp
 *
 *  Created on: Mar 23, 2024
 *      Author: danil
 */

#include "IconParser.hpp"
#include <iostream>
#include <fstream>

Icon_Parser::Icon_Parser() {
	this->update();
}



GtkWidget* Icon_Parser::get_icon(int index){
	unsigned long int i;
	for (i = 0; i < this->icons_names.size(); i++){
		if (this->icons_names[i]->check_id(index)){
			return this->icons_names[i]->get_icon();
		}
	}
	return nullptr;
}


int Icon_Parser::get_icon_name_id(std::string name){
	unsigned long int i;
	for(i = 0; i < this->icons_names.size(); i++){
		if (this->icons_names[i]->get_icon_id(name) != 0){
			return this->icons_names[i]->get_icon_id(name);
		}
	}

	return 0;
}



Icon_Names* Icon_Parser::get_icon_names(int id){
	unsigned long int i;

	for (i = 0; i < this->icons_names.size(); i++){
		if (this->icons_names[i]->check_id(id))
			return this->icons_names[i];
	}
	return nullptr;
}



void Icon_Parser::append_icon_names_to_vector(int icon_id, std::vector<std::string> *dest){
	Icon_Names* icon = this->get_icon_names(icon_id);
	if (icon != nullptr)
		icon->append_icon_names_to_vector(icon_id, dest);
}



void Icon_Parser::update(){
	std::fstream f("products_icons/product_names.txt");
	if (!(f.is_open())){
		std::cout << "Can't open product_names.txt!" << std::endl;
	}

	std::string buffer;
	while (std::getline(f, buffer)){
		if (buffer == "<filename>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at filename reading" << std::endl;
				break;
			}
			else{
				this->icons_names.push_back(new Icon_Names(buffer));
				if (!(this->icons_names.back()->check_file(buffer))){
					std::cout << "File doesn't exist!" << std::endl;
					break;
				}
			}

		}
		else if (buffer == "<textlines>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at textlines reading" << std::endl;
				break;
			}
			while (buffer != "</textlines>"){
				this->icons_names.back()->add_name(buffer);
				std::getline(f, buffer);
			}

		}
		else if (buffer == "<enum_number>"){
			if (!(std::getline(f, buffer))){
				std::cout << "Error at enumeration number reading" << std::endl;
				break;
			}
			else{
				this->icons_names.back()->set_icon_ID(stoi(buffer));
			}
		}
	}

	f.close();
}


void Icon_Parser::print_into_console(){
	unsigned long int i;
	for(i = 0; i < this->icons_names.size(); i++){
		this->icons_names[i]->print();
	}
}


Icon_Parser::~Icon_Parser() {
	// TODO Auto-generated destructor stub
}

