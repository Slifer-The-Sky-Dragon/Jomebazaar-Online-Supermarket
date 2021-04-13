#include "input_handler.hpp"
#include "bad_req.hpp"
#include "not_found.hpp"
#include <sstream>
#include <iostream>

#define EMPTY ""
#define SPACE ' '

#define NO_VALUE -1
#define DOUBLE_NO_VALUE 0.0

#define IMPORT_PRODUCTS "importProducts"
#define SIGN_UP "signup"
#define LOGIN "login"
#define LOGOUT "logout"
#define POST_OFFER "offer"
#define CHANGE_OFFER "changeOffer"
#define DISCOUNT_GEN "generateDiscountCode"
#define CHARGE_WALLET "chargeWallet"
#define COMMENT "comment"
#define ADD_TO_CART "addToCart"
#define SUBMIT_CART "submitCart"

#define GET_OFFERS "offers"
#define GET_PRODUCTS "getProducts"
#define GET_MY_OFFERS "myOffers"
#define GET_WALLET "wallet"
#define GET_OFFERS_ON_PRODUCT "offersOnProduct"
#define GET_PRODUCT_DETAIL "productDetail"
#define GET_COMMENT "comments"
#define GET_COMPARE "compare"
#define GET_CART "cart"
#define GET_ORDERS "orders"

#define QUESTION_SIGN "?"
#define TYPE_FIELD "type"
#define FILE_PATH_FIELD "filePath"
#define EMAIL_FIELD "email"
#define USERNAME_FIELD "username"
#define PASSWORD_FIELD "password"
#define ORDER_FIELD "order"
#define PRODUCT_ID_FIELD "productId"
#define OFFER_UNIT_PRICE_FIELD "offerUnitPrice"
#define OFFER_AMOUNT_FIELD "offerAmount"
#define OFFER_ID_FIELD "offerId"
#define COUNT_FIELD "count"
#define DISCOUNT_PER_FIELD "discountPercent"
#define DISCOUNT_NUM_FIELD "discountNumber"
#define AMOUNT_FIELD "amount"
#define COMMENT_FIELD "comment"
#define PRODUCT_ID_1_FIELD "productId1"
#define PRODUCT_ID_2_FIELD "productId2"

#define SELLER "seller"
#define BUYER "buyer"

#define ASCENDING "ASCEND"
#define DESCENDING "DESCEND"

#define FIELD "field"
#define OFFER_ID "offerId"
#define OFFER_PRICE "offerPrice"

#define MOBILE "mobile"
#define TV "tv"
#define CAR "car"

#define POST "POST"
#define GET "GET"

using namespace std;



const vector < string > get_input_types = {GET_OFFERS , GET_PRODUCTS , GET_MY_OFFERS , GET_WALLET ,
										 GET_OFFERS_ON_PRODUCT  , GET_PRODUCT_DETAIL , GET_COMMENT ,
										 GET_COMPARE , GET_CART , GET_ORDERS};


const vector < string > post_input_types = {LOGOUT , SUBMIT_CART , IMPORT_PRODUCTS , SIGN_UP , LOGIN , 
										  POST_OFFER , CHANGE_OFFER , DISCOUNT_GEN , CHARGE_WALLET ,
										  COMMENT , ADD_TO_CART};


