#ifndef _CONTROLLER_HPP
#define _CONTROLLER_HPP

#include "shop.hpp"
#include "user.hpp"
#include "buyer.hpp"
#include "seller.hpp"
#include "offer.hpp"

#include <iostream>
#include <vector>

using namespace std;

typedef long long int Hashcode;
typedef int SID;

class Controller {
public:
	Controller(Shop* _shop);

	void import_products(string file_data , string type_of_product);
	void create_offer(SID user_sid , string product_id , string unit_price , string amount);
	void change_offer(string offer_id , string unit_price , string amount);
	void print_offers_by_order(string order , string cur_field);
	void generate_discount_code(string offer_id , double discount_per , string discount_number);
	void charge_wallet(SID user_sid , double amount);
	void post_comment(string product_id , string cur_comment);

	string get_products();
	string get_my_offers(SID user_sid);
	double get_wallet(SID user_sid);
	string get_offers_on_product(string product_id);
	string get_product_detail(string product_id);
	void get_comments(string product_id);
	string get_cart(SID user_sid);
	void get_orders(int count);
	void compare_products(string product_id_1 , string product_id_2);
	string submit_cart(SID user_sid);

	void print_all_offers();

	SID signup_user(string email , string user_name , string password , string type);
	SID login_user(string email , string password);
	void logout_user(SID user_sid);

	SID find_user_sid(string user_name);
	SID find_user_sid(User* user);

	Buyer* find_buyer(User* buyer);

	bool is_username_exist(string user_name);
	bool is_account_info_valid(string user_name , string password);

	void add_a_seller(string email , string user_name , string password);
	void add_a_buyer(string email , string user_name , string password);
	void add_to_cart(SID user_sid , string offer_id , string amount , string discount_code);


	bool is_active_user(string user_name);
	bool is_active_user(SID user_sid);

	bool is_user_admin(SID user_sid);
	bool is_user_buyer(SID user_sid);
	bool is_user_seller(SID user_sid);

	bool is_cur_user_a_buyer();
	bool is_cur_user_a_seller();

	string get_username(SID user_sid);

	void unactive_user(SID user_sid);

	vector < string > gen_random_code(int numbers_of_discount_codes);
	Hashcode compute_hash(string password);

private:
	vector < Buyer* > buyers;
	vector < Seller* > sellers;
	vector < User* > all_users;
	vector < SID > active_users;
	User* admin;
	Shop* shop;

	User* cur_user;
	int new_user_id;
};

#endif