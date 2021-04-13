#include "controller.hpp"
#include "bad_req.hpp"
#include "permision_denied.hpp"
#include <ctime>

#define NO_USER NULL
#define EMPTY ""
#define DONE "OK\n"

#define TOKENS "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

#define DISCOUNT_CODE_LEN 8
#define ADMIN_EMAIL "admin@gmail.com"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASS "admin"
#define ADMIN_ID 0

#define SELLER "seller"
#define BUYER "buyer"

#define ASCENDING "ASCEND"
#define DESCENDING "DESCEND"

#define NO_VALUE 0
#define HASH_NUM 31
#define NOT_ACTIVE -1



const long long int MOD = 1e9 + 7;
const long long int BASE = 427;

typedef long long int Hashcode;

Controller::Controller(Shop* _shop){
	shop = _shop;
	
	Hashcode admin_pass_hash = compute_hash(ADMIN_PASS);
	admin = new User(ADMIN_EMAIL , ADMIN_USERNAME , admin_pass_hash , ADMIN_ID);
	cur_user = NO_USER;
	new_user_id = 1;
	all_users.push_back(admin);
};


void Controller::import_products(string file_data , string type_of_product){
	shop -> import_products(file_data , type_of_product);
}


SID Controller::signup_user(string email , string user_name , string password , string type){
	if(is_username_exist(user_name) == true)
		throw Bad_request();

	if(type == SELLER)
		add_a_seller(email , user_name , password);
	else
		add_a_buyer(email , user_name , password);
	return active_users.back();
}

SID Controller::login_user(string user_name , string password){
	if(is_account_info_valid(user_name , password)  == false)
		throw Bad_request();

	SID logined_user_sid = find_user_sid(user_name);
	active_users.push_back(logined_user_sid);
	return logined_user_sid;
}

void Controller::logout_user(SID user_sid){
	if(is_user_buyer(user_sid) == true){
		Buyer* cur_buyer = find_buyer(all_users[user_sid]);
		cur_buyer -> put_back_cart();
	}
	unactive_user(user_sid);
}

string Controller::get_products(){
	return shop -> get_products();
}

void Controller::create_offer(SID user_sid , string product_id , string unit_price , string amount){
	User* cur_seller = all_users[user_sid];
	shop -> create_offer(cur_seller , product_id , unit_price , amount);
}

void Controller::change_offer(string offer_id , string unit_price , string amount){
	try{
		if(is_cur_user_a_seller() == false)
			throw Permision_denied();
		shop -> change_offer(cur_user , offer_id , unit_price , amount);
	}catch(Permision_denied e){
		cout << e.what();
	}
}


void Controller::print_offers_by_order(string order , string cur_field){
	try{
		if(cur_user != admin)
			throw Permision_denied();
		shop -> print_offers_by_order(order , cur_field);
	}catch(Permision_denied e){
		cout << e.what();
	}
}

void Controller::add_to_cart(SID user_sid , string offer_id , string amount , string discount_code){
	Buyer* cur_buyer = find_buyer(all_users[user_sid]);
	shop -> add_to_buyer_cart(cur_buyer , offer_id , amount , discount_code);
}

void Controller::generate_discount_code(string offer_id , double discount_per , string discount_number){
	try{
		if(is_cur_user_a_seller() == false)
			throw Permision_denied();
		int cnt_of_discount_codes = stoi(discount_number);
		vector < string > discount_code = gen_random_code(cnt_of_discount_codes);
		shop -> add_discount_code(cur_user , offer_id , discount_per , discount_code);
	}catch(Permision_denied e){
		cout << e.what();
	}
}

void Controller::charge_wallet(SID user_sid , double amount){
	User* cur_user = all_users[user_sid];
	cur_user -> charge_wallet(amount);
}

void Controller::post_comment(string product_id , string cur_comment){
	try{
		if(is_cur_user_a_buyer() == false)
			throw Permision_denied();
		shop -> add_comment_on_product(cur_user , product_id , cur_comment);
	}catch(Permision_denied e){
		cout << e.what();
	}
}


string Controller::get_my_offers(SID user_sid){
	User* cur_seller = all_users[user_sid];
	return shop -> print_user_offers(cur_seller);
}

double Controller::get_wallet(SID user_sid){
	User* cur_user = all_users[user_sid];	
	return cur_user -> get_balance();
}

string Controller::get_offers_on_product(string product_id){
	return shop -> get_offers_on_product(product_id);
}

string Controller::get_product_detail(string product_id){
	return shop -> print_product_deatil(product_id);
}

void Controller::get_comments(string product_id){
	try{
		if(is_cur_user_a_buyer() == false)
			throw Permision_denied();
		shop -> print_comments(product_id);
	}catch(Permision_denied e){
		cout << e.what();
	}
}

SID Controller::find_user_sid(string user_name){
	for(int user_number = 0 ; user_number < all_users.size() ; user_number++){
		User* cur_user = all_users[user_number];
		if(cur_user -> is_username_equal(user_name) == true)
			return user_number;
	}	
	return NOT_ACTIVE;
}


SID Controller::find_user_sid(User* user){
	for(int user_number = 0 ; user_number < all_users.size() ; user_number++){
		User* cur_user = all_users[user_number];
		if(cur_user == user)
			return user_number;
	}
	return NOT_ACTIVE;
}


Buyer* Controller::find_buyer(User* buyer){
	for(int buyer_name = 0 ; buyer_name < buyers.size() ; buyer_name++){
		User* cur_user = buyers[buyer_name];
		if(cur_user == buyer)
			return buyers[buyer_name];
	}	
	return NO_USER;
}

