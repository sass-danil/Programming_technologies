/*
 * add_product_utils.hpp
 *
 *  Created on: May 2, 2024
 *      Author: danil
 */

#ifndef ADD_PRODUCT_UTILS_HPP_
#define ADD_PRODUCT_UTILS_HPP_

/* Vstavlyaetsya neposredstvenno v main file, poetomu net nuzhdi v extern'ah */

void product_name_changed (GtkApplication *application, gpointer user_data){
	if (icons_parser->get_icon(std::string(gtk_entry_buffer_get_text(product_name_buffer))) != nullptr){
//		products_add_field_icon = icons_parser->get_icon(std::string(gtk_entry_buffer_get_text(product_name_buffer)));
		g_object_ref(gtk_button_get_image(GTK_BUTTON(products_add_field_icon)));
		gtk_button_set_image(GTK_BUTTON(products_add_field_icon), icons_parser->get_icon(std::string(gtk_entry_buffer_get_text(product_name_buffer))));
	}
	else{
		g_object_ref(gtk_button_get_image(GTK_BUTTON(products_add_field_icon)));
		gtk_button_set_image(GTK_BUTTON(products_add_field_icon), icons_parser->get_icon(0));
	}
	current_icon_id = icons_parser->get_icon_name_id(std::string(gtk_entry_buffer_get_text(product_name_buffer)));
}

#endif /* ADD_PRODUCT_UTILS_HPP_ */
