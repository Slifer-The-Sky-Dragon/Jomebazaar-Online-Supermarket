#include "handlers.hpp"
#include "my_server.hpp"
#include "Controller/controller.hpp"
#include "Controller/shop.hpp"
#include <cstdlib> // for rand and srand
#include <ctime>   // for time
#include <iostream>

#define HOME "/"
#define SIGNUP "/signup"
#define LOGIN "/login"
#define SIGNOUT "/signout"
#define IMPORT_PRODUCTS "/import_product"
#define ADD_OFFER "/addoffer"
#define SHOW_PRODUCT_INFO "/show_product_info"
#define ADD_TO_CART "/add_to_cart"
#define WALLET "/wallet"
#define CHARGE_WALLET "/charge_wallet"
#define CART "/cart"
#define SUBMIT_CART "/submit_cart"

using namespace std;

int main(int argc, char **argv) {
  srand(time(NULL)); // for rand
  Shop* shop = new Shop();
  Controller* controller = new Controller(shop);
  try {
    MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
    server.setNotFoundErrPage("static/404.html");

    server.get(HOME, new HomeHandler(controller));

    server.get(SIGNUP, new ShowPage("static/signup.html"));
    server.post(SIGNUP , new SignupHandler(controller));

    server.get(LOGIN, new ShowPage("static/login.html"));
    server.post(LOGIN, new LoginHandler(controller));

    server.get(SIGNOUT , new SignoutHandler(controller));

    server.post(IMPORT_PRODUCTS , new ImportProductsHandler(controller));

    server.get(ADD_OFFER , new AddOfferHandler(controller));
    server.post(ADD_OFFER , new AddOfferHandler(controller));

    server.get(SHOW_PRODUCT_INFO , new ShowProductHandler(controller));
    server.post(ADD_TO_CART , new AddToCartHandler(controller));

    server.get(WALLET , new WalletHandler(controller));
    server.post(CHARGE_WALLET , new ChargeWalletHandler(controller));

    server.get(CART , new CartHandler(controller));
    server.post(SUBMIT_CART , new SubmitCartHandler(controller));

    server.get("/shop.jpg", new ShowImage("static/shop.jpg"));
    server.get("/admin.png", new ShowImage("static/admin.png"));
    server.get("/user.png", new ShowImage("static/user.png"));


    server.run();
  } catch (Server::Exception e) {
    cerr << e.getMessage() << endl;
  }
}
