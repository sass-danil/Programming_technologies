/*
 * Product.cpp
 *
 *  Created on: Apr 11, 2024
 *      Author: danil
 */

#include "Product.hpp"
#include <iostream>
#include <map>
#include "IconParser.hpp"
#include "ProductsList.hpp"


#define RED_DATE 3
#define ORANGE_DATE 5


extern std::map<char, std::string> measures_map;
extern Icon_Parser* icons_parser;
extern Products_List* products;
extern GtkWidget* delete_product_message;


extern std::string name_to_lower_case(std::string name);


extern Product* selected_product;
extern GtkWidget* new_product_form;
extern GtkWidget* products_add_field_icon;
extern GtkWidget *units_button;
extern GtkEntryBuffer* product_name_buffer;
extern GtkEntryBuffer* product_count_buffer;
extern GtkWidget* cal_lifetime;
extern int current_icon_id;
extern GtkWidget* add_product_button;
static void product_combo_changed (GtkApplication *application, gpointer user_data){
	Product* prod = (Product*)user_data;
	selected_product = prod;

	if (strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(prod->get_combo())), "Удалить") == 0){
		gtk_widget_show_all(delete_product_message);
	}
	else if (strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(prod->get_combo())), "Редактировать") == 0){
		gtk_window_set_title(GTK_WINDOW(new_product_form), "Редактирование продукта");
		std::cout << "Current product's icon ID = " << prod->get_icon_id() << std::endl;
		if (icons_parser->get_icon(prod->get_icon_id()) == nullptr){
			gtk_button_set_image(GTK_BUTTON(products_add_field_icon), icons_parser->get_icon(0));
		}
		else{
			gtk_button_set_image(GTK_BUTTON(products_add_field_icon), icons_parser->get_icon(prod->get_icon_id()));
		}
		current_icon_id = prod->get_icon_id();
//		gtk_button_set_image(GTK_BUTTON(products_add_field_icon), gtk_image_new_from_pixbuf(gtk_image_get_pixbuf(GTK_IMAGE(icons_parser->get_icon(prod->get_icon_id())))));
		gtk_combo_box_set_active(GTK_COMBO_BOX(units_button), prod->get_unit());
		gtk_entry_buffer_set_text(product_name_buffer, prod->get_name().c_str(), -1);
		gtk_entry_buffer_set_text(product_count_buffer, std::to_string(prod->get_count()).c_str(), -1);
		tm death_date = prod->get_death_date();
		gtk_calendar_select_month(GTK_CALENDAR(cal_lifetime), death_date.tm_mon - 1, death_date.tm_year + 1900);
		gtk_calendar_select_day(GTK_CALENDAR(cal_lifetime), death_date.tm_mday);
		gtk_button_set_label(GTK_BUTTON(add_product_button), "Сохранить изменения");
		gtk_widget_show_all (new_product_form);
	}

	gtk_combo_box_set_active(GTK_COMBO_BOX(prod->get_combo()), 0);
}


Product::Product() {
	this->box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
	this->icon = NULL;
	this->image = nullptr;
	this->product_label = gtk_label_new("");
	this->add_date_label = gtk_label_new("");
	this->death_date_label = gtk_label_new("");
	this->count_label = gtk_label_new("");
	this->unit = 0;
	this->product_id = -1;
	this->count = 0;
	this->icon_id = 0;
	this->combo = nullptr;
}


Product::Product(std::string product_name) : Product(){
	gtk_label_set_text(GTK_LABEL(this->product_label), product_name.c_str());
	this->product_names.push_back(name_to_lower_case(product_name));
	icons_parser->append_icon_names_to_vector(icons_parser->get_icon_name_id(this->product_names[0]), &(this->product_names));
}



void Product::set_icon_id(int id){
	this->icon_id = id;
}



void Product::set_count(std::string count){
	try{
		this->count = stof(count);
	}
	catch(std::invalid_argument){
		this->count = 0;
	}
}


void Product::set_add_date(std::string date){
	sscanf(date.c_str(), "%d.%d.%d", &this->add_date.tm_mday, &this->add_date.tm_mon, &this->add_date.tm_year);
	this->add_date.tm_year -= 1900;
}


