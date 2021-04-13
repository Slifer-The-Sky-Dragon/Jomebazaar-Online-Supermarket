#include "order.hpp"
#include <sstream>

#define SPACER " | "
#define SPACE " "
#define EMPTY ""
#define NEW_LINE "\n"

string Order::show_info(){
	string res = EMPTY;
	res += product -> get_id_and_name();
	res += offer -> show_complete_id_info();

	string temp = EMPTY;
	stringstream ss;

	ss << price << SPACE << amount << SPACE;
	while(ss >> temp)
		res += temp + NEW_LINE;
	return res;
}


void Order::charge_seller(){
	offer -> charge_seller(price);
}

void Order::put_back_order(){
	offer -> increase_amount(amount);
}
