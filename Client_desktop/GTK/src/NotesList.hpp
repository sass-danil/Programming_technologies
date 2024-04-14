/*
 * NotesList.hpp
 *
 *  Created on: Apr 14, 2024
 *      Author: danil
 */

#ifndef NOTESLIST_HPP_
#define NOTESLIST_HPP_

#include <vector>

#include "Note.hpp"

class Notes_List {
	public:
		Notes_List();


		void set_box(GtkWidget* box){ this->notes_box = box;}


		void parse_notes();

		void update_box();


		virtual ~Notes_List();

	protected:
		std::vector<Note*> notes;
		GtkWidget *notes_box;
};

#endif /* NOTESLIST_HPP_ */
