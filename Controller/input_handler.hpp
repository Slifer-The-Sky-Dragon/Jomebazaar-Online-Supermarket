#ifndef _INPUT_HANDLER_HPP
#define _INPUT_HANDLER_HPP

#include "controller.hpp"
#include "product.hpp"
#include "mobile.hpp"
#include <sstream>

class Input_handler {
public:
	Input_handler(Controller* _controller) : controller(_controller) {};
	~Input_handler() {};

	void handle_input(string input);
private:
	Controller* controller;

	void handle_post_input(stringstream& command);
	void handle_import_product(stringstream& command);
	void handle_signup(stringstream& command);
	void handle_login(stringstream& command);
	void handle_logout(stringstream& command);

	void handle_post_offer(stringstream& command);
	void handle_change_offer(stringstream& command);
	void handle_generate_discount(stringstream& command);
	void handle_charge_wallet(stringstream& command);
	void handle_comment(stringstream& command);
	void handle_add_to_cart(stringstream& command);
	void handle_submit_cart(stringstream& command);

	void handle_get_input(stringstream& command);
	void handle_get_offers(stringstream& command);
	void handle_get_all_offers(stringstream& command);
	void handle_get_products(stringstream& command);
	void handle_get_my_offers(stringstream& command);
	void handle_get_wallet(stringstream& command);
	void handle_get_offers_on_product(stringstream& command);
	void handle_get_product_detail(stringstream& command);
	void handle_get_comments(stringstream& command);
	void handle_get_compare(stringstream& command);
	void handle_get_cart(stringstream& command);
	void handle_get_orders(stringstream& command);

	string get_entered_comment(stringstream& command);

	bool is_valid_post_input_type(string type);
	bool is_valid_get_input_type(string type);

	bool is_valid_product(string type_of_product);
	bool is_valid_user_type(string user_type);

	bool is_valid_import_product_inputs(string cur_type_sign , string type_of_product 
														, string file_path_field , string file_path);

	bool is_valid_signup_inputs(string username_field , string email_field 
											, string password_field , string type , string type_field);

	bool is_valid_get_offers_inputs(string order_field , string order , string field 
																				, string sort_field);

	bool is_valid_post_offer_field(string product_id_field , string unit_price_field 
																	, string amount_field);

	bool is_valid_change_offer_inputs(string offer_id_field , string offer_id
						 , string unit_price_field , string unit_price , string amount , string amount_field);
	
	bool is_valid_discount_gen_inputs(string offer_id_field , string offer_id , string discount_per_field 
						, double discount_per , string discount_number_field , string discount_number);

	bool is_valid_comment_inputs(string product_id_field , string product_id
												 , string comment_field , string comment);


	bool is_valid_get_compare_inputs(string product_id_1_field , string product_id_1 
														, string product_id_2_field , string product_id_2);

	bool is_valid_add_to_cart_input(string offer_id_field , string offer_id ,
		 				string amount_field , string amount, string discount_code_field , string discount_code);


};

#endif