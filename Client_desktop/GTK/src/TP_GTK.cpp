//============================================================================
// Name        : TP_GTK.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtk/gtk.h>
#include <cstdio>
#include <map>
#include <cstring>

#include "IconParser.hpp"
#include "ProductParser.hpp"
#include "RecipesList.hpp"
#include "NotesList.hpp"
#include "Products_tab_utils.hpp"


GtkWidget *window;
GtkApplication *app;

GtkWidget* menu_button;
GtkWidget *main_horizontal_panned;

GtkWidget* products_list_box;
GtkWidget *products_area_panned;
GtkWidget* products_sort_button;
GtkWidget* products_arrange_button;
GtkWidget* products_plus_button;

		/* Add Product form */
GtkWidget *new_product_form;
GtkWidget* products_add_field_icon;
GtkWidget *units_button;
GtkEntryBuffer* product_name_buffer;
GtkEntryBuffer* product_count_buffer;
GtkWidget* cal_lifetime;
int current_icon_id = 0;
GtkWidget* add_product_button;
GtkWidget* delete_product_message;


GtkWidget* arrange_up_icon;
GtkWidget* arrange_down_icon;

GtkWidget *recipes_area_panned;
GtkWidget *recipes_sort_button;
GtkWidget *recipes_arrange_button;

GtkWidget *notes_area_panned;
GtkWidget *notes_sort_button;
GtkWidget *notes_arrange_button;



Icon_Parser* icons_parser;
Product_Parser* products_parser;
Products_List* products;
Recipes_List* recipes;
Notes_List* notes;


std::map<char, std::string> measures_map{{0, ""},
										{1, "г."},
										{2, "мл."},
										{3, "шт."}};


#include "add_product_utils.hpp"



void set_theme(const char *cssFile) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GError *error = NULL;

    if (gtk_css_provider_load_from_path(provider, cssFile, &error)) {
        gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                                   GTK_STYLE_PROVIDER(provider),
                                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    } else {
        g_printerr("Error loading CSS file: %s\n", error->message);
        g_error_free(error);
    }

    g_object_unref(provider);
}



static void hide_product_form (GtkApplication *application, gpointer user_data){
	gtk_widget_hide(new_product_form);
}

static void hide_delete_message (GtkApplication *application, gpointer user_data){
	gtk_widget_hide(delete_product_message);
}

Product* selected_product = nullptr;
static void delete_product (GtkApplication *application, gpointer user_data){
	products->delete_product(selected_product);
	gtk_widget_hide(delete_product_message);
	products->print_into_file("./user_data/products.txt");
}


static void close_all (GtkApplication *application, gpointer user_data){
	gtk_widget_destroy(new_product_form);
	gtk_widget_destroy(window);
	std::cout << "All is closed" << std::endl;
	exit(0);
}



static void change_active_tab (GtkApplication *application, gpointer user_data){
	std::cout << "Tab changed" << std::endl;
	std::cout << "Current tab is " << gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(menu_button)) << std::endl;
	if (gtk_paned_get_child2(GTK_PANED(main_horizontal_panned)) != NULL)
		gtk_container_remove(GTK_CONTAINER(main_horizontal_panned), gtk_paned_get_child2(GTK_PANED(main_horizontal_panned)));
	if (strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(menu_button)), "Products") == 0){
		gtk_paned_pack2(GTK_PANED (main_horizontal_panned), products_area_panned, FALSE, FALSE);
		std::cout << "Changed to Products" << std::endl;
	}
	else if (strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(menu_button)), "Recipes") == 0){
		gtk_paned_pack2(GTK_PANED (main_horizontal_panned), recipes_area_panned, FALSE, FALSE);
		std::cout << "Changed to Recipes" << std::endl;
	}
	else if (strcmp(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(menu_button)), "Notes") == 0){
		gtk_paned_pack2(GTK_PANED (main_horizontal_panned), notes_area_panned, FALSE, FALSE);
		std::cout << "Changed to Notes" << std::endl;
	}
	if (gtk_paned_get_child2(GTK_PANED(main_horizontal_panned)) != NULL)
		gtk_widget_show_all(gtk_paned_get_child2(GTK_PANED(main_horizontal_panned)));
}



