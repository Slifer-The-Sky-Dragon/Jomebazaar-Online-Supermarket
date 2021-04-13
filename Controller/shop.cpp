#include "shop.hpp"
#include "not_found.hpp"
#include "bad_req.hpp"
#include <fstream>
#include <sstream>

#define NO_OFFER NULL
#define NO_PRODUCT NULL

#define DONE "OK\n"
#define NOT_FOUND 0
#define EMPTY ""

#define MOBILE "mobile"
#define CAR "car"
#define TV "tv"

#define NAME_FIELD "productName"
#define PRODUCT_ID_FIELD "productId"
#define PRODUCT_NAME_FIELD "productName"
#define OFFER_UNIT_PRICE_FIELD "offerUnitPrice"
#define OFFER_AMOUNT_FIELD "offerAmount"
#define OFFER_ID_FIELD "offerId"

#define OFFER_ID "offerId"
#define OFFER_PRICE "offerPrice"
#define ASCENDING "ASCEND"
#define DESCENDING "DESCEND"

#define SPACER " | "
#define SPACE " "
#define NEW_LINE "\n"

using namespace std;

typedef vector < string > Information;

Shop::Shop(){
	new_product_id = 1;
	new_offer_id = 1;
}

void Shop::import_products(string file_data , string type){
	stringstream file(file_data);
	import_products_from_file(file , type);
	cout << "OK" << endl;
}

void Shop::create_offer(User* seller , string product_id , string unit_price , string amount){
	if(is_seller_offerd_on_this_product_before(seller , product_id) == true)
		throw Bad_request();
	add_new_offer(seller , product_id , unit_price , amount);
}

void Shop::change_offer(User* seller , string offer_id , string unit_price , string amount){
	try{
		if(is_offer_id_exist(offer_id) == false)
			throw Bad_request();
		Offer* cur_offer = find_offer(offer_id);
		if(cur_offer -> is_seller_equals(seller) == false)
			throw Bad_request();
		cur_offer -> replace_values(unit_price , amount);
		cout << DONE;
	}catch(Bad_request e){
		cout << e.what();
	}
}	


string Shop::get_products(){
	string res = EMPTY;

	for(int product_number = 0 ; product_number < products.size() ; product_number++){
		res += products[product_number] -> get_id_and_name();
	}	
	return res;
}


void Shop::print_offers_by_order(string order , string sort_field){
	sort_offers(order , sort_field);

	cout << PRODUCT_ID_FIELD << SPACER << OFFER_ID_FIELD << SPACER;
	cout << OFFER_UNIT_PRICE_FIELD << SPACER << OFFER_AMOUNT_FIELD << endl;

	for(int offer_number = 0 ; offer_number < offers.size() ; offer_number++){
		Offer* cur_offer = offers[offer_number];
		cur_offer -> show_info();
	}
}

void Shop::print_all_offers(){
	cout << PRODUCT_ID_FIELD << SPACER << PRODUCT_NAME_FIELD << SPACER;
	cout << OFFER_ID_FIELD << SPACER << OFFER_UNIT_PRICE_FIELD << SPACER << OFFER_AMOUNT_FIELD << endl;

	for(int offer_number = 0 ; offer_number < offers.size() ; offer_number++){
		Offer* cur_offer = offers[offer_number];
		for(int cur_product_id = 1 ; cur_product_id < new_product_id ; cur_product_id++){
			if(cur_offer -> is_product_id_equals(cur_product_id)){
				Product* cur_product = find_product(cur_product_id);
				cur_product -> print_id_and_name_oneline();
				cur_offer -> show_info_without_product_id();
			}	
		}
	}	
}


string Shop::print_user_offers(User* seller){
	sort_offers_by_id();

	string res = EMPTY;

	for(int offer_number = 0 ; offer_number < offers.size() ; offer_number++){
		Offer* cur_offer = offers[offer_number];
		if(cur_offer -> is_seller_equals(seller))
			res += cur_offer -> show_info();
	}
	return res;
}

string Shop::get_offers_on_product(string product_id){
	sort_offers_by_id();
	return print_offers_on_product(product_id);
}

