#ifndef _BUYER_HPP
#define _BUYER_HPP

#include "user.hpp"
#include "offer.hpp"
#include "order.hpp"
#include <vector>

using namespace std;

typedef int price;
typedef vector < Order* > Purchase_info;
typedef vector < Purchase_info > Purchases_list;

typedef long long int Hashcode;

class Buyer : public User {
public:
	Buyer(string _email , string _username , Hashcode _pass , int _id) 
													: User(_email , _username , _pass , _id) {};

	void add_to_cart(Order* new_order);
	string print_cart();
	string submit_cart();
	double calculate_cost_of_cart();
	void send_money_to_sellers();
	void delete_cart();
	void print_orders(int count);
	void put_back_cart();

private:
	Purchase_info cart;
	Purchases_list all_purchases;
};

#endif