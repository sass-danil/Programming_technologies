/*
 * Products_tab_utils.hpp
 *
 *  Created on: May 2, 2024
 *      Author: danil
 */

#ifndef PRODUCTS_TAB_UTILS_HPP_
#define PRODUCTS_TAB_UTILS_HPP_

#include <map>


void add_new_product (GtkApplication *application, gpointer user_data);


enum sorts_options{
	SORT_BY_NAME = 0,
	SORT_BY_DATE
};


enum order_options{
	ORDER_BY_ASCENDING = 0,
	ORDER_BY_DESCENDING
};


inline std::map<std::string, int> letters_map = {
    {"А", 1}, {"а", 1},
    {"Б", 2}, {"б", 2},
    {"В", 3}, {"в", 3},
    {"Г", 4}, {"г", 4},
    {"Д", 5}, {"д", 5},
    {"Е", 6}, {"е", 6},
    {"Ё", 7}, {"ё", 7},
    {"Ж", 8}, {"ж", 8},
    {"З", 9}, {"з", 9},
    {"И", 10}, {"и", 10},
    {"Й", 11}, {"й", 11},
    {"К", 12}, {"к", 12},
    {"Л", 13}, {"л", 13},
    {"М", 14}, {"м", 14},
    {"Н", 15}, {"н", 15},
    {"О", 16}, {"о", 16},
    {"П", 17}, {"п", 17},
    {"Р", 18}, {"р", 18},
    {"С", 19}, {"с", 19},
    {"Т", 20}, {"т", 20},
    {"У", 21}, {"у", 21},
    {"Ф", 22}, {"ф", 22},
    {"Х", 23}, {"х", 23},
    {"Ц", 24}, {"ц", 24},
    {"Ч", 25}, {"ч", 25},
    {"Ш", 26}, {"ш", 26},
    {"Щ", 27}, {"щ", 27},
    {"Ъ", 28}, {"ъ", 28},
    {"Ы", 29}, {"ы", 29},
    {"Ь", 30}, {"ь", 30},
    {"Э", 31}, {"э", 31},
    {"Ю", 32}, {"ю", 32},
    {"Я", 33}, {"я", 33},
    {"A", 34}, {"a", 34},
    {"B", 35}, {"b", 35},
    {"C", 36}, {"c", 36},
    {"D", 37}, {"d", 37},
    {"E", 38}, {"e", 38},
    {"F", 39}, {"f", 39},
    {"G", 40}, {"g", 40},
    {"H", 41}, {"h", 41},
    {"I", 42}, {"i", 42},
    {"J", 43}, {"j", 43},
    {"K", 44}, {"k", 44},
    {"L", 45}, {"l", 45},
    {"M", 46}, {"m", 46},
    {"N", 47}, {"n", 47},
    {"O", 48}, {"o", 48},
    {"P", 49}, {"p", 49},
    {"Q", 50}, {"q", 50},
    {"R", 51}, {"r", 51},
    {"S", 52}, {"s", 52},
    {"T", 53}, {"t", 53},
    {"U", 54}, {"u", 54},
    {"V", 55}, {"v", 55},
    {"W", 56}, {"w", 56},
    {"X", 57}, {"x", 57},
    {"Y", 58}, {"y", 58},
    {"Z", 59}, {"z", 59}
};

void update_products_sort();


void change_products_sort (GtkApplication *application, gpointer user_data);

void change_products_arrange (GtkApplication *application, gpointer user_data);

void add_new_product_to_list (GtkApplication *application, gpointer user_data);


#endif /* PRODUCTS_TAB_UTILS_HPP_ */
