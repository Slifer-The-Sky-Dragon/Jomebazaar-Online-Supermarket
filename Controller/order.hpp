#ifndef _ORDER_HPP
#define _ORDER_HPP

#include "product.hpp"
#include "offer.hpp"

class Order{
public:
	Order(Product* _product , Offer* _offer , double _price , string _amount) : 
										product(_product) , offer(_offer) , price(_price) , amount(_amount){};
	string show_info();
	double get_price() { return price; };
	void charge_seller();
	void put_back_order();
private:
	Product* product;
	Offer* offer;
	double price;
	string amount;
};

#endif