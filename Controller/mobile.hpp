#ifndef _MOBILE_HPP
#define _MOBILE_HPP

#include "product.hpp"
#include <iostream>
#include <vector>

using namespace std;

typedef vector < string > Information;

class Mobile : public Product {
public:
	Mobile(int _id , Information _info , Information _info_label);
	bool compare_type_with(Product* other_product);
	bool compare_type_with(string other_product_type);

	void compare_info_with(Product* other_product);
	void compare_info_with(Information other_product_info);

private:

};

#endif