string Shop::print_offers_on_product(string product_id){
	string res = EMPTY , temp = EMPTY;

	stringstream ss;
	ss << OFFER_ID_FIELD << SPACE << OFFER_UNIT_PRICE_FIELD << SPACE << OFFER_AMOUNT_FIELD << SPACE;

	while(ss >> temp){
		res += temp + NEW_LINE;
	}

	for(int offer_number = 0 ; offer_number < offers.size() ; offer_number++){
		Offer* cur_offer = offers[offer_number];
		if(cur_offer -> is_product_id_equals(product_id)){
			res += cur_offer -> show_info_without_product_id();
		}	
	}

	return res;
}

string Shop::print_product_deatil(string product_id){
	Product* cur_product = find_product(product_id);
	return cur_product -> print_details();
}

void Shop::add_comment_on_product(User* buyer , string product_id , string cur_comment){
	try{
		if(is_product_id_exist(product_id) == false)
			throw Not_found();
		Product* cur_product = find_product(product_id);
		cur_product -> add_comment(buyer , cur_comment);
		cout << DONE;
	}catch(Not_found e){
		cout << e.what();
	}
}

void Shop::print_comments(string product_id){
	try{
		if(is_product_id_exist(product_id) == false)
			throw Not_found();
		Product* cur_product = find_product(product_id);
		cur_product -> show_comments();
	}catch(Not_found e){
		cout << e.what();
	}
}

Product* Shop::find_product(string product_id){
	for(int product_number = 0 ; product_number < products.size() ; product_number++){
		Product* cur_product = products[product_number];
		if(cur_product -> is_id_equals(product_id))
			return cur_product;
	}
	return NO_PRODUCT;
}

Product* Shop::find_product(int product_id){
	for(int product_number = 0 ; product_number < products.size() ; product_number++){
		Product* cur_product = products[product_number];
		if(cur_product -> is_id_equals(product_id))
			return cur_product;
	}
	return NO_PRODUCT;
}


Offer* Shop::find_offer(string offer_id){
	for(int offer_number = 0 ; offer_number < offers.size() ; offer_number++){
		Offer* cur_offer = offers[offer_number];
		if(cur_offer -> is_id_equals(offer_id))
			return cur_offer;
	}
	return NO_OFFER;
}


void Shop::sort_offers(string order , string sort_field){
	if(sort_field == OFFER_ID){
		sort_offers_by_id();
		if(order == DESCENDING)
			reverse(offers.begin() , offers.end());
	}
	else{
		if(order == ASCENDING)
			sort_offers_by_price_ascending();
		else
			sort_offers_by_price_descending();
	}	
}

void Shop::sort_offers_by_id(){
	for(int first_offer_number = 0 ; first_offer_number < offers.size() ; first_offer_number++){
		for(int sec_offer_number = first_offer_number ; sec_offer_number < offers.size() ; sec_offer_number++){
			Offer* first_offer = offers[first_offer_number];
			Offer* second_offer = offers[sec_offer_number];
			if(first_offer -> is_older_than(second_offer)){
				swap(offers[first_offer_number] , offers[sec_offer_number]);
			}
		}
	}
}

void Shop::sort_offers_by_price_ascending(){
	for(int first_offer_number = 0 ; first_offer_number < offers.size() ; first_offer_number++){
		for(int sec_offer_number = first_offer_number ; sec_offer_number < offers.size() ; sec_offer_number++){
			Offer* first_offer = offers[first_offer_number];
			Offer* second_offer = offers[sec_offer_number];
			if(first_offer -> is_more_expensive_than(second_offer)){
				swap(offers[first_offer_number] , offers[sec_offer_number]);
			}
		}
	}
}

void Shop::sort_offers_by_price_descending(){
	for(int first_offer_number = 0 ; first_offer_number < offers.size() ; first_offer_number++){
		for(int sec_offer_number = first_offer_number ; sec_offer_number < offers.size() ; sec_offer_number++){
			Offer* first_offer = offers[first_offer_number];
			Offer* second_offer = offers[sec_offer_number];
			if(first_offer -> is_cheaper_than(second_offer)){
				swap(offers[first_offer_number] , offers[sec_offer_number]);
			}
		}
	}
}

