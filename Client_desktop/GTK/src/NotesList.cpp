/*
 * NotesList.cpp
 *
 *  Created on: Apr 14, 2024
 *      Author: danil
 */


#include <filesystem>
#include <fstream>
#include <iostream>
#include "NotesList.hpp"

Notes_List::Notes_List() {
	this->notes_box = nullptr;
}



void Notes_List::parse_notes(){
	std::string path = "./user_data/notes";
	Note *new_note;
	for (const auto & entry : std::filesystem::directory_iterator(path)){
		new_note = new Note();
		this->notes.push_back(new_note);

		std::fstream f(std::string(entry.path()));
		std::cout << "Parsing note from file " << std::string(entry.path()) << std::endl;
		if (!(f.is_open())){
			std::cout << "Can't open file " << std::string(entry.path()) << std::endl;
		}

		std::string buffer;
		while (std::getline(f, buffer)){
			if (buffer == "<name>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at note name reading" << std::endl;
					break;
				}
				else{
					new_note->set_name(buffer);
				}
			}
			else if (buffer == "<favourite>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at favourite reading" << std::endl;
					break;
				}
				new_note->set_favourite(buffer[0]);
			}
			else if (buffer == "<created>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at note creation date reading" << std::endl;
					break;
				}
				new_note->set_add_date(buffer);
			}
			else if (buffer == "<note_body>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at note body reading" << std::endl;
					break;
				}
				std::string body_buffer = buffer;
				while (std::getline(f, buffer)){
					if (buffer == "</note_body>"){
						new_note->set_body(body_buffer);
						break;
					}
					else{
						body_buffer += "\n" + buffer;
					}
				}
			}
		}

		f.close();
		this->notes.back()->create_gui();
	}
}

void Notes_List::update_box(){
	GList* childrens = gtk_container_get_children(GTK_CONTAINER(this->notes_box));
//	while(childrens->data != NULL){
//		gtk_container_remove(GTK_CONTAINER(this->notes_box), GTK_WIDGET(childrens->data));
//		childrens = childrens->next;
//	}
	unsigned long int i;
	for (i = 0; i < this->notes.size(); i++){
		gtk_box_pack_start(GTK_BOX(this->notes_box), this->notes[i]->get_paned(), false, false, 3);
	}
}



Notes_List::~Notes_List() {
	// TODO Auto-generated destructor stub
}