void Input_handler::handle_input(string input){

	stringstream command(input);

	string type_of_input;
	command >> type_of_input;

	try{
		if(type_of_input == POST)
			handle_post_input(command);
		else if(type_of_input == GET)
			handle_get_input(command);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}

bool Input_handler::is_valid_post_input_type(string type){
	for(int type_number = 0 ; type_number < post_input_types.size() ; type_number++){
		string cur_type = post_input_types[type_number];
		if(cur_type == type)
			return true;
	}
	return false;
}

void Input_handler::handle_post_input(stringstream& command){
	string type , questionare;
	command >> type >> questionare;

	try{
		if(is_valid_post_input_type(type) == false)
			throw Not_found();

		if(type == LOGOUT) handle_logout(command);

		else if(type == SUBMIT_CART) 
			handle_submit_cart(command);

		else if(type == IMPORT_PRODUCTS && questionare == QUESTION_SIGN) 
			handle_import_product(command);

		else if(type == SIGN_UP && questionare == QUESTION_SIGN) 
			handle_signup(command);

		else if(type == LOGIN && questionare == QUESTION_SIGN) 
			handle_login(command);
		
		else if(type == POST_OFFER && questionare == QUESTION_SIGN) 
			handle_post_offer(command);

		else if(type == CHANGE_OFFER && questionare == QUESTION_SIGN) 
			handle_change_offer(command);
		
		else if(type == DISCOUNT_GEN && questionare == QUESTION_SIGN) 
			handle_generate_discount(command);
		
		else if(type == CHARGE_WALLET && questionare == QUESTION_SIGN) 
			handle_charge_wallet(command);
		
		else if(type == COMMENT && questionare == QUESTION_SIGN) 
			handle_comment(command);
		
		else if(type == ADD_TO_CART && questionare == QUESTION_SIGN) 
			handle_add_to_cart(command);

		else 
			throw Bad_request();
	}catch(Not_found e){
		cout << e.what();
	}catch(Bad_request e){
		cout << e.what();
	}
	
}

bool Input_handler::is_valid_product(string type_of_product){
	if(type_of_product == MOBILE || type_of_product == TV || type_of_product == CAR)
		return true;
	return false;
}

bool Input_handler::is_valid_import_product_inputs(string cur_type_sign , string type_of_product 
														, string file_path_field , string file_path){
	if(cur_type_sign != TYPE_FIELD)
		return false;
	if(is_valid_product(type_of_product) == false)
		return false;
	if(file_path_field != FILE_PATH_FIELD)
		return false;
	if(file_path == EMPTY)
		return false;
	return true;
}

void Input_handler::handle_import_product(stringstream& command){
	string cur_type_sign , type_of_product;
	string file_path_field , file_path = EMPTY;

	command >> cur_type_sign >> type_of_product;
	command >> file_path_field >> file_path;

	try{
		if(is_valid_import_product_inputs(cur_type_sign , type_of_product , file_path_field , file_path))
			controller -> import_products(file_path , type_of_product);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}

bool Input_handler::is_valid_user_type(string user_type){
	if(user_type == BUYER || user_type == SELLER)
		return true;
	return false;
}

bool Input_handler::is_valid_signup_inputs(string username_field , string email_field 
											, string password_field , string type , string type_field){
	if(username_field != USERNAME_FIELD)
		return false;
	if(email_field != EMAIL_FIELD)
		return false;
	if(password_field != PASSWORD_FIELD)
		return false;
	if(is_valid_user_type(type) == false)
		return false;
	if(type_field != TYPE_FIELD){
		if(type_field == EMPTY && type == BUYER){
			return true;
		}
		else{
			return false;
		}
	}
	return true;
}

void Input_handler::handle_signup(stringstream& command){
	string username_field , username;
	string email_field , email;
	string password_field , password;
	string type_field = EMPTY , type = EMPTY;

	command >> email_field >> email >> username_field >> username;
	command >> password_field >> password >> type_field >> type;

	if(type == EMPTY)
		type = BUYER;

	try{
		if(is_valid_signup_inputs(username_field , email_field , password_field , type , type_field))
			controller -> signup_user(email , username , password , type);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}

void Input_handler::handle_login(stringstream& command){
	string email_field , email;
	string password_field , password;
	command >> email_field >> email >> password_field >> password;
	try{
		if(email_field == EMAIL_FIELD && password_field == PASSWORD_FIELD)
			controller -> login_user(email , password);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}

void Input_handler::handle_logout(stringstream& command){
	controller -> logout_user();
}

bool Input_handler::is_valid_post_offer_field(string product_id_field , 
												string unit_price_field , string amount_field){
	if(product_id_field != PRODUCT_ID_FIELD)
		return false;
	if(unit_price_field != OFFER_UNIT_PRICE_FIELD)
		return false;
	if(amount_field != OFFER_AMOUNT_FIELD)
		return false;
	return true;
}

void Input_handler::handle_post_offer(stringstream& command){
	string product_id_field , product_id;
	string unit_price_field , amount_field;
	string unit_price = EMPTY , amount = EMPTY;

	command >> product_id_field >> product_id >> unit_price_field >> unit_price;
	command >> amount_field >> amount;

	try{
		if(is_valid_post_offer_field(product_id_field , unit_price_field , amount_field)){
			if(unit_price != EMPTY && amount != EMPTY){
				controller -> create_offer(product_id , unit_price , amount);
			}
			else
				throw Bad_request();
		}
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}

bool Input_handler::is_valid_change_offer_inputs(string offer_id_field , string offer_id
						 , string unit_price_field , string unit_price , string amount_field , string amount){
	
	if(offer_id_field != OFFER_ID_FIELD)
		return false;
	if(unit_price_field != OFFER_UNIT_PRICE_FIELD)
		return false;
	if(amount_field != OFFER_AMOUNT_FIELD)
		return false;
	if(offer_id == EMPTY || amount == EMPTY || unit_price == EMPTY)
		return false;
	return true;
}


void Input_handler::handle_change_offer(stringstream& command){
	string offer_id_field , offer_id = EMPTY;
	string unit_price_field , amount_field;
	string unit_price = EMPTY , amount = EMPTY;

	command >> offer_id_field >> offer_id;
	command >> unit_price_field >> unit_price;
	command >> amount_field >> amount;

	try{
		if(is_valid_change_offer_inputs(offer_id_field , offer_id , unit_price_field 
															, unit_price , amount_field , amount) == true)
			controller -> change_offer(offer_id , unit_price , amount);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}


bool Input_handler::is_valid_discount_gen_inputs(string offer_id_field , string offer_id
 , string discount_per_field , double discount_per , string discount_number_field , string discount_number){

	if(offer_id_field != OFFER_ID_FIELD)
		return false;
	if(discount_per_field != DISCOUNT_PER_FIELD)
		return false;
	if(discount_number_field != DISCOUNT_NUM_FIELD)
		return false;
	if(offer_id == EMPTY || discount_per == DOUBLE_NO_VALUE || discount_number == EMPTY)
		return false;
	return true;
}

void Input_handler::handle_generate_discount(stringstream& command){
	string offer_id_field , discount_per_field , discount_number_field;
	string offer_id = EMPTY , discount_number = EMPTY;
	double discount_per = DOUBLE_NO_VALUE;

	command >> offer_id_field >> offer_id;
	command >> discount_per_field >> discount_per;
	command >> discount_number_field >> discount_number;

	try{
		if(is_valid_discount_gen_inputs(offer_id_field , offer_id , discount_per_field , discount_per
														, discount_number_field , discount_number) == false)
				throw Bad_request();
		controller -> generate_discount_code(offer_id , discount_per , discount_number);
	}catch(Bad_request e){
		cout << e.what();
	}
}

void Input_handler::handle_charge_wallet(stringstream& command){
	string amount_field;
	double amount = DOUBLE_NO_VALUE;
	command >> amount_field >> amount;
	try{
		if(amount_field != AMOUNT_FIELD || amount == DOUBLE_NO_VALUE)
			throw Bad_request();
		controller -> charge_wallet(amount);
	}catch(Bad_request e){
		cout << e.what();
	}
}

bool Input_handler::is_valid_comment_inputs(string product_id_field , string product_id
											 , string comment_field , string comment){
	if(product_id_field != PRODUCT_ID_FIELD)
		return false;
	if(comment_field != COMMENT_FIELD)
		return false;
	if(product_id == EMPTY || comment == EMPTY)
		return false;
	return true;
}

string Input_handler::get_entered_comment(stringstream& command){
	string comment = EMPTY;
	string temp_word = EMPTY;
	while(command >> temp_word){
		if(temp_word != EMPTY && comment != EMPTY)
			comment += SPACE;
		comment += temp_word;
	}
	return comment;
}

void Input_handler::handle_comment(stringstream& command){
	string product_id_field = EMPTY , product_id = EMPTY;
	string comment_field = EMPTY , cur_comment = EMPTY;

	command >> product_id_field >> product_id >> comment_field;
	cur_comment = get_entered_comment(command);

	try{
		if(is_valid_comment_inputs(product_id_field , product_id , comment_field , cur_comment) == false)
			throw Bad_request();
		controller -> post_comment(product_id , cur_comment);
	}catch(Bad_request e){
		cout << e.what();
	}
}

bool Input_handler::is_valid_add_to_cart_input(string offer_id_field , string offer_id ,
		 		string amount_field , string amount, string discount_code_field , string discount_code){
	if(offer_id_field != OFFER_ID_FIELD)
		return false;
	if(amount_field != AMOUNT_FIELD)
		return false;
	if(offer_id == EMPTY || amount == EMPTY)
		return false;
	if(discount_code_field != EMPTY){
		if(discount_code == EMPTY)
			return false;
	}
	return true;

}

void Input_handler::handle_add_to_cart(stringstream& command){
	string offer_id_field , offer_id , amount_field , amount , discount_code_field , discount_code;
	discount_code = EMPTY;
	offer_id = EMPTY;
	amount = EMPTY;

	command >> offer_id_field >> offer_id >> amount_field >> amount;
	command >> discount_code_field >> discount_code;

	try{
		if(is_valid_add_to_cart_input(offer_id_field , offer_id , amount_field , amount 
														, discount_code_field , discount_code) == false)
			throw Bad_request();
		controller -> add_to_cart(offer_id , amount , discount_code);
	}catch(Bad_request e){
		cout << e.what();
	}
}


void Input_handler::handle_submit_cart(stringstream& command){
	controller -> submit_cart();
}

bool Input_handler::is_valid_get_input_type(string type){
	vector < string > get_input_types = {GET_OFFERS , GET_PRODUCTS , GET_MY_OFFERS , GET_WALLET ,
										 GET_OFFERS_ON_PRODUCT  , GET_PRODUCT_DETAIL , GET_COMMENT ,
										 GET_COMPARE , GET_CART , GET_ORDERS};
	for(int type_number = 0 ; type_number < get_input_types.size() ; type_number++){
		string cur_type = get_input_types[type_number];
		if(cur_type == type)
			return true;
	}
	return false;
}

void Input_handler::handle_get_input(stringstream& command){
	string type , questionare = EMPTY;
	command >> type >> questionare;

	try{
		if(is_valid_get_input_type(type) == false)
			throw Not_found();

		if(type == GET_OFFERS && questionare == QUESTION_SIGN) 
			handle_get_offers(command);

		else if(type == GET_OFFERS && questionare == EMPTY)
			handle_get_all_offers(command);
		
		else if(type == GET_PRODUCTS) 
			handle_get_products(command);
		
		else if(type == GET_MY_OFFERS) 
			handle_get_my_offers(command);

		else if(type == GET_WALLET && questionare == QUESTION_SIGN)
			handle_get_wallet(command);
		
		else if(type == GET_OFFERS_ON_PRODUCT) 
			handle_get_offers_on_product(command);

		else if(type == GET_PRODUCT_DETAIL && questionare == QUESTION_SIGN) 
				handle_get_product_detail(command);
		
		else if(type == GET_COMMENT && questionare == QUESTION_SIGN)
			handle_get_comments(command);
		else if(type == GET_COMPARE && questionare == QUESTION_SIGN)
			handle_get_compare(command);
		
		else if(type == GET_CART) 
			handle_get_cart(command);

		else if(type == GET_ORDERS && questionare == QUESTION_SIGN)
			handle_get_orders(command);
		else
			throw Bad_request();
	}catch(Not_found e){
		cout << e.what();
	}catch(Bad_request e){
		cout << e.what();
	}
	
}

bool Input_handler::is_valid_get_offers_inputs(string order_field , string order , string field 
																				, string sort_field){
	if(order_field != ORDER_FIELD)
		return false;
	if(field != FIELD)
		return false;
	if(order != ASCENDING && order != DESCENDING)
		return false;
	if(sort_field != OFFER_ID && sort_field != OFFER_PRICE)
		return false;
	return true;
}

void Input_handler::handle_get_offers(stringstream& command){
	string order_field , order;
	string field , sort_field;
	command >> order_field >> order >> field >> sort_field;

	try{
		if(is_valid_get_offers_inputs(order_field , order , field , sort_field))
			controller->print_offers_by_order(order , sort_field);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}

void Input_handler::handle_get_all_offers(stringstream& command){
	controller -> print_all_offers();
}


void Input_handler::handle_get_products(stringstream& command){
	controller -> get_products();
}

void Input_handler::handle_get_my_offers(stringstream& command){
	controller -> get_my_offers();
}

void Input_handler::handle_get_wallet(stringstream& command){
	string count_field;
	int count = NO_VALUE;
	command >> count_field >> count;
	try{
		if(count_field == COUNT_FIELD && count != NO_VALUE)
			controller -> get_wallet(count);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}

void Input_handler::handle_get_offers_on_product(stringstream& command){
	string product_id_field , product_id = EMPTY;
	command >> product_id_field >> product_id;
	try{
		if(product_id_field == PRODUCT_ID_FIELD && product_id != EMPTY)
			controller -> get_offers_on_product(product_id);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}

void Input_handler::handle_get_product_detail(stringstream& command){
	string product_id_field , product_id = EMPTY;
	command >> product_id_field >> product_id;
	try{
		if(product_id_field == PRODUCT_ID_FIELD && product_id != EMPTY)
			controller -> get_product_detail(product_id);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}
}

void Input_handler::handle_get_comments(stringstream& command){
	string product_id_field , product_id;
	command >> product_id_field >> product_id;
	try{
		if(product_id_field != PRODUCT_ID_FIELD || product_id == EMPTY)
			throw Bad_request();
		controller -> get_comments(product_id);
	}catch(Bad_request e){
		cout << e.what();
	}
}


bool Input_handler::is_valid_get_compare_inputs(string product_id_1_field , string product_id_1 
													, string product_id_2_field , string product_id_2){
	if(product_id_1_field != PRODUCT_ID_1_FIELD)
		return false;
	if(product_id_2_field != PRODUCT_ID_2_FIELD)
		return false;
	if(product_id_1 == EMPTY || product_id_2 == EMPTY)
		return false;
	return true;
}

void Input_handler::handle_get_compare(stringstream& command){
	string product_id_1_field , product_id_2_field;
	string product_id_1 = EMPTY , product_id_2 = EMPTY;
	command >> product_id_1_field >> product_id_1 >> product_id_2_field >> product_id_2;
	try{
		if(is_valid_get_compare_inputs(product_id_1_field , product_id_1 , product_id_2_field
																 , product_id_2) == false)
			throw Bad_request();
		controller -> compare_products(product_id_1 , product_id_2);
	}catch(Bad_request e){
		cout << e.what();
	}
}

void Input_handler::handle_get_cart(stringstream& command){
	controller -> get_cart();
}

void Input_handler::handle_get_orders(stringstream& command){
	string count_field;
	int count = NO_VALUE;
	command >> count_field >> count;
	try{
		if(count_field == COUNT_FIELD && count != NO_VALUE)
			controller -> get_orders(count);
		else
			throw Bad_request();
	}catch(Bad_request e){
		cout << e.what();
	}	
}







