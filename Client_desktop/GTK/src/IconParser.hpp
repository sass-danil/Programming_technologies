/*
 * IconParser.hpp
 *
 *  Created on: Mar 23, 2024
 *      Author: danil
 */

#ifndef ICONPARSER_HPP_
#define ICONPARSER_HPP_

#include "IconNames.hpp"

class Icon_Parser {
	public:
		Icon_Parser();


		GtkWidget* get_icon(std::string name);

		GtkWidget* get_icon(int index);

		int get_icon_name_id(std::string name);

		Icon_Names* get_icon_names(int id);

		int get_icons_count() {return this->icons_names.size(); }


		void append_icon_names_to_vector(int icon_id, std::vector<std::string> *dest);

		void update();

		void print_into_console();


		virtual ~Icon_Parser();

	protected:
		std::vector<Icon_Names*> icons_names;
};

#endif /* ICONPARSER_HPP_ */
