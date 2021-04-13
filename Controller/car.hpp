#ifndef _CAR_HPP
#define _CAR_HPP

#include "product.hpp"

class Car : public Product {
public:
	Car(int _id , Information _info , Information _info_label);
	bool compare_type_with(Product* other_product);
	bool compare_type_with(string other_product_type);

	void compare_info_with(Product* other_product);
	void compare_info_with(Information other_product_info);

private:

};

#endif