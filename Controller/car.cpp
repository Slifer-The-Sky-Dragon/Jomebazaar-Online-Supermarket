#include "car.hpp"
#include "bad_req.hpp"
#include <iostream>

#define CAR "car"
#define SAME true
#define NOT_SAME false;
#define NAME_INDEX 0

Car::Car(int _id , Information _info , Information _info_label)
													: Product(_id , _info , _info_label) {
	type = CAR;
};

bool Car::compare_type_with(Product* other_product){
	return other_product -> compare_type_with(type);
}

bool Car::compare_type_with(string other_product_type){
	if(type == other_product_type)
		return SAME;
	return NOT_SAME;
}

void Car::compare_info_with(Product* other_product){
	if(compare_type_with(other_product) == SAME)
		other_product -> compare_info_with(info);
	else
		throw Bad_request();
}
void Car::compare_info_with(Information other_product_info){
	for(int info_number = 0 ; info_number < info_label.size() ; info_number++){
		if(info_number != NAME_INDEX)
			cout << info_label[info_number] << ": ";
		cout << other_product_info[info_number] << " | ";
		cout << info[info_number] << endl;
	}
}

