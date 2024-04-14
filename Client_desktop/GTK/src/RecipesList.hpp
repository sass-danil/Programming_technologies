/*
 * RecipesList.hpp
 *
 *  Created on: Apr 13, 2024
 *      Author: danil
 */

#ifndef RECIPESLIST_HPP_
#define RECIPESLIST_HPP_

#include "Recipe.hpp"

class Recipes_List {
	public:
		Recipes_List();



		void set_box(GtkWidget* box){ this->recipes_box = box;}



		void parse_recipes();

		void update_box();


		virtual ~Recipes_List();

	private:
		std::vector<Recipe*> recipes;
		GtkWidget *recipes_box;
};

#endif /* RECIPESLIST_HPP_ */
