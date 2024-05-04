/*
 * Products_tab_utils.cpp
 *
 *  Created on: May 2, 2024
 *      Author: danil
 */

#include <gtk/gtk.h>
#include <iostream>
#include "ProductsList.hpp"
#include "Products_tab_utils.hpp"


extern Product *selected_product;
extern GtkWidget *new_product_form;
extern GtkWidget *add_product_button;

char arrange = ORDER_BY_ASCENDING;
char sort = SORT_BY_NAME;


void add_new_product (GtkApplication *application, gpointer user_data){
	gtk_window_set_title(GTK_WINDOW(new_product_form), "Добавление продукта");
	gtk_button_set_label(GTK_BUTTON(add_product_button), "Добавить продукт");
	selected_product = nullptr;
	gtk_widget_show_all (new_product_form);
}


extern Products_List* products;
void sort_by_name (){
	unsigned long int i, j, k;
	Product* temp_product;
	std::string t_str_1 = "ab", t_str_2 = "ab";
	if (arrange == ORDER_BY_ASCENDING){
		for(i = 0; i < products->products.size(); i++){
			for (j = i + 1; j < products->products.size(); j++){
				for(k = 0; (k < products->products[i]->get_name().size()) && (k < products->products[j]->get_name().size()); k += 2){
					t_str_1[0] = products->products[i]->get_name()[k];
					t_str_1[1] = products->products[i]->get_name()[k + 1];
					t_str_2[0] = products->products[j]->get_name()[k];
					t_str_2[1] = products->products[j]->get_name()[k + 1];
					std::cout << letters_map[t_str_1] << ", " << letters_map[t_str_2] << std::endl;
					if (letters_map[t_str_1] > letters_map[t_str_2]){
						temp_product = products->products[i];
						products->products[i] = products->products[j];
						products->products[j] = temp_product;
						break;
					}
					else if (letters_map[t_str_1] < letters_map[t_str_2]){
						break;
					}
				}
			}
		}
	}
	else{
		for(i = 0; i < products->products.size(); i++){
			for (j = i + 1; j < products->products.size(); j++){
				for(k = 0; (k < products->products[i]->get_name().size()) && (k < products->products[j]->get_name().size()); k += 2){
					t_str_1[0] = products->products[i]->get_name()[k];
					t_str_1[1] = products->products[i]->get_name()[k + 1];
					t_str_2[0] = products->products[j]->get_name()[k];
					t_str_2[1] = products->products[j]->get_name()[k + 1];
					if (letters_map[t_str_1] < letters_map[t_str_2]){
						temp_product = products->products[i];
						products->products[i] = products->products[j];
						products->products[j] = temp_product;
						break;
					}
					if (letters_map[t_str_1] > letters_map[t_str_2]){
						break;
					}
				}
			}
		}
	}
	products->update_gui();
}


void sort_by_date (){
	unsigned long int i, j;
	Product* temp_product;
	tm death_date_1, death_date_2;

	if (arrange == ORDER_BY_DESCENDING){
		for(i = 0; i < products->products.size(); i++){
			for (j = i + 1; j < products->products.size(); j++){
				death_date_1 = products->products[i]->get_death_date();
				death_date_2 = products->products[j]->get_death_date();
//				std::cout << "year = " << death_date_1.tm_year << ", " << death_date_2.tm_year << std::endl;
//				std::cout << "mounth_day = " << death_date_1.tm_yday << ", " << death_date_2.tm_yday << std::endl;
				if (death_date_2.tm_year > death_date_1.tm_year){
					temp_product = products->products[i];
					products->products[i] = products->products[j];
					products->products[j] = temp_product;
					continue;
				}
				else if (death_date_2.tm_year < death_date_1.tm_year)
					continue;
				if (death_date_2.tm_mon > death_date_1.tm_mon){
					temp_product = products->products[i];
					products->products[i] = products->products[j];
					products->products[j] = temp_product;
					continue;
				}
				else if (death_date_2.tm_mon < death_date_1.tm_mon)
					continue;
				if (death_date_2.tm_mday > death_date_1.tm_mday){
					temp_product = products->products[i];
					products->products[i] = products->products[j];
					products->products[j] = temp_product;
					continue;
				}
			}
		}
	}
	else{
		for(i = 0; i < products->products.size(); i++){
			for (j = i + 1; j < products->products.size(); j++){
				death_date_1 = products->products[i]->get_death_date();
				death_date_2 = products->products[j]->get_death_date();
				if (death_date_2.tm_year < death_date_1.tm_year){
					temp_product = products->products[i];
					products->products[i] = products->products[j];
					products->products[j] = temp_product;
					continue;
				}
				else if (death_date_2.tm_year > death_date_1.tm_year)
					continue;
				if (death_date_2.tm_mon < death_date_1.tm_mon){
					temp_product = products->products[i];
					products->products[i] = products->products[j];
					products->products[j] = temp_product;
					continue;
				}
				else if (death_date_2.tm_mon > death_date_1.tm_mon)
					continue;
				if (death_date_2.tm_mday < death_date_1.tm_mday){
					temp_product = products->products[i];
					products->products[i] = products->products[j];
					products->products[j] = temp_product;
					continue;
				}
			}
		}
	}
	products->update_gui();
}


