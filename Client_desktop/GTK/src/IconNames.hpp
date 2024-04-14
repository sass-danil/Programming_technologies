/*
 * IconNames.hpp
 *
 *  Created on: Mar 23, 2024
 *      Author: danil
 */

#ifndef ICONNAMES_HPP_
#define ICONNAMES_HPP_

#include <vector>
#include <string>
#include <gtk/gtk.h>

class Icon_Names {
	public:
		Icon_Names(std::string filename);


		GtkWidget* get_icon(){ return this->icon; }

		int get_icon_id(std::string name);


		void set_icon_ID(int id){ this->icon_id = id; }


		bool check_icon(std::string name);

		bool check_id(int id) {return (id == this->icon_id); }

		bool check_file(std::string name);


		void append_icon_names_to_vector(int icon_id, std::vector<std::string> *dest);

		void add_name(std::string new_name);


		void print();


		virtual ~Icon_Names();

	private:
		GtkWidget* icon;
		std::vector<std::string> names;
		std::string filename;
		int icon_id;
};

#endif /* ICONNAMES_HPP_ */
