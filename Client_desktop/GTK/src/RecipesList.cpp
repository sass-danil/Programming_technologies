/*
 * RecipesList.cpp
 *
 *  Created on: Apr 13, 2024
 *      Author: danil
 */

#include "RecipesList.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

Recipes_List::Recipes_List() {
	this->recipes_box = nullptr;
}



void Recipes_List::parse_recipes(){
	std::string path = "./recipes";
	Recipe *new_recipe;
	for (const auto & entry : std::filesystem::directory_iterator(path)){
		new_recipe = new Recipe(entry.path());
		this->recipes.push_back(new_recipe);

		std::fstream f(std::string(entry.path()) + "/recipe.txt");
		std::cout << "Parsing recipe from file " << std::string(entry.path()) + "/recipe.txt" << std::endl;
		if (!(f.is_open())){
			std::cout << "Can't open file " << std::string(entry.path()) + "/recipe.txt" << std::endl;
		}

		std::string buffer;
		while (std::getline(f, buffer)){
			if (buffer == "<name>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at recipe name reading" << std::endl;
					break;
				}
				else{
					new_recipe->set_name(buffer);
				}
			}
			else if (buffer == "<dificulcity>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at dificulcity reading" << std::endl;
					break;
				}
				new_recipe->set_dificulcity(stoi(buffer));
			}
			else if (buffer == "<icon>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at recipe icon reading" << std::endl;
					break;
				}
				new_recipe->set_icon(std::string(entry.path()) + "/" + buffer);
			}
			else if (buffer == "<intro>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at intro reading" << std::endl;
					break;
				}
				std::string intro_buffer = buffer;
				while (std::getline(f, buffer)){
					if (buffer == "</intro>"){
						new_recipe->add_intro(intro_buffer);
						break;
					}
					else{
						intro_buffer += "\n" + buffer;
					}
				}
			}
			else if (buffer == "<note>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at note reading" << std::endl;
					break;
				}
				std::string intro_buffer = buffer;
				while (std::getline(f, buffer)){
					if (buffer == "</note>"){
						new_recipe->add_note(intro_buffer);
						break;
					}
					else{
						intro_buffer += "\n" + buffer;
					}
				}
			}
			else if (buffer == "<image>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at recipe image reading" << std::endl;
					break;
				}
				new_recipe->add_image(std::string(entry.path()) + "/" + buffer);
			}
			else if (buffer == "<products>"){
				while (std::getline(f, buffer)){
					if (buffer == "</products>")
						break;
					else if (buffer == "<product>"){
						std::string product_name;
						std::string product_text_name;
						while (std::getline(f, buffer)){
							if (buffer == "</product>"){
								new_recipe->add_ingredient(product_name, product_text_name);
								break;
							}
							else if (buffer == "<name>"){
								std::getline(f, product_name);
							}
							else if (buffer == "<text_name>"){
								std::getline(f, product_text_name);
							}
						}
					}
					else if (buffer == "<note>"){
						if (!(std::getline(f, buffer))){
							std::cout << "Error at note reading" << std::endl;
							break;
						}
						std::string intro_buffer = buffer;
						while (std::getline(f, buffer)){
							if (buffer == "</note>"){
								new_recipe->add_note(intro_buffer);
								break;
							}
							else{
								intro_buffer += "\n" + buffer;
							}
						}
					}
				}
			}
			else if (buffer == "<step>"){
				if (!(std::getline(f, buffer))){
					std::cout << "Error at step reading" << std::endl;
					break;
				}
				std::string step_buffer = buffer;
				while (std::getline(f, buffer)){
					if (buffer == "</step>"){
						new_recipe->add_step(step_buffer);
						break;
					}
					else{
						step_buffer += "\n" + buffer;
					}
				}
			}
			else if (buffer == "<outro>"){
				std::string outro_buffer;
				while (std::getline(f, buffer)){
					outro_buffer += "\n" + buffer;
				}
				new_recipe->add_outro(outro_buffer);
			}
		}

		f.close();
		this->recipes.back()->create_gui();
	}
}

void Recipes_List::update_box(){
	GList* childrens = gtk_container_get_children(GTK_CONTAINER(this->recipes_box));
//	while(childrens->data != NULL){
//		gtk_container_remove(GTK_CONTAINER(this->recipes_box), GTK_WIDGET(childrens->data));
//		childrens = childrens->next;
//	}
	unsigned long int i;
	for (i = 0; i < this->recipes.size(); i++){
		gtk_box_pack_start(GTK_BOX(this->recipes_box), this->recipes[i]->get_paned(), false, false, 3);
	}
}



Recipes_List::~Recipes_List() {
	// TODO Auto-generated destructor stub
}

