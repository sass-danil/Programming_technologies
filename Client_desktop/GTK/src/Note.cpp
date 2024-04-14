/*
 * Note.cpp
 *
 *  Created on: Apr 14, 2024
 *      Author: danil
 */

#include "Note.hpp"



static void fold_note (GtkApplication *application, gpointer user_data){
	GtkWidget *box = GTK_WIDGET(user_data);
	if (gtk_widget_get_visible(box)){
		gtk_widget_set_visible(box, false);
	}
	else{
		gtk_widget_set_visible(box, true);
	}
}



Note::Note() {
	this->body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	this->paned = nullptr;
	this->is_favourite = false;
}



void Note::set_add_date(std::string buffer){
	sscanf(buffer.c_str(), "%d.%d.%d", &this->add_date.tm_mday, &this->add_date.tm_mon, &this->add_date.tm_year);
	this->add_date.tm_year -= 1900;
}

void Note::set_body(std::string buffer){
	GtkWidget* label = gtk_label_new(buffer.c_str());
	gtk_label_set_line_wrap(GTK_LABEL(label), true);
	gtk_widget_set_halign(label, GTK_ALIGN_START);
	gtk_box_pack_start(GTK_BOX(this->body_box), label, false, false, 3);
}



void Note::create_gui(){
	this->paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
	GtkWidget* header_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
	GtkWidget *label = gtk_label_new(this->name.c_str());
	gtk_box_pack_start(GTK_BOX(header_box), label, false, false, 3);
	GtkWidget *button = gtk_button_new_with_label("Fold");
	g_signal_connect (button, "clicked", G_CALLBACK (fold_note), this->body_box);
	gtk_box_pack_end(GTK_BOX(header_box), button, false, false, 3);
	char s[15];
	sprintf(s, "%d.%d.%d", this->add_date.tm_mday, this->add_date.tm_mon, this->add_date.tm_year + 1900);
	label = gtk_label_new((std::string("Was added ") + s).c_str());
	gtk_box_pack_end(GTK_BOX(header_box), label, false, false, 3);
	gtk_paned_pack1(GTK_PANED(this->paned), header_box, false, false);
	gtk_paned_pack2(GTK_PANED(this->paned), this->body_box, false, false);
}


Note::~Note() {
	// TODO Auto-generated destructor stub
}

