#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include "Controller/controller.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

class RandomNumberHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class SignupHandler : public RequestHandler {
public:
	SignupHandler(Controller* _controller) : controller(_controller) {};
	Response* signup_complete_page(Request *req , SID user_sid);
	Response* signup_failed_page(Request *req , bool bad_pas , bool invalid_username);
	Response *callback(Request *);
private:
	Controller* controller;
};

class LoginHandler : public RequestHandler {
public:
	LoginHandler(Controller* _controller) : controller(_controller) {};
	Response* login_complete_page(SID user_sid);
	Response* login_failed_page();
	Response *callback(Request *);
private:
	Controller* controller;
};

class HomeHandler : public RequestHandler {
public:
	HomeHandler(Controller* _controller) : controller(_controller) {};
	Response* default_home_page();
	Response* admin_home_page(SID user_sid);
	Response* buyer_home_page(SID user_sid);
	Response* seller_home_page(SID user_sid);

	Response *callback(Request *);
private:
	Controller* controller;
};

class SignoutHandler : public RequestHandler {
public:
	SignoutHandler(Controller* _controller) : controller(_controller) {};

	Response *callback(Request *);
private:
	Controller* controller;
};


class ImportProductsHandler : public RequestHandler {
public:
	ImportProductsHandler(Controller* _controller) : controller(_controller) {};

	Response *callback(Request *);
private:
	Controller* controller;
};

class AddOfferHandler : public RequestHandler {
public:
	AddOfferHandler(Controller* _controller) : controller(_controller) {};

	Response* add_offer_form_page(SID user_sid , int is_add_done);
	Response *callback(Request *);
private:
	Controller* controller;
};


class ShowProductHandler : public RequestHandler {
public:
	ShowProductHandler(Controller* _controller) : controller(_controller) {};

	Response* show_product_info_page(SID user_sid , string product_id);
	Response *callback(Request *);
private:
	Controller* controller;
};

class AddToCartHandler : public RequestHandler {
public:
	AddToCartHandler(Controller* _controller) : controller(_controller) {};

	Response *callback(Request *);
private:
	Controller* controller;
};

class WalletHandler : public RequestHandler {
public:
	WalletHandler(Controller* _controller) : controller(_controller) {};

	Response* wallet_page(SID user_sid);
	Response *callback(Request *);
private:
	Controller* controller;
};

class ChargeWalletHandler : public RequestHandler {
public:
	ChargeWalletHandler(Controller* _controller) : controller(_controller) {};

	Response *callback(Request *);
private:
	Controller* controller;
};

class CartHandler : public RequestHandler {
public:
	CartHandler(Controller* _controller) : controller(_controller) {};
	
	Response* cart_page(Request* req , SID user_sid);
	Response *callback(Request *);
private:
	Controller* controller;
};

class SubmitCartHandler : public RequestHandler {
public:
	SubmitCartHandler(Controller* _controller) : controller(_controller) {};
	
	Response *callback(Request *);
private:
	Controller* controller;
};


class UploadHandler : public RequestHandler {
public:
  Response *callback(Request *);
};

class ColorHandler : public TemplateHandler {
public:
  ColorHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

#endif