extern GtkWidget *products_sort_button;
void change_products_sort (GtkApplication *application, gpointer user_data){
	if (sort == SORT_BY_DATE){
		gtk_button_set_label(GTK_BUTTON(products_sort_button), "Сортировка по имени");
		sort = SORT_BY_NAME;
	}
	else if (sort == SORT_BY_NAME){
		gtk_button_set_label(GTK_BUTTON(products_sort_button), "Сортировка по сроку годности");
		sort = SORT_BY_DATE;
	}
	update_products_sort();
}


extern GtkWidget *products_arrange_button;
extern GtkWidget* arrange_up_icon;
extern GtkWidget* arrange_down_icon;
void change_products_arrange (GtkApplication *application, gpointer user_data){
	if (arrange == ORDER_BY_ASCENDING){
		arrange = ORDER_BY_DESCENDING;
		g_object_ref(arrange_up_icon);
		gtk_button_set_image(GTK_BUTTON(products_arrange_button), arrange_down_icon);
	}
	else{
		arrange = ORDER_BY_ASCENDING;
		g_object_ref(arrange_down_icon);
		gtk_button_set_image(GTK_BUTTON(products_arrange_button), arrange_up_icon);
	}
	update_products_sort();
}


void update_products_sort(){
	if (sort == SORT_BY_DATE){
		sort_by_date();
	}
	else if (sort == SORT_BY_NAME){
		sort_by_name();
	}
}




extern GtkWidget* products_add_field_icon;
extern GtkWidget *units_button;
extern GtkEntryBuffer* product_name_buffer;
extern GtkEntryBuffer* product_count_buffer;
extern GtkWidget* products_list_box;
extern GtkWidget* cal_lifetime;
extern int current_icon_id;
void add_new_product_to_list (GtkApplication *application, gpointer user_data){
	if (selected_product == nullptr){
		Product* temp_prod = new Product();
		temp_prod->set_label_text(gtk_entry_buffer_get_text(product_name_buffer));
		selected_product->set_name(gtk_entry_buffer_get_text(product_name_buffer));
		char time_str[15];
		guint d, m, y;
		gtk_calendar_get_date(GTK_CALENDAR(cal_lifetime), &y, &m, &d);
		sprintf(time_str, "%d.%d.%d", d, m + 1, y);
		temp_prod->set_death_date(time_str);
		time_t add_time = time(NULL);
		tm add_date = *localtime(&add_time);
		sprintf(time_str, "%d.%d.%d", add_date.tm_mday, add_date.tm_mon + 1, add_date.tm_year + 1900);
		temp_prod->set_add_date(time_str);
		temp_prod->set_count(gtk_entry_buffer_get_text(product_count_buffer));
		temp_prod->set_icon(gtk_button_get_image(GTK_BUTTON(products_add_field_icon)));
		temp_prod->set_icon_id(current_icon_id);
		temp_prod->set_unit(gtk_combo_box_get_active(GTK_COMBO_BOX(units_button)));
		products->add_product(temp_prod);
		temp_prod->update_box();
		gtk_box_pack_start(GTK_BOX(products_list_box), temp_prod->get_box(), false, false, 3);
		gtk_widget_show_all(products_list_box);
		gtk_widget_hide(new_product_form);
		update_products_sort();
		products->print_into_file("./user_data/products.txt");
	}
	else{
		selected_product->set_label_text(gtk_entry_buffer_get_text(product_name_buffer));
		selected_product->set_name(gtk_entry_buffer_get_text(product_name_buffer));
		char time_str[15];
		guint d, m, y;
		gtk_calendar_get_date(GTK_CALENDAR(cal_lifetime), &y, &m, &d);
		sprintf(time_str, "%d.%d.%d", d, m + 1, y);
		selected_product->set_death_date(time_str);
		time_t add_time = time(NULL);
		tm add_date = *localtime(&add_time);
		sprintf(time_str, "%d.%d.%d", add_date.tm_mday, add_date.tm_mon + 1, add_date.tm_year + 1900);
		selected_product->set_add_date(time_str);
		selected_product->set_count(gtk_entry_buffer_get_text(product_count_buffer));
		selected_product->set_icon(gtk_button_get_image(GTK_BUTTON(products_add_field_icon)));
		selected_product->set_icon_id(current_icon_id);
		selected_product->set_unit(gtk_combo_box_get_active(GTK_COMBO_BOX(units_button)));
		selected_product->update_box();
		gtk_widget_show_all(products_list_box);
		gtk_widget_hide(new_product_form);
		update_products_sort();
		products->print_into_file("./user_data/products.txt");
	}
}

