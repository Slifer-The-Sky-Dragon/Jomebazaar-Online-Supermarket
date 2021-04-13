#ifndef _SELLER_HPP
#define _SELLER_HPP

#include "user.hpp"
#include "offer.hpp"
#include <vector>

using namespace std;

typedef long long int Hashcode;

class Seller : public User {
public:
	Seller(string _email , string _username , Hashcode _pass , int _id)
													: User(_email , _username , _pass , _id) {};
private:
	
};

#endif