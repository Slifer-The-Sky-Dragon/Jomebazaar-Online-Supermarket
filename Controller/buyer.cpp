#include "buyer.hpp"
#include "bad_req.hpp"
#include "not_found.hpp"

#define DONE "OK\n"
#define NOT_DONE "BAD\n"

#define OK "1"
#define BAD "0"

#define EMPTYCART 0
#define EMPTY "Empty"
#define EMPTY_STR ""
#define NO_PURCHASE 0

#define PRODUCT_ID_FIELD "productId"
#define PRODUCT_NAME_FIELD "productName" 
#define OFFER_ID_FIELD "offerId"
#define SELLER_ID_FIELD "sellerId"
#define PRICE_FIELD "totalPriceConsideringDiscount"
#define AMOUNT_FIELD "amount"
#define SOLD_PRICE_FIELD "soldPrice"
#define SPACER " | "
#define ORDER_SPLIT "****"
#define NEW_LINE "\n"

typedef long long int Hashcode;

void Buyer::add_to_cart(Order* new_order){
	cart.push_back(new_order);
}

string Buyer::print_cart(){
	string res = EMPTY_STR;

	if(cart.size() != EMPTYCART){
		for(int order_number = cart.size() - 1 ; order_number >= 0 ; order_number--){
			Order* cur_order = cart[order_number];
			res += cur_order -> show_info();
		}
	}

	return res;
}

double Buyer::calculate_cost_of_cart(){
	double cost = 0.0;
	for(int order_number = cart.size() - 1 ; order_number >= 0 ; order_number--){
		Order* cur_order = cart[order_number];
		double cur_order_cost = cur_order -> get_price();
		cost += cur_order_cost;
	}
	return cost;
}

void Buyer::send_money_to_sellers(){
	for(int order_number = cart.size() - 1 ; order_number >= 0 ; order_number--){
		Order* cur_order = cart[order_number];
		cur_order -> charge_seller();
	}
}

void Buyer::delete_cart(){
	cart.clear();
}

string Buyer::submit_cart(){
	double cart_cost = calculate_cost_of_cart();
	if(balance < cart_cost)
		return BAD;
	balance -= cart_cost;
	turnovers.push_back(balance);
	send_money_to_sellers();
	
	all_purchases.push_back(cart);
	delete_cart();
	return OK;
}

void Buyer::print_orders(int count){
	try{
		if(all_purchases.size() == NO_PURCHASE)
			throw Not_found();

		cout << PRODUCT_ID_FIELD << SPACER << PRODUCT_NAME_FIELD << SPACER;
		cout << OFFER_ID_FIELD << SPACER << SELLER_ID_FIELD << SPACER;
		cout << SOLD_PRICE_FIELD << SPACER << AMOUNT_FIELD << endl;

		if(count > all_purchases.size())
			count = all_purchases.size();
		for(int purchase_number = 0 ; purchase_number < count ; purchase_number++){
			int purchase_index = all_purchases.size() - purchase_number - 1;

			Purchase_info cur_purchase = all_purchases[purchase_index];

			for(int order_number = cur_purchase.size() - 1 ; order_number >= 0 ; order_number--){
				Order* cur_order = cur_purchase[order_number];
				cur_order -> show_info();
			}

			if(purchase_number != count - 1)
				cout << ORDER_SPLIT << endl;
		}
	}catch(Not_found e){
		cout << e.what();
	}
}

void Buyer::put_back_cart(){
	for(int order_number = cart.size() - 1 ; order_number >= 0 ; order_number--){
		Order* cur_order = cart[order_number];
		cur_order -> put_back_order();
		free(cur_order);
	}	
	cart.clear();
}





