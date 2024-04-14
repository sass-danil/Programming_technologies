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


GtkWidget *window;
GtkWidget *new_product_form;
GtkApplication *app;

GtkWidget* menu_button;
GtkWidget *main_horizontal_panned;

GtkWidget* products_list_overlay;
GtkWidget* products_list_box;
GtkWidget *products_area_panned;
GtkWidget* products_sort_button;
GtkWidget* products_arrange_button;
GtkWidget* products_plus_button;

GtkWidget *recipes_area_panned;
GtkWidget *recipes_sort_button;
GtkWidget *recipes_arrange_button;

GtkWidget *notes_area_panned;
GtkWidget *notes_sort_button;
GtkWidget *notes_arrange_button;

static GtkEntryBuffer* product_name_buffer;


Icon_Parser* icons_parser;
Product_Parser* products_parser;
Products_List* products;
Recipes_List* recipes;
Notes_List* notes;


std::map<char, std::string> measures_map{{0, ""},
										{1, "г."},
										{2, "мл."},
										{3, "шт."}};


static void add_new_product (GtkApplication *application, gpointer user_data){
	gtk_widget_show_all (new_product_form);
}


static void hide_product_form (GtkApplication *application, gpointer user_data){
	gtk_widget_hide(new_product_form);
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
	GtkWidget* arrange_up_icon;


//	-----		main area			-----

//  -----			Products area			-----
		GtkWidget *products_top_menu_panned, *products_plus_icon;
	//	-----		sort_arrange panel	-----
		products_top_menu_panned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
		products_sort_button = gtk_button_new();
		gtk_button_set_label(GTK_BUTTON(products_sort_button), "Sort By");
		products_arrange_button = gtk_button_new();
	//	gtk_button_set_label(GTK_BUTTON(arrange_button), "Arrange By");
		arrange_up_icon = gtk_image_new_from_file("up_button.png");
		gtk_button_set_image(GTK_BUTTON(products_arrange_button), arrange_up_icon);
		gtk_paned_pack1(GTK_PANED (products_top_menu_panned), products_sort_button, TRUE, FALSE);
		gtk_paned_pack2(GTK_PANED (products_top_menu_panned), products_arrange_button, TRUE, FALSE);

//		-----			List area			-----
		products_area_panned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
		g_object_ref(products_area_panned);
		products_list_overlay = gtk_overlay_new();
		gtk_overlay_add_overlay(GTK_OVERLAY(products_list_overlay), products_list_box);
		products_plus_button = gtk_button_new();
		products_plus_icon = gtk_image_new_from_file("plus_icon.png");
		gtk_widget_set_vexpand(products_plus_icon, FALSE);
		gtk_widget_set_hexpand(products_plus_icon, FALSE);
		gtk_button_set_image(GTK_BUTTON(products_plus_button), products_plus_icon);
		gtk_widget_set_vexpand(products_plus_button, FALSE);
		gtk_widget_set_hexpand(products_plus_button, FALSE);
		gtk_widget_set_halign(products_plus_button, GTK_ALIGN_END);
		gtk_widget_set_valign(products_plus_button, GTK_ALIGN_END);
	//	gtk_widget_is_composited(products_plus_button, TRUE);
		gtk_widget_set_opacity(products_plus_button, 0.3);
		g_signal_connect (products_plus_button, "clicked", G_CALLBACK (add_new_product), NULL);
		gtk_overlay_add_overlay(GTK_OVERLAY(products_list_overlay), products_plus_button);
		gtk_overlay_set_overlay_pass_through(GTK_OVERLAY(products_list_overlay), products_plus_button, true);
		gtk_paned_pack1(GTK_PANED (products_area_panned), products_top_menu_panned, FALSE, FALSE);
		gtk_paned_pack2(GTK_PANED (products_area_panned), products_list_overlay, TRUE, FALSE);

//  -----			Recipes area			-----
		GtkWidget *recipes_top_menu_panned, *recipes_list_box;
	//	-----		sort_arrange panel	-----
		recipes_top_menu_panned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
		recipes_sort_button = gtk_button_new();
		gtk_button_set_label(GTK_BUTTON(recipes_sort_button), "Sort By");
		recipes_arrange_button = gtk_button_new();
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
		GtkAdjustment* h_adj = gtk_adjustment_new(1.0, 1.0, 1.0, 0.1, 0.1, 1.0);
		GtkAdjustment* v_adj = gtk_adjustment_new(1.0, 1.0, 1.0, 0.1, 0.1, 1.0);
		GtkWidget* scrolled = gtk_scrolled_window_new(h_adj, v_adj);
		gtk_container_add(GTK_CONTAINER(scrolled), recipes_list_box);
		gtk_paned_pack2(GTK_PANED (recipes_area_panned), scrolled, TRUE, FALSE);



//  -----			Notes area			-----
		GtkWidget *notes_top_menu_panned, *notes_list_box;
	//	-----		sort_arrange panel	-----
		notes_top_menu_panned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
		notes_sort_button = gtk_button_new();
		gtk_button_set_label(GTK_BUTTON(notes_sort_button), "Sort By");
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
	gtk_container_add (GTK_CONTAINER (window), main_horizontal_panned);
	g_signal_connect (window, "delete-event", G_CALLBACK (close_all), NULL);



//	-----		new_product_form	-----
	new_product_form = gtk_application_window_new (application);
	gtk_window_set_title (GTK_WINDOW (new_product_form), "Add New Product");
	gtk_window_set_position(GTK_WINDOW(new_product_form), GTK_WIN_POS_CENTER);
	GtkWidget* create_products_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
	GtkWidget* product_name_label = gtk_label_new("Название продукта");
	product_name_buffer = gtk_entry_buffer_new("", -1);
	GtkWidget* product_name_field = gtk_entry_new_with_buffer(product_name_buffer);
	gtk_container_add (GTK_CONTAINER (new_product_form), create_products_box);
	gtk_box_pack_start(GTK_BOX(create_products_box), product_name_label, FALSE, FALSE, 3);
	gtk_box_pack_start(GTK_BOX(create_products_box), product_name_field, FALSE, FALSE, 3);
	GtkWidget* product_lifetime_label = gtk_label_new("Годен до");
	gtk_box_pack_start(GTK_BOX(create_products_box), product_lifetime_label, FALSE, FALSE, 3);
	GtkWidget* product_count_label = gtk_label_new("Количество");
	gtk_box_pack_start(GTK_BOX(create_products_box), product_count_label, FALSE, FALSE, 3);
	g_signal_connect (new_product_form, "delete-event", G_CALLBACK (hide_product_form), NULL);




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


	recipes = new Recipes_List();
	recipes->parse_recipes();

	notes = new Notes_List();
	notes->parse_notes();


	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