Hashcode Controller::compute_hash(string password){
	Hashcode password_hash = NO_VALUE;

	for(int char_number = 0 ; char_number < password.size() ; char_number++){
		char cur_char = password[char_number];
		password_hash = ((BASE * password_hash) + cur_char) % MOD;
	}

	return password_hash;
}

bool Controller::is_account_info_valid(string user_name , string password){
	for(int user_number = 0 ; user_number < all_users.size() ; user_number++){
		User* cur_user = all_users[user_number];
		Hashcode hash_password = compute_hash(password);
		if(cur_user -> is_username_and_password_equal(user_name , hash_password) == true)
			return true;
	}
	return false;	
}

bool Controller::is_username_exist(string user_name){
	for(int user_number = 0 ; user_number < all_users.size() ; user_number++){
		User* cur_user = all_users[user_number];
		if(cur_user -> is_username_equal(user_name) == true)
			return true;
	}
	return false;
}

bool Controller::is_active_user(string user_name){
	SID user_sid = find_user_sid(user_name);
	for(int user_number = 0 ; user_number < active_users.size() ; user_number++){
		SID cur_user_sid = active_users[user_number];
		if(cur_user_sid == user_sid)
			return true;
	}
	return false;
}

bool Controller::is_active_user(SID user_sid){
	for(int user_number = 0 ; user_number < active_users.size() ; user_number++){
		SID cur_user_sid = active_users[user_number];
		if(cur_user_sid == user_sid)
			return true;
	}
	return false;
}


void Controller::unactive_user(SID user_sid){
	for(int user_number = 0 ; user_number < active_users.size() ; user_number++){
		SID cur_user_sid = active_users[user_number];
		if(cur_user_sid == user_sid){
			active_users.erase(active_users.begin() + user_number);
			break;
		}
	}
}

string Controller::get_username(SID user_sid){
	User* cur_user = all_users[user_sid];
	return cur_user -> get_username();
}



void Controller::add_a_seller(string email , string user_name , string password){
	Hashcode hash_password = compute_hash(password);
	Seller* new_seller = new Seller(email , user_name , hash_password , new_user_id);

	sellers.push_back(new_seller);
	all_users.push_back(new_seller);
	active_users.push_back(new_user_id);

	new_user_id++;
}

void Controller::add_a_buyer(string email , string user_name , string password){
	Hashcode hash_password = compute_hash(password);
	Buyer* new_buyer = new Buyer(email , user_name , hash_password , new_user_id);

	buyers.push_back(new_buyer);
	all_users.push_back(new_buyer);
	active_users.push_back(new_user_id);

	new_user_id++;
}

void Controller::compare_products(string product_id_1 , string product_id_2){
	try{
		if(is_cur_user_a_buyer() == false)
			throw Permision_denied();
		shop -> compare_products(product_id_1 , product_id_2);
	}catch(Permision_denied e){
		cout << e.what();
	}
}

bool Controller::is_user_admin(SID user_sid){
	if(user_sid == ADMIN_ID)
		return true;
	return false;
}

bool Controller::is_user_buyer(SID user_sid){
	for(int buyer_number = 0 ; buyer_number < buyers.size() ; buyer_number++){
		User* cur_buyer = buyers[buyer_number];
		SID cur_buyer_sid = find_user_sid(cur_buyer);
		if(user_sid == cur_buyer_sid){
			return true;
		}
	}
	return false;	
}

bool Controller::is_user_seller(SID user_sid){
	for(int seller_number = 0 ; seller_number < sellers.size() ; seller_number++){
		User* cur_seller = sellers[seller_number];
		SID cur_seller_sid = find_user_sid(cur_seller);
		if(user_sid == cur_seller_sid){
			return true;
		}
	}
	return false;	
}


bool Controller::is_cur_user_a_buyer(){
	for(int buyer_number = 0 ; buyer_number < buyers.size() ; buyer_number++){
		User* cur_buyer = buyers[buyer_number];
		if(cur_buyer == cur_user){
			return true;
		}
	}
	return false;
}

bool Controller::is_cur_user_a_seller(){
	for(int seller_number = 0 ; seller_number < sellers.size() ; seller_number++){
		User* cur_seller = sellers[seller_number];
		if(cur_seller == cur_user){
			return true;
		}
	}
	return false;
}

vector < string > Controller::gen_random_code(int numbers_of_discount_codes) {
    string tokens = TOKENS;
    
    vector < string > dis_codes;
    srand(time(0));
    int token_size = tokens.size();

    for(int cnt = 0 ; cnt < numbers_of_discount_codes ; cnt++){
       	string discount_code = EMPTY;
	    for(int len = 0 ; len < DISCOUNT_CODE_LEN ; len++){
	    	discount_code += tokens[rand() % token_size];
	    }
	    dis_codes.push_back(discount_code);
	}

    return dis_codes;
}

string Controller::get_cart(SID user_sid){
	User* cur_user = all_users[user_sid];
	Buyer* cur_buyer = find_buyer(cur_user);
	return cur_buyer -> print_cart();
}

string Controller::submit_cart(SID user_sid){
	User* cur_user = all_users[user_sid];
	Buyer* cur_buyer = find_buyer(cur_user);
	return cur_buyer -> submit_cart();
}

void Controller::get_orders(int count){
	try{
		if(is_cur_user_a_buyer() == false)
			throw Permision_denied();
		Buyer* cur_buyer = find_buyer(cur_user);
		cur_buyer -> print_orders(count);
	}catch(Permision_denied e){
		cout << e.what();
	}
}

void Controller::print_all_offers(){
	try{
		if(is_cur_user_a_buyer() == false)
			throw Permision_denied();
		shop -> print_all_offers();
	}catch(Permision_denied e){
		cout << e.what();
	}
}




