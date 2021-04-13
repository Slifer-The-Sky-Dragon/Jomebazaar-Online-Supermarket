#include "input_handler.hpp"
#include "shop.hpp"
#include "user.hpp"
#include "controller.hpp"
#include <iostream>
#include <string>

using namespace std;

int main(){
	Shop* my_shop = new Shop();
	Controller* shop_controller = new Controller(my_shop);
	Input_handler* shop_input_handler = new Input_handler(shop_controller);
	
	string input;
	while(getline(cin , input)){
	 	shop_input_handler -> handle_input(input);
	}
}