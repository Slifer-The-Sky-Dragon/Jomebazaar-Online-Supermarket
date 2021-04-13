#ifndef _PRODUCT_HPP
#define _PRODUCT_HPP

#include <string>
#include <vector>
#include "user.hpp"

using namespace std;

typedef string COMMENT_TEXT;
typedef pair < User* , COMMENT_TEXT > Comment;
typedef vector < string > Information;

class Product {
public:
	Product(int _id , Information _info , Information _info_label) 
								: id(_id) , info(_info) , info_label(_info_label){};

	virtual bool compare_type_with(Product* other_product) = 0;
	virtual bool compare_type_with(string other_product_type) = 0;

	virtual void compare_info_with(Product* other_product) = 0;
	virtual void compare_info_with(Information other_product_info) = 0;

	void add_comment(User* buyer , string comment);

	string get_id_and_name();
	void print_id_and_name_oneline();
	string print_details();
	void show_comments();
	
	bool is_id_equals(string cur_id);
	bool is_id_equals(int cur_id);

protected:
	int id;
	string type;
	Information info , info_label;
	vector < Comment > comments;
};

#endif