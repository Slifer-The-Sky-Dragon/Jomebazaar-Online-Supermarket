#ifndef _SHOP_HPP
#define _SHOP_HPP

#include <vector>
#include "product.hpp"
#include "mobile.hpp"
#include "car.hpp"
#include "tv.hpp"
#include "offer.hpp"
#include "user.hpp"
#include "buyer.hpp"
#include "seller.hpp"
#include "order.hpp"

using namespace std;

typedef vector < string > Information;

class Shop {
public:
	Shop();
	void import_products(string file_data , string type);
	string get_products();
	void create_offer(User* seller , string product_id , string unit_price , string amount);
	void change_offer(User* seller , string offer_id , string unit_price , string amount);	
	void add_comment_on_product(User* buyer , string product_id , string cur_comment);
	void compare_products(string product_id_1 , string product_id_2);

	void print_offers_by_order(string order , string cur_field);
	void print_all_offers();
	string print_user_offers(User* seller);
	string get_offers_on_product(string product_id);
	string print_offers_on_product(string product_id);
	string print_product_deatil(string product_id);
	void print_comments(string product_id);
	void add_discount_code(User* seller , string offer_id , double discount_per 
															, vector < string > discount_codes);
	void add_to_buyer_cart(Buyer* buyer , string offer_id , string amount , string discount_code);

private:
	vector < Product* > products;
	vector < Offer* > offers;
	int new_product_id;
	int new_offer_id;

	Information extract_info_from_csv(string csv_string);

	void import_products_from_file(stringstream& file);
	Information get_label_from_file(stringstream& file);
	void add_product_from_file(stringstream& file , Information labels , string type);
	void import_products_from_file(stringstream& file , string type);
	
	void add_new_product(int id , Information product_info , Information labels , string type);
	void add_new_offer(User* seller , string product_id , string unit_price , string amount);

	bool is_product_id_exist(string product_id);
	bool is_offer_id_exist(string offer_id);
	bool is_seller_offerd_on_this_product_before(User* seller , string product_id);

	void sort_offers(string order , string sort_field);
	void sort_offers_by_id();
	void sort_offers_by_price_ascending();
	void sort_offers_by_price_descending();

	Offer* find_offer(string offer_id);
	Product* find_product(string product_id);
	Product* find_product(int product_id);



};

#endif