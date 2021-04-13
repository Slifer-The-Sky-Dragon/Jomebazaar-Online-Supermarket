#ifndef _USER_HPP
#define _USER_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define SPACER " | "

typedef long long int Hashcode;

class User {
public:
	User(string _email , string _username , Hashcode _pass , int _id);
	bool is_username_equal(string _username);
	bool is_email_and_password_equal(string _email , Hashcode _password);
	bool is_email_equal(string _email);
	bool is_username_and_password_equal(string _username , Hashcode _password);

	void show_username() { cout << username; };
	void show_id() { cout << id << SPACER; };
	int get_id() { return id; };
	string get_username(){ return username; };
	void print_wallet(int count);
	void charge_wallet(double amount);

	double get_balance();

protected:
	string email , username;
	Hashcode password;
	double balance;
	int id;
	vector < double > turnovers;
};

#endif