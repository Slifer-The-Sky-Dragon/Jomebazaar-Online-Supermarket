#include "user.hpp"
#include "bad_req.hpp"

using namespace std;

#define INITIAL_BALANCE 0
#define CREDIT_SIGN "credit"
#define VECTOR_FIRST_INDEX 0
#define DONE "OK\n"
#define SPACER " | "

typedef long long int Hashcode;

User::User(string _email , string _username , Hashcode _pass , int _id){
	balance = INITIAL_BALANCE;
	email = _email;
	username = _username;
	password = _pass;
	id = _id;
	turnovers.push_back(INITIAL_BALANCE);
}

bool User::is_username_equal(string _username){
	if(username == _username)
		return true;
	return false;
}

bool User::is_email_and_password_equal(string _email , Hashcode _password){
	if(email == _email && password == _password)
		return true;
	return false;
}

bool User::is_username_and_password_equal(string _username , Hashcode _password){
	if(username == _username && password == _password)
		return true;
	return false;	
}


bool User::is_email_equal(string _email){
	if(email == _email)
		return true;
	return false;
}

void User::print_wallet(int count){
	cout << CREDIT_SIGN << endl;
	int turnovers_count = turnovers.size();
	int last_turnover_index = turnovers_count - 1;

	int temp_cnt = 0 , temp_index = last_turnover_index;
	while(temp_cnt < count && temp_index >= VECTOR_FIRST_INDEX){
		cout << turnovers[temp_index] << endl;
		temp_cnt++;
		temp_index--;
	}
}

double User::get_balance(){
	return balance;
}

void User::charge_wallet(double amount){
	try{
		if(amount <= 0)
			throw Bad_request();
		balance += amount;
		turnovers.push_back(balance);
	}catch(Bad_request e){
		cout << e.what();
	}
}