void Product::set_death_date(std::string date){
	sscanf(date.c_str(), "%d.%d.%d", &this->death_date.tm_mday, &this->death_date.tm_mon, &this->death_date.tm_year);
	this->death_date.tm_year -= 1900;
}


void Product::set_label_text(const char* text){
	gtk_label_set_label(GTK_LABEL(this->product_label), text);
	this->product_names.push_back(std::string(text));
}



void Product::set_name(const char* text){
	this->product_names.push_back(std::string(text));
	std::string temp_name = this->product_names.back();
	this->product_names.back() = this->product_names.front();
	this->product_names.front() = temp_name;
}



bool Product::check_name(std::string name){
	unsigned long int i;
	for (i = 0; i < this->product_names.size(); i++){
		if (name == this->product_names[i]){
			return true;
		}
	}

	return false;
}



void Product::update_box(){
	std::setlocale(LC_NUMERIC, "POSIX");
	if (this->icon != NULL){
		if (this->image == nullptr){
			this->image = gtk_image_new_from_pixbuf(gtk_image_get_pixbuf(GTK_IMAGE(this->icon)));
			gtk_box_pack_start(GTK_BOX(this->box), this->image, false, false, 3);
		}
		else{
			gtk_image_set_from_pixbuf(GTK_IMAGE(this->image), gtk_image_get_pixbuf(GTK_IMAGE(this->icon)));
			if (gtk_widget_get_parent(this->image) != this->box){
				gtk_box_pack_start(GTK_BOX(this->box), this->image, false, false, 3);
			}
		}
	}
	if (gtk_widget_get_parent(this->product_label) != this->box)
		gtk_box_pack_start(GTK_BOX(this->box), this->product_label, false, false, 3);
	gtk_widget_set_name(this->box, "product_box");

	char s[15];
//	sprintf(s, "%d.%d.%d", this->add_date.tm_mday, this->add_date.tm_mon, this->add_date.tm_year + 1900);
//	gtk_label_set_text(GTK_LABEL(this->add_date_label), (std::string("Was added ") + s).c_str());
//	if (gtk_widget_get_parent(this->add_date_label) != this->box)
//		gtk_box_pack_start(GTK_BOX(this->box), this->add_date_label, false, false, 3);

	sprintf(s, "%d.%d.%d", this->death_date.tm_mday, this->death_date.tm_mon, this->death_date.tm_year + 1900);
	gtk_label_set_text(GTK_LABEL(this->death_date_label), (std::string("Испортится  ") + s).c_str());
	gtk_widget_set_halign(this->death_date_label, GTK_ALIGN_CENTER);
	if (gtk_widget_get_parent(this->death_date_label) != this->box)
		gtk_box_pack_start(GTK_BOX(this->box), this->death_date_label, true, true, 3);

	if (this->count > 0){
		sprintf(s, "%.3f", this->count);
		gtk_label_set_text(GTK_LABEL(this->count_label), (std::string(s) + " " + measures_map[this->unit]).c_str());
	}
	else{
		gtk_label_set_text(GTK_LABEL(this->count_label), "");
	}
	if (gtk_widget_get_parent(this->count_label) != this->box)
		gtk_box_pack_start(GTK_BOX(this->box), this->count_label, false, false, 3);

	if (this->combo == nullptr){
		this->combo = gtk_combo_box_text_new();
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(this->combo), "Дополнительно");
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(this->combo), "Редактировать");
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(this->combo), "Удалить");
		gtk_combo_box_set_active(GTK_COMBO_BOX(this->combo), 0);
		gtk_box_pack_end(GTK_BOX(this->box), this->combo, FALSE, FALSE, 3);
		g_signal_connect (this->combo, "changed", G_CALLBACK (product_combo_changed), this);
		gtk_widget_set_name(this->combo, "product_combo");
	}

	gtk_widget_set_name(this->count_label, "normal_product");
	gtk_widget_set_name(this->death_date_label, "normal_product");
	gtk_widget_set_name(this->add_date_label, "normal_product");
	gtk_widget_set_name(this->product_label, "normal_product");
	if (this->alarm_icon != nullptr){
		gtk_widget_destroy(this->alarm_icon);
	}
	time_t today_time = time(NULL);
	tm today_date = *localtime(&today_time);
	today_date.tm_mon += 1;
	if (today_date.tm_year > this->death_date.tm_year){
		this->alarm_icon = gtk_image_new_from_file("./death.png");
		gtk_box_pack_end(GTK_BOX(this->box), this->alarm_icon, FALSE, FALSE, 3);
		gtk_widget_set_name(this->count_label, "dead_product");
		gtk_widget_set_name(this->death_date_label, "dead_product");
		gtk_widget_set_name(this->add_date_label, "dead_product");
		gtk_widget_set_name(this->product_label, "dead_product");
	}
	else if (today_date.tm_mon > this->death_date.tm_mon){
		this->alarm_icon = gtk_image_new_from_file("./death.png");
		gtk_box_pack_end(GTK_BOX(this->box), this->alarm_icon, FALSE, FALSE, 3);
		gtk_widget_set_name(this->count_label, "dead_product");
		gtk_widget_set_name(this->death_date_label, "dead_product");
		gtk_widget_set_name(this->add_date_label, "dead_product");
		gtk_widget_set_name(this->product_label, "dead_product");
	}
	else if (today_date.tm_mday > this->death_date.tm_mday){
		this->alarm_icon = gtk_image_new_from_file("./death.png");
		gtk_box_pack_end(GTK_BOX(this->box), this->alarm_icon, FALSE, FALSE, 3);
		gtk_widget_set_name(this->count_label, "dead_product");
		gtk_widget_set_name(this->death_date_label, "dead_product");
		gtk_widget_set_name(this->add_date_label, "dead_product");
		gtk_widget_set_name(this->product_label, "dead_product");
	}
	else if ((today_date.tm_year == this->death_date.tm_year) &&
			(today_date.tm_mon == this->death_date.tm_mon) &&
			(this->death_date.tm_mday - today_date.tm_mday <= RED_DATE)){
		this->alarm_icon = gtk_image_new_from_file("./alarm.png");
		gtk_box_pack_end(GTK_BOX(this->box), this->alarm_icon, FALSE, FALSE, 3);
		gtk_widget_set_name(this->count_label, "red_product");
		gtk_widget_set_name(this->death_date_label, "red_product");
		gtk_widget_set_name(this->add_date_label, "red_product");
		gtk_widget_set_name(this->product_label, "red_product");
	}
	else if ((today_date.tm_year == this->death_date.tm_year) &&
			(today_date.tm_mon == this->death_date.tm_mon) &&
			(this->death_date.tm_mday - today_date.tm_mday <= ORANGE_DATE)){
		this->alarm_icon = gtk_image_new_from_file("./warning.png");
		gtk_box_pack_end(GTK_BOX(this->box), this->alarm_icon, FALSE, FALSE, 3);
		gtk_widget_set_name(this->count_label, "orange_product");
		gtk_widget_set_name(this->death_date_label, "orange_product");
		gtk_widget_set_name(this->add_date_label, "orange_product");
		gtk_widget_set_name(this->product_label, "orange_product");
	}
	std::cout << "death_date = " << this->death_date.tm_mday << "." << this->death_date.tm_mon << "." << this->death_date.tm_year << std::endl;
	std::cout << "current_date = " << today_date.tm_mday << "." << today_date.tm_mon << "." << today_date.tm_year << std::endl;
}



void Product::print_into_console(){
	std::cout << "product_names :" << gtk_label_get_text(GTK_LABEL(this->product_label)) << std::endl;
	unsigned int long i;
	for (i = 0; i < this->product_names.size(); i++){
		std::cout << "\t" << this->product_names[i] << std::endl;
	}
	std::cout << "product_ID " << this->product_id << std::endl;
	std::cout << "unit_ID " << (int)this->unit << ": " << measures_map[this->unit] << std::endl;
	std::cout << "Count " << this->count << std::endl;
	std::cout << "add_date " << this->add_date.tm_mday << "." << this->add_date.tm_mon << "." << this->add_date.tm_year + 1900 << std::endl;
	std::cout << "death_date " << this->death_date.tm_mday << "." << this->death_date.tm_mon << "." << this->death_date.tm_year + 1900 << std::endl;
}



Product::~Product() {
	// TODO Auto-generated destructor stub
}

