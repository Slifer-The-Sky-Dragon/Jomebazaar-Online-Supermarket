#include "product.hpp"
#include <iostream>
#include <sstream>

#define NAME_INDEX 0
#define NEXT 1

#define EMPTY ""

#define BUYER first;
#define COMMENT_TEXT second;

#define SPACER " | "
#define NEW_LINE "\n"

string Product::get_id_and_name(){
	stringstream ss;
	ss << id << NEW_LINE << info[NAME_INDEX] << NEW_LINE;
	string cur_id , cur_name;
	getline(ss , cur_id);
	getline(ss , cur_name);

	return (cur_id + NEW_LINE + cur_name + NEW_LINE);
}

void Product::print_id_and_name_oneline(){
	cout << id << SPACER << info[NAME_INDEX];	
}

bool Product::is_id_equals(string cur_id){
	if(id == stoi(cur_id))
		return true;
	return false;
}

bool Product::is_id_equals(int cur_id){
	if(id == cur_id)
		return true;
	return false;
}


string Product::print_details(){
	string res = EMPTY;
	res = info_label[NAME_INDEX] + NEW_LINE;
	res += info[NAME_INDEX] + NEW_LINE;
	for(int detail_number = NAME_INDEX + NEXT ; detail_number < info.size() ; detail_number++){
		res += info_label[detail_number] + NEW_LINE	+ info[detail_number] + NEW_LINE;
	}
	return res;
}

void Product::add_comment(User* buyer , string comment){
	comments.push_back(make_pair(buyer , comment));
}

void Product::show_comments(){
	cout << info[NAME_INDEX] << endl;
	for(int comment_number = comments.size() - 1 ; comment_number >= 0 ; comment_number--){
		User* buyer = comments[comment_number].BUYER;
		string cur_comment = comments[comment_number].COMMENT_TEXT;
		buyer -> show_username();
		cout << SPACER;
		cout << cur_comment << endl;
	}
}













