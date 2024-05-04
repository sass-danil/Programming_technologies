/*
 * Recipe.cpp
 *
 *  Created on: Apr 13, 2024
 *      Author: danil
 */

#include "Recipe.hpp"
#include "ProductParser.hpp"
#include <iostream>
#include <map>
#include <cmath>


extern Products_List* products;
extern std::map<char, std::string> measures_map;


static void fold_recipe (GtkApplication *application, gpointer user_data){
	GtkWidget *box = GTK_WIDGET(user_data);
	if (gtk_widget_get_visible(box)){
		gtk_widget_set_visible(box, false);
	}
	else{
		gtk_widget_set_visible(box, true);
	}
}


Recipe::Recipe(std::string dirpath) {
	std::cout << "parsing products from " << dirpath << std::endl;
	std::string t_str = dirpath + "/products.txt";
	Product_Parser* parser = new Product_Parser();
	std::cout << "products:"  << std::endl;
	this->products = new Products_List();
	parser->parse_products(this->products, t_str.c_str());
	this->products->print_into_console();
	this->body_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	this->dificulcity = 5;
	this->icon = nullptr;
	this->paned = nullptr;
	this->current_ingredient = 0;
	this->current_step = 0;
}



void Recipe::set_icon(std::string filename){
	this->icon = gtk_image_new_from_file(filename.c_str());
}



void Recipe::add_intro(std::string buffer){
	GtkWidget* label = gtk_label_new(buffer.c_str());
	gtk_label_set_line_wrap(GTK_LABEL(label), true);
	gtk_box_pack_start(GTK_BOX(this->body_box), label, false, false, 3);
}


void Recipe::add_image(std::string filename){
	GtkWidget* image = gtk_image_new_from_file(filename.c_str());
	gtk_box_pack_start(GTK_BOX(this->body_box), image, false, false, 3);
}



void Recipe::add_ingredient(std::string buffer){
	if (this->current_ingredient == 0){
		GtkWidget* label_0 = gtk_label_new("Необходимые продукты");
		gtk_label_set_line_wrap(GTK_LABEL(label_0), true);
		gtk_box_pack_start(GTK_BOX(this->body_box), label_0, false, false, 3);
	}
	this->current_ingredient++;
	GtkWidget* label = gtk_label_new((std::to_string(this->current_ingredient) + ". " + buffer).c_str());
	gtk_widget_set_halign(label, GTK_ALIGN_START);
	gtk_label_set_line_wrap(GTK_LABEL(label), true);
	gtk_box_pack_start(GTK_BOX(this->body_box), label, false, false, 3);
}


void Recipe::add_ingredient(std::string name, std::string text_name){
	if (this->current_ingredient == 0){
		GtkWidget* label_0 = gtk_label_new("Необходимые продукты");
		gtk_label_set_line_wrap(GTK_LABEL(label_0), true);
		gtk_box_pack_start(GTK_BOX(this->body_box), label_0, false, false, 3);
	}
	this->current_ingredient++;
	Product *new_product = products->get_element(name);
	if (new_product != nullptr){
		std::string str(std::to_string(this->current_ingredient) + ". " );
		str += text_name;
		if (new_product->get_count() > 0){
			str += " - ";
			char float_buffer[20];
			if (fmod(new_product->get_count(), 1.0f) == 0){
				sprintf(float_buffer, "%d ", (int)new_product->get_count());
			}
			else{
				sprintf(float_buffer, "%.3f ", new_product->get_count());
			}
			str += float_buffer;
			str += measures_map[new_product->get_unit()];
		}
		GtkWidget* label = gtk_label_new(str.c_str());
		gtk_widget_set_halign(label, GTK_ALIGN_START);
		gtk_label_set_line_wrap(GTK_LABEL(label), true);
		gtk_box_pack_start(GTK_BOX(this->body_box), label, false, false, 3);
		return;
	}
	std::cout << "Cant't find product " << name << std::endl;
	GtkWidget* label = gtk_label_new((std::to_string(this->current_ingredient) + ". " + name).c_str());
	gtk_widget_set_halign(label, GTK_ALIGN_START);
	gtk_label_set_line_wrap(GTK_LABEL(label), true);
	gtk_box_pack_start(GTK_BOX(this->body_box), label, false, false, 3);
}


void Recipe::add_note(std::string buffer){
	GtkWidget* label = gtk_label_new(buffer.c_str());
	gtk_label_set_line_wrap(GTK_LABEL(label), true);
	gtk_box_pack_start(GTK_BOX(this->body_box), label, false, false, 3);
}



void Recipe::add_step(std::string buffer){
	if (this->current_step == 0){
		GtkWidget* label_0 = gtk_label_new("Шаги приготовления");
		gtk_label_set_line_wrap(GTK_LABEL(label_0), true);
		gtk_box_pack_start(GTK_BOX(this->body_box), label_0, false, false, 3);
	}
	this->current_step++;
	GtkWidget* label = gtk_label_new((std::to_string(this->current_step) + ". " + buffer).c_str());
	gtk_label_set_line_wrap(GTK_LABEL(label), true);
	gtk_widget_set_halign(label, GTK_ALIGN_START);
	gtk_box_pack_start(GTK_BOX(this->body_box), label, false, false, 3);
}



void Recipe::add_outro(std::string buffer){
	GtkWidget* label = gtk_label_new(buffer.c_str());
	gtk_label_set_line_wrap(GTK_LABEL(label), true);
	gtk_box_pack_start(GTK_BOX(this->body_box), label, false, false, 3);
}



void Recipe::create_gui(){
	this->paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
	GtkWidget* header_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
	GtkWidget *label = gtk_label_new(this->name.c_str());
	gtk_box_pack_start(GTK_BOX(header_box), this->icon, false, false, 3);
	gtk_box_pack_start(GTK_BOX(header_box), label, false, false, 3);
	GtkWidget *button = gtk_button_new_with_label("Fold");
	g_signal_connect (button, "clicked", G_CALLBACK (fold_recipe), this->body_box);
	gtk_box_pack_end(GTK_BOX(header_box), button, false, false, 3);
	gtk_paned_pack1(GTK_PANED(this->paned), header_box, false, false);
	gtk_paned_pack2(GTK_PANED(this->paned), this->body_box, false, false);
}



Recipe::~Recipe() {
	// TODO Auto-generated destructor stub
}