static void activate (GtkApplication *application, gpointer user_data){
/*
 * Init all window's elements
 */
	GtkWidget* menu_bar;
	GtkWidget *side_menu_panned;
	GtkAdjustment* h_adj = gtk_adjustment_new(1.0, 1.0, 1.0, 0.1, 0.1, 1.0);
	GtkAdjustment* v_adj = gtk_adjustment_new(1.0, 1.0, 1.0, 0.1, 0.1, 1.0);


//	-----		main area			-----

//  -----			Products area			-----
		GtkWidget *products_plus_icon;
	//	-----		sort_arrange panel	-----
		products_sort_button = gtk_button_new();
		gtk_button_set_label(GTK_BUTTON(products_sort_button), "Сортировка по имени");
		gtk_widget_set_name(products_sort_button, "sort_button");
		g_signal_connect (products_sort_button, "clicked", G_CALLBACK (change_products_sort), NULL);
		products_arrange_button = gtk_button_new();
		gtk_widget_set_name(products_arrange_button, "arrange_button");
	//	gtk_button_set_label(GTK_BUTTON(arrange_button), "Arrange By");
		arrange_up_icon = gtk_image_new_from_file("up_button.png");
		g_object_ref(arrange_up_icon);
		arrange_down_icon = gtk_image_new_from_file("down_button.png");
		g_object_ref(arrange_down_icon);
		gtk_button_set_image(GTK_BUTTON(products_arrange_button), arrange_up_icon);
		g_signal_connect (products_arrange_button, "clicked", G_CALLBACK (change_products_arrange), NULL);
//		GtkWidget* button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
//		gtk_box_pack_start(GTK_BOX(button_box), products_arrange_button, false, false, 0);
//		gtk_widget_set_size_request(button_box, 30, 30);
		GtkWidget* products_sort_arrange_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
		gtk_widget_set_name(products_sort_arrange_box, "sort_arrange_box");
		gtk_widget_set_halign(products_sort_button, GTK_ALIGN_CENTER);
		gtk_box_pack_start(GTK_BOX(products_sort_arrange_box), products_sort_button, true, false, 3);
		gtk_box_pack_end(GTK_BOX(products_sort_arrange_box), products_arrange_button, false, false, 0);

//		-----			List area			-----
		products_area_panned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
		g_object_ref(products_area_panned);
		GtkWidget* products_list_main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
		GtkWidget* products_scrolled = gtk_scrolled_window_new(h_adj, v_adj);
		products_plus_button = gtk_button_new();
		gtk_widget_set_name(products_plus_button, "add_product_button");
		gtk_widget_set_halign(products_plus_button, GTK_ALIGN_CENTER);
		products_plus_icon = gtk_image_new_from_file("plus_icon.png");
		gtk_widget_set_vexpand(products_plus_icon, FALSE);
		gtk_widget_set_hexpand(products_plus_icon, FALSE);
//		gtk_button_set_image(GTK_BUTTON(products_plus_button), products_plus_icon);
//		gtk_widget_set_vexpand(products_plus_button, FALSE);
//		gtk_widget_set_hexpand(products_plus_button, FALSE);
//		gtk_widget_set_halign(products_plus_button, GTK_ALIGN_END);
//		gtk_widget_set_valign(products_plus_button, GTK_ALIGN_END);
		gtk_button_set_label(GTK_BUTTON(products_plus_button), "Добавить продукт");
	//	gtk_widget_is_composited(products_plus_button, TRUE);
//		gtk_widget_set_opacity(products_plus_button, 0.3);
		g_signal_connect (products_plus_button, "clicked", G_CALLBACK (add_new_product), NULL);
		gtk_container_add(GTK_CONTAINER(products_scrolled), products_list_box);
		gtk_box_pack_start(GTK_BOX(products_list_main_box), products_scrolled, true, true, 3);
		gtk_box_pack_end(GTK_BOX(products_list_main_box), products_plus_button, false, false, 3);
		gtk_widget_set_name(products_list_main_box, "sort_arrange_box");
		gtk_paned_pack1(GTK_PANED (products_area_panned), products_sort_arrange_box, FALSE, FALSE);
		gtk_paned_pack2(GTK_PANED (products_area_panned), products_list_main_box, TRUE, FALSE);

//  -----			Recipes area			-----
		GtkWidget *recipes_top_menu_panned, *recipes_list_box;
	//	-----		sort_arrange panel	-----
		recipes_top_menu_panned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
		recipes_sort_button = gtk_button_new();
		gtk_button_set_label(GTK_BUTTON(recipes_sort_button), "Sort By");
		gtk_widget_set_name(recipes_sort_button, "sort_button");
		recipes_arrange_button = gtk_button_new();
		gtk_widget_set_name(recipes_arrange_button, "arrange_button");
		arrange_up_icon = gtk_image_new_from_file("up_button.png");
		gtk_button_set_image(GTK_BUTTON(recipes_arrange_button), arrange_up_icon);
		gtk_paned_pack1(GTK_PANED (recipes_top_menu_panned), recipes_sort_button, TRUE, FALSE);
		gtk_paned_pack2(GTK_PANED (recipes_top_menu_panned), recipes_arrange_button, TRUE, FALSE);

//		-----			List area			-----
		recipes_area_panned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
		g_object_ref(recipes_area_panned);
		recipes_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
		gtk_paned_pack1(GTK_PANED (recipes_area_panned), recipes_top_menu_panned, FALSE, FALSE);
		recipes->set_box(recipes_list_box);
		recipes->update_box();
		GtkWidget* scrolled = gtk_scrolled_window_new(h_adj, v_adj);
		gtk_container_add(GTK_CONTAINER(scrolled), recipes_list_box);
		gtk_paned_pack2(GTK_PANED (recipes_area_panned), scrolled, TRUE, FALSE);



//  -----			Notes area			-----
		GtkWidget *notes_top_menu_panned, *notes_list_box;
	//	-----		sort_arrange panel	-----
		notes_top_menu_panned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
		notes_sort_button = gtk_button_new();
		gtk_button_set_label(GTK_BUTTON(notes_sort_button), "Sort By");
		gtk_widget_set_name(notes_sort_button, "sort_button");
		notes_arrange_button = gtk_button_new();
		arrange_up_icon = gtk_image_new_from_file("up_button.png");
		gtk_button_set_image(GTK_BUTTON(notes_arrange_button), arrange_up_icon);
		gtk_paned_pack1(GTK_PANED (notes_top_menu_panned), notes_sort_button, TRUE, FALSE);
		gtk_paned_pack2(GTK_PANED (notes_top_menu_panned), notes_arrange_button, TRUE, FALSE);

//		-----			List area			-----
		notes_area_panned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
		g_object_ref(notes_area_panned);
		notes_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
		gtk_paned_pack1(GTK_PANED (notes_area_panned), notes_top_menu_panned, FALSE, FALSE);
		notes->set_box(notes_list_box);
		notes->update_box();
		GtkWidget* notes_scrolled = gtk_scrolled_window_new(h_adj, v_adj);
		gtk_container_add(GTK_CONTAINER(notes_scrolled), notes_list_box);
		gtk_paned_pack2(GTK_PANED (notes_area_panned), notes_scrolled, TRUE, FALSE);





//	-----		side panel			----
	menu_bar = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	menu_button = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu_button), "Products");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu_button), "Recipes");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu_button), "Notes");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(menu_button), "Account");
	gtk_combo_box_set_active(GTK_COMBO_BOX(menu_button), 0);
	gtk_box_pack_start(GTK_BOX(menu_bar), menu_button, FALSE, FALSE, 3);
	g_signal_connect (menu_button, "changed", G_CALLBACK (change_active_tab), NULL);

