/*
 * IconNames.cpp
 *
 *  Created on: Mar 23, 2024
 *      Author: danil
 */

#include "IconNames.hpp"
#include <iostream>
#include <fstream>

Icon_Names::Icon_Names(std::string filename) {
	this->filename = filename;
	std::fstream f(std::string("./products_icons/") + filename);
	if (!(f.is_open())){
		std::cout << "Can't open!" << std::endl;
	}
	f.close();
	this->icon = gtk_image_new_from_file((std::string("./products_icons/") + filename).c_str());
	gtk_widget_set_vexpand(this->icon, FALSE);
	gtk_widget_set_hexpand(this->icon, FALSE);
	this->icon_id = -1;
}


extern std::string name_to_lower_case(std::string name);
int Icon_Names::get_icon_id(std::string name){
	unsigned long int i;
	name = name_to_lower_case(name);
	for (i = 0; i < this->names.size(); i++){
		if (this->names[i] == name)
			return this->icon_id;
		else if (this->names[i].find(name) == 0)
			return this->icon_id;
	}

	return 0;
}


bool Icon_Names::check_icon(std::string name){
	long unsigned i;
	name = name_to_lower_case(name);
	for (i = 0; i < this->names.size(); i++){
		if (this->names[i] == name)
			return true;
		else if (this->names[i].find(name) == 0)
			return true;
	}
	return false;
}


bool Icon_Names::check_file(std::string name){
	std::fstream f(std::string("./products_icons/") + name);
	if (f.is_open()){
		f.close();
		return true;
	}
	return false;
}



void Icon_Names::append_icon_names_to_vector(int icon_id, std::vector<std::string> *dest){
	unsigned long int i;

	for (i = 0; i < this->names.size(); i++){
		dest->push_back(this->names[i]);
	}
}



void Icon_Names::add_name(std::string new_name){
	this->names.push_back(new_name);
}



void Icon_Names::print(){
	std::cout << "Filename " << this->filename << std::endl;
	std::cout << "ID " << this->icon_id << std::endl;
	unsigned long int i;
	for (i = 0; i < this->names.size(); i++){
		std::cout << "\t" << this->names[i] << std::endl;
	}
}



Icon_Names::~Icon_Names() {
	// TODO Auto-generated destructor stub
}

