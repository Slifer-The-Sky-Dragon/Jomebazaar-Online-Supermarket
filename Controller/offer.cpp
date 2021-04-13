#include "offer.hpp"
#include <sstream>

#define EQUAL 0
#define GREATER 1
#define LOWER -1

#define SPACE " "
#define EMPTY ""

#define PERCANT second
#define CODE first

#define SPACER " | "
#define NEW_LINE "\n"

using namespace std;

void Offer::replace_values(string unit_price , string _amount){
	stringstream ss(unit_price + SPACE + _amount);
	ss >> price;
	ss >> amount;
}


bool Offer::is_seller_equals(User* cur_seller){
	if(seller == cur_seller)
		return true;
	return false;
}

bool Offer::is_product_id_equals(string cur_product_id){
	if(product_id == stoi(cur_product_id))
		return true;
	return false;
}

bool Offer::is_product_id_equals(int cur_product_id){
	if(product_id == cur_product_id)
		return true;
	return false;
}

bool Offer::is_id_equals(string cur_id){
	if(id == stoi(cur_id))
		return true;
	return false;	
}

bool Offer::is_id_equals(int cur_id){
	if(id == cur_id)
		return true;
	return false;	
}



bool Offer::is_older_than(Offer* other_offer){
	return !(other_offer -> is_older_than(id));
}

bool Offer::is_older_than(int other_offer_id){
	return id > other_offer_id;
}

bool Offer::is_more_expensive_than(Offer* other_offer){
	int compare_res = other_offer -> compare_with(price);
	if(compare_res == GREATER){
		return false;
	}
	else if(compare_res == LOWER){
		return true;
	}
	else{
		return !(other_offer -> is_older_than(id));
	}
}

bool Offer::is_cheaper_than(Offer* other_offer){
	int compare_res = other_offer -> compare_with(price);
	if(compare_res == GREATER){
		return true;
	}
	else if(compare_res == LOWER){
		return false;
	}
	else{
		return !(other_offer -> is_older_than(id));
	}
}

int Offer::compare_with(double other_offer_price){
	if(price > other_offer_price)
		return GREATER;
	else if(price == other_offer_price)
		return EQUAL;
	return LOWER;
}

string Offer::show_info(){
	string res = EMPTY , temp = EMPTY;
	stringstream ss;
	ss << product_id << SPACE << id << SPACE << price << SPACE << amount;

	while(ss >> temp)
		res += temp + NEW_LINE;
	return res;
}

string Offer::show_info_without_product_id(){
	string res = EMPTY , temp = EMPTY;
	stringstream ss;
	ss << id << SPACE << price << SPACE << amount;

	while(ss >> temp)
		res += temp + NEW_LINE;
	return res;	
}

string Offer::show_complete_id_info(){
	string res = EMPTY , temp = EMPTY;
	stringstream ss;

	int seller_id = seller -> get_id();
	ss << id << SPACE << seller_id << SPACE;

	while(ss >> temp)
		res += temp + NEW_LINE;
	return res;
}


void Offer::add_discount_codes(vector < string > cur_discount_codes , double perc){
	for(int code_number = 0 ; code_number < cur_discount_codes.size() ; code_number++){
		string cur_code = cur_discount_codes[code_number];
		cout << cur_code << endl;
		discount_codes.push_back(make_pair(cur_code , perc));
	}
}

bool Offer::is_valid_amount(string cur_amount){
	if(stoi(cur_amount) > amount)
		return false;
	return true;
}

bool Offer::is_valid_code(string discount_code){
	for(int code_number = 0 ; code_number < discount_codes.size() ; code_number++){
		Discount cur_code = discount_codes[code_number];
		if(cur_code.CODE == discount_code)
			return true;
	}	
	return false;
}

double Offer::calculate_price(string cur_amount , string discount_code){
	int temp_amount = stoi(cur_amount);
	double code_per = 0.0;
	for(int code_number = 0 ; code_number < discount_codes.size() ; code_number++){
		Discount cur_code = discount_codes[code_number];
		if(cur_code.CODE == discount_code){
			code_per = cur_code.PERCANT;
			discount_codes.erase(discount_codes.begin() + code_number);
			break;
		}
	}

	code_per = code_per / 100.0;
	return double(temp_amount) * (price - (price * code_per));
}

void Offer::decrease_amount(string cur_amount){
	int temp_amount = stoi(cur_amount);
	amount -= temp_amount;
}

void Offer::increase_amount(string cur_amount){
	int temp_amount = stoi(cur_amount);
	amount += temp_amount;	
}


void Offer::charge_seller(double price){
	seller -> charge_wallet(price);
}












