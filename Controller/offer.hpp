#ifndef _OFFER_HPP
#define _OFFER_HPP

#include "product.hpp"
#include "user.hpp"
#include "seller.hpp"
#include <vector>

typedef pair < string , double > Discount;

class Offer {
public:
	Offer(User* _seller , int _product_id , int _id , double _price , int _amount) 
					: seller(_seller) , product_id(_product_id) , id(_id) , price(_price) , amount(_amount) {};

	bool is_seller_equals(User* cur_seller);
	bool is_product_id_equals(string cur_product_id);
	bool is_product_id_equals(int cur_product_id);

	bool is_id_equals(string cur_id);
	bool is_id_equals(int cur_id);


	bool is_older_than(Offer* other_offer);
	bool is_more_expensive_than(Offer* other_offer);
	bool is_cheaper_than(Offer* other_offer);

	void replace_values(string unit_price , string _amount);

	string show_info();
	string show_info_without_product_id();
	string show_complete_id_info();
	void add_discount_codes(vector < string > cur_discount_codes);

	void add_discount_codes(vector < string > cur_discount_codes , double perc);

	double calculate_price(string cur_amount , string discount_code);
	bool is_valid_amount(string cur_amount);
	bool is_valid_code(string discount_code);

	void decrease_amount(string amount);
	void increase_amount(string amount);

	int get_product_id() { return product_id; };

	void charge_seller(double price);

private:
	User* seller;
	int product_id;
	int id;
	double price;
	int amount;

	vector < Discount > discount_codes;
	bool is_older_than(int other_offer_id);
	int compare_with(double other_offer_price);

};

#endif