//	-----		Window				-----
	window = gtk_application_window_new (application);
	gtk_window_set_title (GTK_WINDOW (window), "TP");
	gtk_window_set_default_size (GTK_WINDOW (window), 1200, 600);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	main_horizontal_panned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_paned_pack1(GTK_PANED (main_horizontal_panned), menu_bar, FALSE, FALSE);
	gtk_paned_pack2(GTK_PANED (main_horizontal_panned), products_area_panned, FALSE, FALSE);
	gtk_paned_set_wide_handle(GTK_PANED(main_horizontal_panned), false);
	gtk_container_add (GTK_CONTAINER (window), main_horizontal_panned);
	g_signal_connect (window, "delete-event", G_CALLBACK (close_all), NULL);



//	-----		new_product_form	-----
	new_product_form = gtk_application_window_new (application);
	gtk_window_set_title (GTK_WINDOW (new_product_form), "Add New Product");
	gtk_window_set_position(GTK_WINDOW(new_product_form), GTK_WIN_POS_CENTER);
	GtkWidget* create_products_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	products_add_field_icon = gtk_button_new();
	gtk_widget_set_name(products_add_field_icon, "product_icon_button");
	gtk_button_set_image(GTK_BUTTON(products_add_field_icon), icons_parser->get_icon(0));
	GtkWidget* add_product_paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
	gtk_paned_add1(GTK_PANED(add_product_paned), products_add_field_icon);
	GtkWidget* add_product_paned_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	gtk_paned_add2(GTK_PANED(add_product_paned), add_product_paned_box);
	GtkWidget* product_name_label = gtk_label_new("Название продукта");
	product_name_buffer = gtk_entry_buffer_new("", -1);
	GtkWidget* product_name_field = gtk_entry_new_with_buffer(product_name_buffer);
	g_signal_connect (product_name_field, "changed", G_CALLBACK (product_name_changed), NULL);
	gtk_container_add (GTK_CONTAINER (new_product_form), create_products_box);
	gtk_box_pack_start(GTK_BOX(add_product_paned_box), product_name_label, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(add_product_paned_box), product_name_field, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(create_products_box), add_product_paned, FALSE, FALSE, 3);
	GtkWidget* product_lifetime_label = gtk_label_new("Годен до");
	gtk_box_pack_start(GTK_BOX(create_products_box), product_lifetime_label, FALSE, FALSE, 3);
	cal_lifetime = gtk_calendar_new();
	gtk_box_pack_start(GTK_BOX(create_products_box), cal_lifetime, FALSE, FALSE, 3);
	GtkWidget* product_count_label = gtk_label_new("Количество");
	gtk_box_pack_start(GTK_BOX(create_products_box), product_count_label, FALSE, FALSE, 3);
	GtkWidget* count_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
	product_count_buffer = gtk_entry_buffer_new("", -1);
	GtkWidget* product_count_field = gtk_entry_new_with_buffer(product_count_buffer);
	gtk_box_pack_start(GTK_BOX(count_box), product_count_field, TRUE, TRUE, 3);
	units_button = gtk_combo_box_text_new();
	int i;
	for (i = 0; i < measures_map.size() ;i++){
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(units_button), measures_map[i].c_str());
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(units_button), 0);
	gtk_box_pack_start(GTK_BOX(count_box), units_button, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(create_products_box), count_box, FALSE, FALSE, 3);
	add_product_button = gtk_button_new_with_label("Добавить продукт");
	g_signal_connect (add_product_button, "clicked", G_CALLBACK (add_new_product_to_list), NULL);
	gtk_box_pack_start(GTK_BOX(create_products_box), add_product_button, FALSE, FALSE, 3);

	g_signal_connect (new_product_form, "delete-event", G_CALLBACK (hide_product_form), NULL);


	delete_product_message = gtk_application_window_new (application);
	gtk_window_set_title (GTK_WINDOW (delete_product_message), "Подтверждение удаления");
	gtk_window_set_position(GTK_WINDOW(delete_product_message), GTK_WIN_POS_CENTER);
	gtk_window_set_decorated(GTK_WINDOW(delete_product_message), false);
	GtkWidget* delete_vert_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	gtk_widget_set_name(delete_vert_box, "delete_product_box");
	GtkWidget* delete_label = gtk_label_new("Вы уверены, что хотите удалить\nэтот продукт из списка?");
	gtk_widget_set_name(delete_label, "delete_product_message");
	gtk_box_pack_start(GTK_BOX(delete_vert_box), delete_label, false, false, 3);
	GtkWidget* delete_hor_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 3);
	GtkWidget* product_delete_button = gtk_button_new_with_label("Да");
	gtk_widget_set_name(product_delete_button, "delete_product_yes_button");
	g_signal_connect (product_delete_button, "clicked", G_CALLBACK (delete_product), NULL);
	GtkWidget* product_not_delete_button = gtk_button_new_with_label("Нет");
	gtk_widget_set_name(product_not_delete_button, "delete_product_no_button");
	g_signal_connect (product_not_delete_button, "clicked", G_CALLBACK (hide_delete_message), NULL);
	gtk_box_pack_start(GTK_BOX(delete_hor_box), product_not_delete_button, false, false, 3);
	gtk_box_pack_end(GTK_BOX(delete_hor_box), product_delete_button, false, false, 3);
	gtk_box_pack_start(GTK_BOX(delete_vert_box), delete_hor_box, false, false, 3);
	gtk_container_add (GTK_CONTAINER (delete_product_message), delete_vert_box);
	g_signal_connect (delete_product_message, "delete-event", G_CALLBACK (hide_delete_message), NULL);





	gtk_widget_show_all (window);
}


int main(int argc, char **argv) {
	int status;
	std::setlocale(LC_NUMERIC, "POSIX");

	gtk_init(&argc, &argv); // @suppress("Invalid arguments")

	//TODO get data from server

	icons_parser = new Icon_Parser();
	icons_parser->print_into_console();

	products_parser = new Product_Parser();
	products = new Products_List();
	products_parser->parse_products(products, "./user_data/products.txt");

	products->print_into_console();


	std::cout << "Measures_map: " << std::endl;
	std::cout << measures_map[0] << std::endl;
	std::cout << measures_map[1] << std::endl;
	std::cout << measures_map[2] << std::endl;
	std::cout << measures_map[3] << std::endl;


	products_list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	products_parser->add_products_to_box(products, products_list_box);
	update_products_sort();		/*sort_products_by_name */


	recipes = new Recipes_List();
	recipes->parse_recipes();

	notes = new Notes_List();
	notes->parse_notes();


	set_theme("theme.css");


	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
