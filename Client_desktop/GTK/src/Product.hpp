/*
 * Product.hpp
 *
 *  Created on: Apr 11, 2024
 *      Author: danil
 */

#ifndef PRODUCT_HPP_
#define PRODUCT_HPP_

#include <vector>
#include <string>
#include <gtk/gtk.h>
#include <ctime>

class Product {
	public:
		Product();
		Product(std::string product_name);


		GtkWidget* get_box(){ return this->box; }

		int get_icon_id(){ return this->icon_id;}

		std::string get_name(){ return this->product_names[0];}

		float get_count(){ return this->count; }

		char get_unit(){ return this->unit; }


		void set_id(int id){ this->product_id = id;}

		void set_icon(GtkWidget* icon){ this->icon = icon;}

		void set_icon_id(int id);

		void set_unit(char unit_id){ this->unit = unit_id;}

		void set_count(std::string count);

		void set_add_date(std::string date);

		void set_death_date(std::string date);



		bool check_name(std::string name);

		void update_box();

		void print_into_console();



		virtual ~Product();

	private:
		GtkWidget* box;
		GtkWidget* icon;
		GtkWidget* product_label;
		GtkWidget* add_date_label;
		GtkWidget* death_date_label;
		GtkWidget* count_label;
		std::vector<std::string> product_names;
		int icon_id;
		int product_id;
		char unit;
		float count;
		tm add_date;
		tm death_date;
};

#endif /* PRODUCT_HPP_ */
