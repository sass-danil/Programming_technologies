/*
 * Note.hpp
 *
 *  Created on: Apr 14, 2024
 *      Author: danil
 */

#ifndef NOTE_HPP_
#define NOTE_HPP_

#include <gtk/gtk.h>
#include <string>
#include <ctime>

class Note {
	public:
		Note();



		GtkWidget* get_paned(){ return this->paned; }



		void set_name(std::string name){ this->name = name; }

		void set_favourite(char f){ this->is_favourite = f;}

		void set_add_date(std::string buffer);

		void set_body(std::string buffer);



		void create_gui();



		virtual ~Note();

	private:
		GtkWidget *paned;
		std::string name;
		bool is_favourite;
		GtkWidget *body_box;
		tm add_date;
};

#endif /* NOTE_HPP_ */