bool Shop::is_offer_id_exist(string offer_id){
	int cur_id = stoi(offer_id);
	if(cur_id < new_offer_id)
		return true;
	return false;
}

bool Shop::is_product_id_exist(string product_id){
	int cur_id = stoi(product_id);
	if(cur_id < new_product_id)
		return true;
	return false;
}

bool Shop::is_seller_offerd_on_this_product_before(User* seller , string product_id){
	for(int offer_number = 0 ; offer_number < offers.size() ; offer_number++){
		Offer* cur_offer = offers[offer_number];
		if(cur_offer -> is_seller_equals(seller) && cur_offer -> is_product_id_equals(product_id))
			return true;
	}
	return false;
}

void Shop::add_new_offer(User* seller , string product_id , string unit_price , string amount){
	stringstream ss(product_id + " " + unit_price + " " + amount);
	int offer_product_id , offer_amount;
	double offer_price;
	ss >> offer_product_id >> offer_price >> offer_amount;

	int offer_id = new_offer_id;
	new_offer_id++;

	Offer* new_offer = new Offer(seller , offer_product_id , offer_id , offer_price , offer_amount);
	offers.push_back(new_offer);
}

Information Shop::extract_info_from_csv(string csv_string){
	Information info;
	string cur_info;
	istringstream ss(csv_string);
	while(getline(ss , cur_info , ',')){
		info.push_back(cur_info);
	}
	return info;
}

Information Shop::get_label_from_file(stringstream& file){
	Information labels;
	string line , cur_label;
	getline(file , line);

	labels = extract_info_from_csv(line);

	return labels;
}

void Shop::add_new_product(int id , Information product_info , Information labels , string type){
	if(type == MOBILE){
		Mobile* new_product = new Mobile(id , product_info , labels);
		products.push_back(new_product);
	}
	else if(type == CAR){
		Car* new_product = new Car(id , product_info , labels);
		products.push_back(new_product);		
	}
	else if(type == TV){
		Tv* new_product = new Tv(id , product_info , labels);
		products.push_back(new_product);				
	}
}

void Shop::add_product_from_file(stringstream& file , Information labels , string type){
	string line , cur_product;
	while(getline(file , line)){
		Information product_info = extract_info_from_csv(line);

		add_new_product(new_product_id , product_info , labels , type);
		new_product_id++;
	}

}

void Shop::import_products_from_file(stringstream& file , string type){
	Information labels;
	labels = get_label_from_file(file);
	add_product_from_file(file , labels , type);
}

void Shop::compare_products(string product_id_1 , string product_id_2){
	try{
		if(is_product_id_exist(product_id_1) == false || is_product_id_exist(product_id_2) == false)
			throw new Not_found();
		Product* first_product = find_product(product_id_1);
		Product* second_product = find_product(product_id_2);

		first_product -> compare_info_with(second_product);
	}catch(exception* e){
		cout << e->what();
	}
}

void Shop::add_discount_code(User* seller , string offer_id , double discount_per 	
															, vector < string > discount_codes){
	try{
		if(is_offer_id_exist(offer_id) == false)
			throw new Not_found();
		Offer* cur_offer = find_offer(offer_id);
		if(cur_offer -> is_seller_equals(seller) == false)
			throw new Bad_request();
		cur_offer -> add_discount_codes(discount_codes , discount_per);
	}catch(exception* e){
		cout << e -> what();
	}
}

void Shop::add_to_buyer_cart(Buyer* buyer , string offer_id , string amount , string discount_code){
	try{
		if(is_offer_id_exist(offer_id) == false)
			throw new Not_found();

		Offer* cur_offer = find_offer(offer_id);
		Product* cur_product = find_product(cur_offer -> get_product_id());

		if(cur_offer -> is_valid_amount(amount) == false)
			throw new Bad_request();
		if(discount_code != EMPTY && cur_offer -> is_valid_code(discount_code) == false)
			throw new Bad_request();

		double price = cur_offer -> calculate_price(amount , discount_code);
		cur_offer -> decrease_amount(amount);
		Order* new_order = new Order(cur_product , cur_offer , price , amount);
		buyer -> add_to_cart(new_order);
		cout << DONE;
	}catch(exception* e){
		cout << e -> what();
	}
}








