/*
 * Recipe.hpp
 *
 *  Created on: Apr 13, 2024
 *      Author: danil
 */

#ifndef RECIPE_HPP_
#define RECIPE_HPP_

#include "ProductsList.hpp"

class Recipe {
	public:
		Recipe(std::string dirpath);


		GtkWidget* get_paned(){ return this->paned; }


		void set_name(std::string name){ this->name = name;}

		void set_dificulcity(char dif){ this->dificulcity = dif; }

		void set_icon(std::string filename);



		void add_intro(std::string buffer);

		void add_image(std::string filename);

		void add_ingredient(std::string buffer);

		void add_ingredient(std::string name, std::string text_name);

		void add_note(std::string buffer);

		void add_step(std::string buffer);

		void add_outro(std::string buffer);

		void create_gui();



		virtual ~Recipe();

	private:
		GtkWidget *paned;
		std::string name;
		char dificulcity;
		GtkWidget *icon;
		GtkWidget *body_box;
		char current_step;
		char current_ingredient;
		Products_List *products;
};

#endif /* RECIPE_HPP_ */
