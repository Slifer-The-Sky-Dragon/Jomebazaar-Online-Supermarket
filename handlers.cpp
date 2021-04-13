#include "handlers.hpp"
#include "Controller/bad_req.hpp"
#include "Controller/permision_denied.hpp"
#include <sstream>

using namespace std;

#define MAX_OFFER_NUMBER 1000


#define ADMIN_SID 0
#define DONE 1
#define NOT_DONE 0
#define DUPLICATE_ERROR -1

#define OK "1"
#define BAD "0"

#define INFO "More Info"

#define HOME "/"
#define SIGNUP "/signup"
#define LOGIN "/login"
#define SIGNOUT "/signout"

#define USERNAME_PARAM "username"
#define PASSWORD_PARAM "password"
#define RE_ENTER_PASS_PARAM "Re_enter_password"
#define EMAIL_PARAM "email"
#define USER_TYPE_PARAM "user_type"
#define PRODUCT_FILE_PARAM "products_file"
#define PRODUCT_TYPE_PARAM "type_of_product"
#define NO_SID -1

#define EMPTY ""
#define BAD_PASSWORD_ERROR "You didn't confirm you're password correctly!"
#define INVALID_USERNAME_ERROR "Username Exists!"
#define WRONG_USER_OR_PASS "You entered worng Username or password!"
#define ADD_DONE_MESSAGE "Offer added succesfully!"
#define DUPLICATE_ERROR_MESSAGE "You offered on this product before!"

#define SUB_DONE_MESSAGE "Cart submited succesfully!"
#define SUB_ERROR_MESSAGE "Insuffiend fund!"


Response *RandomNumberHandler::callback(Request *req) {
  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body style=\"text-align: center;\">";
  body += "<h1>AP HTTP</h1>";
  body += "<p>";
  body += "a random number in [1, 10] is: ";
  body += to_string(rand() % 10 + 1);
  body += "</p>";
  body += "<p>";
  body += "SeddionId: ";
  body += req->getSessionId();
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setBody(body);
  return res;
}

Response* SignupHandler::signup_complete_page(Request *req , SID user_sid){
  Response *res = new Response;
  string home_link = "/";
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body background=\"/shop.jpg\" style=\"text-align: center;\">";
  body += "<h1>Succesfully Logined</h1>";
  body += "<p>";
  body += "To go to the first page please";
  body += "<a href=\"" + home_link + "\" target=\"_top\"> Click here!</a>";
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setSessionId(to_string(user_sid));
  res->setBody(body);
  return res;
}

Response* SignupHandler::signup_failed_page(Request *req , bool bad_pas , bool invalid_username){
  Response* res = new Response;

  string body = "";
  res->setHeader("Content-Type", "text/html");

  string error_message = EMPTY;
  if(bad_pas) error_message = BAD_PASSWORD_ERROR;
  else error_message = INVALID_USERNAME_ERROR;

  body+= "<!DOCTYPE html>";
  body+= "<html>";
  body+=    "<style>";
  body+=     "input[type=text],[type=password] {";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";
  body+=     "input[type=submit]{";
  body+=       "width: 80%;";
  body+=       "background-color: #33cc00;";
  body+=       "color: white;";
  body+=       "padding: 14px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "border: none;";
  body+=       "border-radius: 4px;";
  body+=       "cursor: pointer;";  
  body+=     "}";
  body+=     "body{";
  body+=       "text-align: center;";
  body+=     "}";
  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 180px;";
  body+=       "left: 25px;";
  body+=       "width: 50%;";
  body+=       "border-radius: 3px;";
  body+=       "background-color: #e6ac00;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}"; 
  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 120px;";
  body+=       "left: 250px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";
 
  body+=  ".form-radio";
  body+=  "{";
  body+=       "-webkit-appearance: none;";
  body+=       "-moz-appearance: none;";
  body+=       "appearance: none;";
  body+=       "display: inline-block;";
  body+=       "position: relative;";
  body+=       "background-color: #f1f1f1;";
  body+=       "color: #666;";
  body+=       "top: 10px;";
  body+=       "height: 30px;";
  body+=       "width: 30px;";
  body+=       "border: 0;";
  body+=       "border-radius: 50px;";
  body+=       "cursor: pointer;";     
  body+=       "margin-right: 7px;";
  body+=       "outline: none;";
  body+=  "}";

  body+=  ".form-radio:checked::before";
  body+=  "{";
  body+=       "position: absolute;";
  body+=       "font: 13px/1 'Open Sans', sans-serif;";
  body+=       "left: 11px;";
  body+=       "top: 7px;";
  body+=       "content: '\\02143';";
  body+=       "transform: rotate(40deg);";
  body+=  "}";
  body+=  ".form-radio:hover";
  body+=  "{";
  body+=       "background-color: #f7f7f7;";
  body+=  "}";
  body+=  ".form-radio:checked";
  body+=  "{";
  body+=       "background-color: #f1f1f1;";
  body+=  "}";


  body+=     "label {";
  body+=         "font-weight: bold;";
  body+=     "}";

  body+=  ".alert {";
  body+=    "padding: 20px;";
  body+=    "background-color: #ff3300;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".closebtn {";
  body+=    "margin-left: 15px;";
  body+=    "color: white;";
  body+=    "font-weight: bold;";
  body+=    "float: right;";
  body+=    "font-size: 22px;";
  body+=    "line-height: 20px;";
  body+=    "cursor: pointer;";
  body+=    "transition: 0.3s;";
  body+=  "}";

  body+=  ".closebtn:hover {";
  body+=    "color: black;";
  body+=  "}";   
  body+=   "</style>";

  body+=   "<body background=\"/shop.jpg\">";
  body+=    "<h1>Welcome to Localhost!</h1>";
  body+=    "<div>";
  body+=      "<form action=\"/signup\" method=\"post\">";
  body+=      "<div class=\"alert\">";
  body+=      "<span class=\"closebtn\" onclick=\"this.parentElement.style.display='none';\">&times;</span>";
  body+=      error_message;
  body+=        "</div>";
  body+=        "<label for=\"username\">Username</label>";
  body+=        "<br/><input name=\"username\" type=\"text\" placeholder=\"Username\" required";
  if(invalid_username) body += " style=\"border: 2px solid red;border-radius: 4px;\"";
  body += "/>";
  body+=        "<br/><label for=\"password\">Password</label>";
  body+=        "<br/><input name=\"password\" type=\"password\" placeholder=\"Password\" required";
  if(bad_pas) body += " style=\"border: 2px solid red;border-radius: 4px;\"";
  body += "/>";
  body+=        "<br/><label for=\"Re_enter_password\">Re-enter password</label>";
  body+=        "<br/><input name=\"Re_enter_password\" type = \"password\" placeholder=\"Password\" required";
  if(bad_pas) body += " style=\"border: 2px solid red;border-radius: 4px;\"";
  body += "/>";
  body+=        "<br/><label for=\"email\">Email</label>";
  body+=        "<br/><input name=\"email\" type = \"text\" placeholder=\"email@email.com\" required/>"; 
  body+=        "<br/><label for=\"type_of_user\">Account type : </label>";
  body+=        "<label for=\"buyer\">Buyer</label>";
  body+=        "<input type=\"radio\" name=\"user_type\" id=\"buyer\" value=\"buyer\" class=\"form-radio\" required>";
  body+=        "<label for=\"seller\">Seller</label>";
  body+=        "<input type=\"radio\" name=\"user_type\" id=\"seller\" value=\"seller\"  class=\"form-radio\" required><br><br>";
  body+=        "<input type=\"submit\" value=\"Submit\">";
  body+=      "</form>";
  body+=    "</div>";
  body+=  "</body>";
  body+= "</html>";

  res->setBody(body);
  return res;
}

Response *SignupHandler::callback(Request *req) {
  Response *res = new Response;

  bool bad_pas = false;
  bool invalid_username = false;

  string username = req -> getBodyParam(USERNAME_PARAM);
  string password = req -> getBodyParam(PASSWORD_PARAM);
  string re_enter_password = req -> getBodyParam(RE_ENTER_PASS_PARAM);
  string email = req -> getBodyParam(EMAIL_PARAM);
  string type = req -> getBodyParam(USER_TYPE_PARAM);

  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);

  try{
    if(controller -> is_active_user(user_sid) == true)
      throw Permision_denied();
    if(password != re_enter_password){
      bad_pas = true;
      throw Bad_request();
    }
    SID new_user_sid = controller -> signup_user(email , username , password , type);
    res = signup_complete_page(req , new_user_sid);
  }catch(Bad_request e){
    if(bad_pas == false) invalid_username = true;
    res = signup_failed_page(req , bad_pas , invalid_username);    
  }catch(Permision_denied e){
    res = Response::redirect("/");
  }
  return res;
}

Response* LoginHandler::login_failed_page(){
  Response* res = new Response;

  string body = "";
  res->setHeader("Content-Type", "text/html");

  string error_message = WRONG_USER_OR_PASS;

  body+= "<!DOCTYPE html>";
  body+= "<html>";
  body+=    "<style>";
  body+=     "input[type=text],[type=password] {";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";
  body+=     "input[type=submit]{";
  body+=       "width: 80%;";
  body+=       "background-color: #33cc00;";
  body+=       "color: white;";
  body+=       "padding: 14px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "border: none;";
  body+=       "border-radius: 4px;";
  body+=       "cursor: pointer;";  
  body+=     "}";
  body+=     "body{";
  body+=       "text-align: center;";
  body+=     "}";
  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 180px;";
  body+=       "left: 25px;";
  body+=       "width: 50%;";
  body+=       "border-radius: 3px;";
  body+=       "background-color: #e6ac00;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}"; 
  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 120px;";
  body+=       "left: 250px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";
 
  body+=     "label {";
  body+=         "font-weight: bold;";
  body+=     "}";

  body+=  ".alert {";
  body+=    "padding: 20px;";
  body+=    "background-color: #ff3300;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".closebtn {";
  body+=    "margin-left: 15px;";
  body+=    "color: white;";
  body+=    "font-weight: bold;";
  body+=    "float: right;";
  body+=    "font-size: 22px;";
  body+=    "line-height: 20px;";
  body+=    "cursor: pointer;";
  body+=    "transition: 0.3s;";
  body+=  "}";

  body+=  ".closebtn:hover {";
  body+=    "color: black;";
  body+=  "}";   
  body+=   "</style>";

  body+=   "<body background=\"/shop.jpg\">";
  body+=    "<h1>Welcome to Localhost!</h1>";
  body+=    "<div>";
  body+=      "<form action=\"/login\" method=\"post\">";
  body+=      "<div class=\"alert\">";
  body+=      "<span class=\"closebtn\" onclick=\"this.parentElement.style.display='none';\">&times;</span>";
  body+=      error_message;
  body+=        "</div>";
  body+=        "<label for=\"username\">Username</label>";
  body+=        "<br/><input name=\"username\" type=\"text\" placeholder=\"Username\" required";
  body += " style=\"border: 2px solid red;border-radius: 4px;\"";
  body += "/>";
  body+=        "<br/><label for=\"password\">Password</label>";
  body+=        "<br/><input name=\"password\" type=\"password\" placeholder=\"Password\" required";
  body += " style=\"border: 2px solid red;border-radius: 4px;\"";
  body += "/>";
  body+=        "<input type=\"submit\" value=\"Login\">";
  body+=      "</form>";
  body+=    "</div>";
  body+=  "</body>";
  body+= "</html>";  

  res->setBody(body);
  return res;  
}

Response* LoginHandler::login_complete_page(SID user_sid){
  Response *res = new Response;
  string home_link = "/";
  res->setHeader("Content-Type", "text/html");
  string body;
  body += "<!DOCTYPE html>";
  body += "<html>";
  body += "<body background=\"/shop.jpg\" style=\"text-align: center;\">";
  body += "<h1>Succesfully Logined</h1>";
  body += "<p>";
  body += "To go to the first page please";
  body += "<a href=\"" + home_link + "\" target=\"_top\"> Click here!</a>";
  body += "</p>";
  body += "</body>";
  body += "</html>";
  res->setSessionId(to_string(user_sid));
  res->setBody(body);
  return res;  
}


Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");

  Response* res = new Response();

  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);

  try{
    if(controller -> is_active_user(user_sid) == true)
      throw Permision_denied();
    SID new_user_sid = controller -> login_user(username , password);
    res = login_complete_page(new_user_sid);
  }catch(Bad_request e){
    res = login_failed_page();    
  }catch(Permision_denied e){
    res = Response::redirect("/");
  }

  return res;
}


Response* HomeHandler::default_home_page(){
  Response* res = new Response();
  res->setHeader("Content-Type", "text/html");
  string body = EMPTY;

  body += "<!DOCTYPE html>";
  body += "<html>";
  body+=  "<style>";
  body+=     ".button {";
  body +=        "font-weight: bold;";
  body+=         "background-color: #e6ac00;";
  body+=         "border: none;";
  body+=         "color: white;";
  body +=        "width: 30%;";
  body+=         "padding: 20px 34px;";
  body+=         "text-align: center;";
  body+=         "text-decoration: none;";
  body+=         "display: inline-block;";
  body+=         "font-size: 20px;";
  body+=         "margin: 4px 2px;";
  body+=         "cursor: pointer;";
  body+=     "}";

  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 300px;";
  body+=       "left: 300px;";
  body+=       "width: 50%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}";

  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 240px;";
  body+=       "left: 410px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";

  body+=  "</style>";
  body +=   "<body background=\"/shop.jpg\">";
  body +=     "<h1>AP Shop</h1>";
  body +=     "<div>";
  body +=     "<a href=\"/signup\" class=\"button\">SIGN UP</a>";
  body +=     "<br />";
  body +=     "<a href=\"/login\" class=\"button\">SIGN IN</a>";
  body +=     "<br />";
  body +=     "</div>";
  body +=   "</body>";
  body += "</html>";

  res -> setBody(body);
  return res;
}

Response* HomeHandler::admin_home_page(SID user_sid){
  Response* res = new Response();
  res->setHeader("Content-Type", "text/html");
  string body = EMPTY;

  body += "<!DOCTYPE html>";
  body += "<html>";
  body+=  "<style>";
  body+=     ".button {";
  body +=       "font-weight: bold;";
  body+=         "background-color: #e6ac00;";
  body+=         "border: none;";
  body+=         "color: white;";
  body +=        "width: 30%;";
  body+=         "padding: 20px 34px;";
  body+=         "text-align: center;";
  body+=         "text-decoration: none;";
  body+=         "display: inline-block;";
  body+=         "font-size: 20px;";
  body+=         "margin: 4px 2px;";
  body+=         "cursor: pointer;";
  body+=     "}";


  body+=     ".form-radio";
  body+=     "{";
  body+=          "-webkit-appearance: none;";
  body+=          "-moz-appearance: none;";
  body+=          "appearance: none;";
  body+=          "display: inline-block;";
  body+=          "position: relative;";
  body+=          "background-color: #f1f1f1;";
  body+=          "color: #666;";
  body+=          "top: 10px;";
  body+=          "height: 30px;";
  body+=          "width: 30px;";
  body+=          "border: 0;";
  body+=          "border-radius: 50px;";
  body+=          "cursor: pointer;";     
  body+=          "margin-right: 7px;";
  body+=          "outline: none;";
  body+=     "}";
  body+=     ".form-radio:checked::before";
  body+=     "{";
  body+=          "position: absolute;";
  body+=          "font: 13px/1 'Open Sans', sans-serif;";
  body+=          "left: 11px;";
  body+=          "top: 7px;";
  body+=          "content: '\\02143';";
  body+=          "transform: rotate(40deg);";
  body+=     "}";
  body+=     ".form-radio:hover";
  body+=     "{";
  body+=          "background-color: #f7f7f7;";
  body+=     "}";
  body+=     ".form-radio:checked";
  body+=     "{";
  body+=          "background-color: #f1f1f1;";
  body+=     "}";


  body+=     "input[type=submit]{";
  body+=       "width: 80%;";
  body+=       "background-color: #33cc00;";
  body+=       "color: white;";
  body+=       "padding: 14px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "border: none;";
  body+=       "border-radius: 4px;";
  body+=       "cursor: pointer;";  
  body+=     "}";

  body+=     "body{";
  body+=       "text-align: center;";
  body+=     "}";

  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 300px;";
  body+=       "left: 200px;";
  body+=       "width: 30%;";
  body+=       "background-color: #e6ac00;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}";

  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 50px;";
  body+=       "left: 500px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";  

  body+=     "h2 {";
  body+=       "position: fixed;";
  body+=       "top: 240px;";
  body+=       "left: 340px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";


  body +=    ".signout-part{";
  body+=       "position: fixed;";
  body+=       "top: 50px;";
  body+=       "left: 50px;";
  body+=       "width: 20%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body +=    "}";

  body+=  "</style>";

  body +=   "<body background=\"/shop.jpg\">";

  body +=  "<div2 class = \"signout-part\">";
  body +=     "<img src=\"/admin.png\" style=\"width:10%;\">";
  body +=     "<label for=\"signout\">Hi Admin , </label>";
  body +=     "<a href=\"/signout\" id = \"signout\">Signout</a>";
  body +=  "</div2>";

  body +=  "<div>";
  body +=    "<h2>Upload Product</h2>";
  body +=    "<form action=\"/import_product\" method=\"post\" enctype=\"multipart/form-data\">";

  body+=        "<br/><label for=\"type_of_product\">Product type : </label>";
  body+=        "<label for=\"tv\">Tv</label>";
  body+=        "<input type=\"radio\" name=\"type_of_product\" id=\"tv\" value=\"tv\" class = \"form-radio\" required>";
  body+=        "<label for=\"mobile\">Mobile</label>";
  body+=        "<input type=\"radio\" name=\"type_of_product\" id=\"mobile\" value=\"mobile\" class = \"form-radio\" required>";
  body+=        "<label for=\"car\">Car</label>";
  body+=        "<input type=\"radio\" name=\"type_of_product\" id=\"car\" value=\"car\" class = \"form-radio\" required><br><br>";

  body +=      "<input type=\"file\" name=\"products_file\" accept=\"text/csv\" required>";

  body +=       "<input type=\"submit\" value=\"Upload Products\">";
  body +=    "</form>";
  body +=  "</div>";

  body +=   "</body>";
  body += "</html>";

  res -> setBody(body);
  res -> setSessionId(to_string(user_sid));
  return res;
}


Response* HomeHandler::buyer_home_page(SID user_sid){
  Response* res = new Response();
  res->setHeader("Content-Type", "text/html");
  string body = EMPTY;

  string products = controller -> get_products();
  stringstream ss(products);

  body+= "<!DOCTYPE html>";
  body+= "<html>";
  body+= "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  body+= "<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">";

  body+=  "<style>";

  body+=     ".button {";
  body +=        "font-weight: bold;";
  body+=         "background-color: #e6ac00;";
  body+=         "border: none;";
  body+=         "color: white;";
  body +=        "width: 30%;";
  body+=         "padding: 20px 34px;";
  body+=         "text-align: center;";
  body+=         "text-decoration: none;";
  body+=         "display: inline-block;";
  body+=         "font-size: 20px;";
  body+=         "margin: 4px 2px;";
  body+=         "cursor: pointer;";
  body+=     "}";


  body+=     "input[type=password] {";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";

  body+=     "input[type=text],[type=number] {";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";


  body+=     "input[type=submit]{";
  body+=       "width: 80%;";
  body+=       "background-color: #33cc00;";
  body+=       "color: white;";
  body+=       "padding: 14px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "border: none;";
  body+=       "border-radius: 4px;";
  body+=       "cursor: pointer;";  
  body+=     "}";


  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 100px;";
  body+=       "left: 0px;";
  body+=       "width: 30%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}";

  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 170px;";
  body+=       "left: 550px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";

  body+=     "div2 {";
  body+=       "position: fixed;";
  body+=       "top: 255px;";
  body+=       "left: 300px;";
  body+=       "width: 50%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}";

  body+=     "p{";
  body+=        "font-size: 10px;";
  body+=     "}";

  body+=     "body{";
  body+=       "text-align: center;";
  body+=     "}";

  body+=     "table{";
  body+=       "overflow-y:scroll;";
  body+=       "width: 30%;";
  body+=       "height: 500px;";
  body+=       "display:block;";
  body+=     "}";

  body+=  ".alert {";
  body+=    "padding: 20px;";
  body+=    "background-color: #33cc00;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".alert2 {";
  body+=    "padding: 20px;";
  body+=    "background-color: #ff3300;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".closebtn {";
  body+=    "margin-left: 15px;";
  body+=    "color: white;";
  body+=    "font-weight: bold;";
  body+=    "float: right;";
  body+=    "font-size: 22px;";
  body+=    "line-height: 20px;";
  body+=    "cursor: pointer;";
  body+=    "transition: 0.3s;";
  body+=  "}";

  body+=  ".closebtn:hover {";
  body+=    "color: black;";
  body+=  "}";   

  body +=  ".signout-part{";
  body+=       "position: fixed;";
  body+=       "top: 50px;";
  body+=       "left: 50px;";
  body+=       "width: 20%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body +=    "}";


  body+=  "</style>";
  body +=   "<body background=\"/shop.jpg\">";

  string cur_username = controller -> get_username(user_sid);

  body +=  "<div2 class = \"signout-part\">";
  body +=     "<img src=\"/user.png\" style=\"width:10%;\">";
  body +=     "<label for=\"signout\">  Hi " + cur_username + ", </label>";
  body +=     "<a href=\"/signout\" id = \"signout\">Signout</a>";
  body +=  "</div2>";

  body +=     "<div>";
  body +=       "<table class=\"w3-table w3-striped w3-bordered\"  style=\"overflow-y:scroll;height: 500px;display:block;\">";
  body +=        "<thead>";
  body +=         "<tr class=\"w3-red\">";
  body +=           "<th>Product ID</th>";
  body +=           "<th>Poduct Name</th>";
  body +=         "</tr>";
  body +=        "</thead>";

    int products_cnt = 0;

    string cur_product_id , cur_product_name;

    while(getline(ss , cur_product_id)){
      products_cnt ++;
      getline(ss , cur_product_name);

      body +=  "<tr class=\"w3-gray\">";
      body +=     "<td><a href=\"/show_product_info?q=" + cur_product_id + "\">" + cur_product_id + "</a></td>";
      body +=     "<td>" + cur_product_name + "</td>";
      body +=  "</tr>";
    }

  body +=       "</table>";

  body +=     "</div>";

  body +=     "<div2>";
  body +=       "<a href=\"/wallet\" class=\"button\">Wallet</a>";
  body +=       "<br/>";
  body +=       "<a href=\"/cart\" class=\"button\">Cart</a>";
  body +=       "<br/>";
  body +=     "</div2>";

  body +=   "</body>";
  body += "</html>";

  res->setBody(body);
  res->setSessionId(to_string(user_sid));
  return res;
}


Response* HomeHandler::seller_home_page(SID user_sid){
  Response* res = new Response();
  res->setHeader("Content-Type", "text/html");
  string body = EMPTY;

  string seller_offers = controller -> get_my_offers(user_sid);
  stringstream ss(seller_offers);

  body+= "<!DOCTYPE html>";
  body+= "<html>";
  body+= "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  body+= "<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">";
  body+=  "<style>";
  body+=     ".button {";
  body +=        "font-weight: bold;";
  body+=         "background-color: #e6ac00;";
  body+=         "border: none;";
  body+=         "color: white;";
  body +=        "width: 30%;";
  body+=         "padding: 20px 34px;";
  body+=         "text-align: center;";
  body+=         "text-decoration: none;";
  body+=         "display: inline-block;";
  body+=         "font-size: 20px;";
  body+=         "margin: 4px 2px;";
  body+=         "cursor: pointer;";
  body+=     "}";

  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 100px;";
  body+=       "left: 0px;";
  body+=       "width: 30%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}";

  body+=     "div2 {";
  body+=       "position: fixed;";
  body+=       "top: 255px;";
  body+=       "left: 480px;";
  body+=       "width: 50%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}";

  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 200px;";
  body+=       "left: 510px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";


  body +=    ".signout-part{";
  body+=       "position: fixed;";
  body+=       "top: 50px;";
  body+=       "left: 50px;";
  body+=       "width: 20%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body +=    "}";


  body+=  "</style>";
  body +=   "<body background=\"/shop.jpg\">";
  body +=     "<h1>Seller Menu</h1>";

  string cur_username = controller -> get_username(user_sid);

  body +=  "<div2 class = \"signout-part\">";
  body +=     "<img src=\"/user.png\" style=\"width:10%;\">";
  body +=     "<label for=\"signout\">  Hi " + cur_username + ", </label>";
  body +=     "<a href=\"/signout\" id = \"signout\">Signout</a>";
  body +=  "</div2>";

  body +=     "<div>";
  body +=       "<table class=\"w3-table w3-striped w3-bordered\"  style=\"overflow-y:scroll;height: 500px;display:block;\">";
  body +=        "<thead>";
  body +=         "<tr class=\"w3-red\">";
  body +=           "<th>Product ID</th>";
  body +=           "<th>Offer ID</th>";
  body +=           "<th>Offer Unit Price</th>";
  body +=           "<th>Offer Amount</th>";

  body +=         "</tr>";
  body +=        "</thead>";

    int products_cnt = 0;

    string cur_product_id , cur_offer_id , cur_price , cur_amount;
    while(getline(ss , cur_product_id)){
      products_cnt ++;
      getline(ss , cur_offer_id);
      getline(ss , cur_price);
      getline(ss , cur_amount);

      body +=  "<tr class=\"w3-gray\">";
      body +=     "<td>" + cur_product_id + "</td>";
      body +=     "<td>" + cur_offer_id + "</td>";
      body +=     "<td>" + cur_price + "</td>";
      body +=     "<td>" + cur_amount + "</td>";
      body +=  "</tr>";
    }

  body +=       "</table>";

  body +=     "</div>";


  body +=     "<div2>";
  body +=     "<a href=\"/addoffer\" class=\"button\">Add Offer</a>";
  body +=     "<br />";
  body +=     "</div2>";
  body +=   "</body>";
  body += "</html>";

  res -> setBody(body);
  res -> setSessionId(to_string(user_sid));
  return res;
}


Response *HomeHandler::callback(Request *req) {
  Response* res = new Response();

  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);

  if(controller -> is_active_user(user_sid) == false)
    res = default_home_page();
  else if(controller -> is_user_buyer(user_sid)){
    res = buyer_home_page(user_sid);
  }
  else if(controller -> is_user_seller(user_sid)){
    res = seller_home_page(user_sid);
  }
  else{
    res = admin_home_page(user_sid);
  }
  return res;
}

Response* SignoutHandler::callback(Request* req){
  Response* res = new Response();

  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);
  controller -> logout_user(user_sid);

  res = Response::redirect("/");
  return res;
}

Response* ImportProductsHandler::callback(Request* req){
  Response* res = new Response();

  string product_data = req->getBodyParam(PRODUCT_FILE_PARAM);
  string product_type = req->getBodyParam(PRODUCT_TYPE_PARAM);

  controller -> import_products(product_data , product_type);

  res = Response::redirect("/");
  res -> setSessionId(to_string(ADMIN_SID));
  return res;
}

Response* AddOfferHandler::add_offer_form_page(SID user_sid , int is_add_done){
  Response* res = new Response();
  res->setHeader("Content-Type", "text/html");
  string body = EMPTY;

  string products = controller -> get_products();
  stringstream ss(products);

  body+= "<!DOCTYPE html>";
  body+= "<html>";
  body+= "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  body+= "<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">";

  body+=  "<style>";
  body+=     ".button {";
  body+=        "position: fixed;";
  body+=        "top: 590px;";
  body+=        "left: 540px;";
  body+=        "font-weight: bold;";
  body+=         "background-color: #ff3300;";
  body+=         "width: 10%;";
  body+=         "color: white;";
  body+=         "padding: 14px 20px;";
  body+=         "margin: 8px 0;";
  body+=         "border: none;";
  body+=         "border-radius: 4px;";
  body+=         "cursor: pointer;";  
  body+=     "}";

  body+=     "input[type=password] {";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";

  body+=     "input[type=text],[type=number] {";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";


  body+=     "input[type=submit]{";
  body+=       "width: 80%;";
  body+=       "background-color: #33cc00;";
  body+=       "color: white;";
  body+=       "padding: 14px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "border: none;";
  body+=       "border-radius: 4px;";
  body+=       "cursor: pointer;";  
  body+=     "}";


  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 100px;";
  body+=       "left: 0px;";
  body+=       "width: 30%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}";

  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 170px;";
  body+=       "left: 550px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";

  body+=     "div2 {";
  body+=           "background-color: #e6ac00;";
  body+=           "position: fixed;";
  body+=           "top: 230px;";
  body+=           "left: 440px;";
  body+=           "width: 25%;";
  body+=           "height: 300;";
  body+=           "border-radius: 1px;";
  body+=           "margin: auto;" ;
  body+=     "}";

  body+=     "body{";
  body+=       "text-align: center;";
  body+=     "}";

  body+=     "table{";
  body+=       "overflow-y:scroll;";
  body+=       "width: 30%;";
  body+=       "height: 500px;";
  body+=       "display:block;";
  body+=     "}";

  body+=  ".alert {";
  body+=    "padding: 20px;";
  body+=    "background-color: #33cc00;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".alert2 {";
  body+=    "padding: 20px;";
  body+=    "background-color: #ff3300;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".closebtn {";
  body+=    "margin-left: 15px;";
  body+=    "color: white;";
  body+=    "font-weight: bold;";
  body+=    "float: right;";
  body+=    "font-size: 22px;";
  body+=    "line-height: 20px;";
  body+=    "cursor: pointer;";
  body+=    "transition: 0.3s;";
  body+=  "}";

  body+=  ".closebtn:hover {";
  body+=    "color: black;";
  body+=  "}";   

  body +=    ".signout-part{";
  body+=       "position: fixed;";
  body+=       "top: 50px;";
  body+=       "left: 50px;";
  body+=       "width: 20%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body +=    "}";

  body+=  "</style>";
  body +=   "<body background=\"/shop.jpg\">";

  string cur_username = controller -> get_username(user_sid);

  body +=  "<div3 class = \"signout-part\">";
  body +=     "<img src=\"/user.png\" style=\"width:10%;\">";
  body +=     "<label for=\"signout\">  Hi " + cur_username + ", </label>";
  body +=     "<a href=\"/signout\" id = \"signout\">Signout</a>";
  body +=  "</div3>";

  body +=     "<div>";
  body +=       "<table class=\"w3-table w3-striped w3-bordered\"  style=\"overflow-y:scroll;height: 500px;display:block;\">";
  body +=        "<thead>";
  body +=         "<tr class=\"w3-red\">";
  body +=           "<th>Product ID</th>";
  body +=           "<th>Poduct Name</th>";
  body +=         "</tr>";
  body +=        "</thead>";

    int products_cnt = 0;

    string cur_product_id , cur_product_name;
    while(getline(ss , cur_product_id)){
      products_cnt ++;
      getline(ss , cur_product_name);

      body +=  "<tr class=\"w3-gray\">";
      body +=     "<td>" + cur_product_id + "</td>";
      body +=     "<td>" + cur_product_name + "</td>";
      body +=  "</tr>";
    }

  body +=       "</table>";

  body +=     "</div>";

  body +=     "<div2>";
  body+=      "<form action=\"/addoffer\" method=\"post\">";
  if(is_add_done == DONE){
    body+=          "<div2 class=\"alert\">";
    body+=             "<span class=\"closebtn\" onclick=\"this.parentElement.style.display='none';\">&times;</span>";
    body+=             ADD_DONE_MESSAGE;
    body+=          "</div2>""<br/>";
  }
  else if(is_add_done == DUPLICATE_ERROR){
    body+=          "<div2 class=\"alert2\">";
    body+=             "<span class=\"closebtn\" onclick=\"this.parentElement.style.display='none';\">&times;</span>";
    body+=             DUPLICATE_ERROR_MESSAGE;
    body+=          "</div2>""<br/>";    
  }
  body+=            "<label for=\"product_id\">Product ID</label>";
  body+=            "<br/><input name=\"product_id\" type=\"number\" placeholder=\"Product ID\" min = \"1\" max = ";
  body+= "\"" + to_string(products_cnt) +"\"";
  body+= " required/>";
  body+=            "<br/><label for=\"offer_unit_price\">Offer Unit Price</label>";
  body+=            "<br/><input name=\"offer_unit_price\" type=\"text\" placeholder=\"Offer Unit Price\" required/>";
  body+=            "<br/><label for=\"offer_amount\">Offer Amount</label>";
  body+=            "<br/><input name=\"offer_amount\" type=\"text\" placeholder=\"Offer Amount\" required/>";
  body+=            "<input type=\"submit\" value=\"Add Offer\">";
  body +=         "</form>";

  body +=     "</div2>";

  body +=           "<a href=\"/\" class=\"button\" style=\"text-decoration: none;\"> Home </a>";
  body +=           "<br />";

  body +=   "</body>";
  body += "</html>";

  res->setBody(body);
  res->setSessionId(to_string(user_sid));
  return res;
}

Response* AddOfferHandler::callback(Request* req){
  Response* res = new Response();


  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid); 

  string product_id = EMPTY;
  string offer_unit_price , offer_amount;

  product_id = req -> getBodyParam("product_id");
  offer_unit_price = req -> getBodyParam("offer_unit_price");
  offer_amount = req -> getBodyParam("offer_amount");

  if(controller -> is_user_seller(user_sid) == true){
    if(product_id == EMPTY){
      res = add_offer_form_page(user_sid , NOT_DONE);
    }
    else{
      try{
        controller -> create_offer(user_sid , product_id , offer_unit_price , offer_amount);
        res = add_offer_form_page(user_sid , DONE);
      }
      catch(Bad_request e){
        res = add_offer_form_page(user_sid , DUPLICATE_ERROR);
      }
    }
  }
  else{
    res = Response::redirect("/");
  }

  res -> setSessionId(to_string(user_sid));
  return res; 
}


Response* ShowProductHandler::show_product_info_page(SID user_sid , string product_id){
  Response* res = new Response();
  res->setHeader("Content-Type", "text/html");
  string body = EMPTY;

  string product_info = controller -> get_product_detail(product_id);
  string product_offers = controller -> get_offers_on_product(product_id);

  stringstream ss(product_info);

  vector < string > labels;
  vector < string > values;

  string cur_label , cur_value;
  while(getline(ss , cur_label)){
    getline(ss , cur_value);

    labels.push_back(cur_label);
    values.push_back(cur_value);
  }

  stringstream ss2(product_offers);
  vector < string > offer_labels;

  for(int label_number = 0 ; label_number < 3 ; label_number++){
    getline(ss2 , cur_label);
    offer_labels.push_back(cur_label);
  }

  body+= "<!DOCTYPE html>";
  body+= "<html>";
  body+= "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  body+= "<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">";

  body+=  "<style>";
  body+=     ".button {";
  body+=        "position: fixed;";
  body+=        "top: 570px;";
  body+=        "left: 540px;";
  body+=        "font-weight: bold;";
  body+=         "background-color: #ff3300;";
  body+=         "width: 10%;";
  body+=         "color: white;";
  body+=         "padding: 14px 20px;";
  body+=         "margin: 8px 0;";
  body+=         "border: none;";
  body+=         "border-radius: 4px;";
  body+=         "cursor: pointer;";  
  body+=     "}";

  body+=     "input[type=password] {";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";

  body+=     "input[type=text]{";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";


  body+=     "input[type=submit]{";
  body+=       "background-color: #33cc00;";
  body+=       "color: white;";
  body+=     "}";


  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 100px;";
  body+=       "left: 0px;";
  body+=       "width: 55%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}";

  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 170px;";
  body+=       "left: 550px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";

  body+=     "div2 {";
  body+=           "background-color: #e6ac00;";
  body+=           "position: fixed;";
  body+=           "top: 230px;";
  body+=           "left: 440px;";
  body+=           "width: 25%;";
  body+=           "height: 300;";
  body+=           "border-radius: 1px;";
  body+=           "margin: auto;" ;
  body+=     "}";

  body+=     "body{";
  body+=       "text-align: center;";
  body+=     "}";

  body+=     "table{";
  body+=       "overflow-y:scroll;";
  body+=       "width: 100%;";
  body+=       "height: 500px;";
  body+=       "display:block;";
  body+=     "}";

  body+=  ".alert {";
  body+=    "padding: 20px;";
  body+=    "background-color: #33cc00;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".alert2 {";
  body+=    "padding: 20px;";
  body+=    "background-color: #ff3300;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".closebtn {";
  body+=    "margin-left: 15px;";
  body+=    "color: white;";
  body+=    "font-weight: bold;";
  body+=    "float: right;";
  body+=    "font-size: 22px;";
  body+=    "line-height: 20px;";
  body+=    "cursor: pointer;";
  body+=    "transition: 0.3s;";
  body+=  "}";

  body+=  ".closebtn:hover {";
  body+=    "color: black;";
  body+=  "}";   

  body +=    ".signout-part{";
  body+=       "position: fixed;";
  body+=       "top: 50px;";
  body+=       "left: 50px;";
  body+=       "width: 20%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body +=    "}";

  body+=  "</style>";
  body +=   "<body background=\"/shop.jpg\">";

  string cur_username = controller -> get_username(user_sid);

  body +=  "<div3 class = \"signout-part\">";
  body +=     "<img src=\"/user.png\" style=\"width:10%;\">";
  body +=     "<label for=\"signout\">  Hi " + cur_username + ", </label>";
  body +=     "<a href=\"/signout\" id = \"signout\">Signout</a>";
  body +=  "</div3>";

  body +=     "<div>";
  body +=       "<table class=\"w3-table w3-striped w3-bordered\"  style=\"overflow-y:scroll;height: 150px; display:block;\">";
  body +=        "<thead>";
  body +=         "<tr class=\"w3-red\">";

  for(int label_number = 0 ; label_number < labels.size() ; label_number++){
    body +=           "<th>" + labels[label_number] + "</th>";
  }

  body +=         "</tr>";
  body +=        "</thead>";

  body +=  "<tr class=\"w3-gray\">";

  for(int value_number = 0 ; value_number < values.size() ; value_number++){
      body +=     "<td>" + values[value_number] + "</td>";
  }
      body +=  "</tr>";
  body +=       "</table>";


  body +=     "<form action=\"/add_to_cart\" method=\"post\">";
  body +=       "<table class=\"w3-table w3-striped w3-bordered\"  style=\"overflow-y:scroll;height: 300px; width: 70%; display:block;\">";
  body +=        "<thead>";
  body +=         "<tr class=\"w3-red\">";

  for(int label_number = 0 ; label_number < offer_labels.size() ; label_number++){
    body +=           "<th>" + offer_labels[label_number] + "</th>";
  }

  body +=             "<th>Count</th>";
  body +=             "<th>Add to Cart</th>";

  body +=         "</tr>";
  body +=        "</thead>";

  string offer_id , offer_price , offer_amount;
  while(getline(ss2 , offer_id)){
      getline(ss2 , offer_price);
      getline(ss2 , offer_amount);
      body +=  "<tr class=\"w3-gray\">";
      body +=     "<td>" + offer_id + "</td>";
      body +=     "<td>" + offer_price + "</td>";
      body +=     "<td>" + offer_amount + "</td>";
      body +=     "<td><input name=\"amount" + offer_id +"\" type=\"number\" placeholder=\"0\" min = \"0\" max = \"" + offer_amount + "\"></td>";
      body +=     "<td><input type=\"submit\" value=\"Submit\"></td>";
      body +=  "</tr>";  
  }
  body +=       "</table>";
  body +=      "</form>";

  body +=     "</div>";
  body +=    "</html>";
  
  res -> setBody(body);
  res -> setSessionId(to_string(user_sid));
  return res;
}

Response* ShowProductHandler::callback(Request *req) {
  Response* res = new Response();

  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);

  string product_id = EMPTY;
  product_id = req -> getQueryParam("q");

  if(product_id == EMPTY)
    res = Response::redirect("/");
  else
    res = show_product_info_page(user_sid , product_id);

  res -> setSessionId(to_string(user_sid));
  return res;
}


Response* AddToCartHandler::callback(Request* req){
  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);

  for(int offer_id = 1 ; offer_id < MAX_OFFER_NUMBER ; offer_id++){
    string param_name = "amount" + to_string(offer_id);
    string cur_amount = req->getBodyParam(param_name);
    if(cur_amount != EMPTY){
      int amount = stoi(cur_amount);
      if(amount != 0)
        controller -> add_to_cart(user_sid , to_string(offer_id) , cur_amount , EMPTY);
    }
  }

  Response* res = Response::redirect("/");
  res -> setSessionId(to_string(user_sid));
  return res;
}

Response* WalletHandler::wallet_page(SID user_sid){
  Response* res = new Response();
  res->setHeader("Content-Type", "text/html");
  string body = EMPTY;

  double balance = controller -> get_wallet(user_sid);
  stringstream ss;
  ss << balance;
  string cur_balance;
  ss >> cur_balance;

  body+= "<!DOCTYPE html>";
  body+= "<html>";
  body+=    "<style>";

  body+=     ".button {";
  body+=        "position: fixed;";
  body+=        "top: 540px;";
  body+=        "left: 475px;";
  body+=        "font-weight: bold;";
  body+=         "background-color: #ff3300;";
  body+=         "width: 10%;";
  body+=         "color: white;";
  body+=         "padding: 14px 20px;";
  body+=         "margin: 8px 0;";
  body+=         "border: none;";
  body+=         "border-radius: 4px;";
  body+=         "cursor: pointer;";  
  body+=     "}";

  body+=     "input[type=text],[type=password],[type=number] {";
  body+=       "width: 45%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";
  body+=     "input[type=submit]{";
  body+=       "width: 80%;";
  body+=       "background-color: #33cc00;";
  body+=       "color: white;";
  body+=       "padding: 14px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "border: none;";
  body+=       "border-radius: 4px;";
  body+=       "cursor: pointer;";  
  body+=     "}";
  body+=     "body{";
  body+=       "text-align: center;";
  body+=     "}";
  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 280px;";
  body+=       "left: 400px;";
  body+=       "width: 20%;";
  body+=       "border-radius: 3px;";
  body+=       "background-color: #e6ac00;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}"; 
  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 210px;";
  body+=       "left: 425px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";
 
  body+=     "label {";
  body+=         "font-weight: bold;";
  body+=     "}";

  body+=    "p{";
  body+=          "font-size: 30px;";
  body+=    "}";

  body+=  ".alert {";
  body+=    "padding: 20px;";
  body+=    "background-color: #ff3300;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".closebtn {";
  body+=    "margin-left: 15px;";
  body+=    "color: white;";
  body+=    "font-weight: bold;";
  body+=    "float: right;";
  body+=    "font-size: 22px;";
  body+=    "line-height: 20px;";
  body+=    "cursor: pointer;";
  body+=    "transition: 0.3s;";
  body+=  "}";

  body+=  ".closebtn:hover {";
  body+=    "color: black;";
  body+=  "}";   

  body +=    ".signout-part{";
  body+=       "position: fixed;";
  body+=       "top: 50px;";
  body+=       "left: 50px;";
  body+=       "width: 20%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body +=    "}";

  body+=   "</style>";

  body+=   "<body background=\"/shop.jpg\">";

  string cur_username = controller -> get_username(user_sid);

  body +=  "<div3 class = \"signout-part\">";
  body +=     "<img src=\"/user.png\" style=\"width:10%;\">";
  body +=     "<label for=\"signout\">  Hi " + cur_username + ", </label>";
  body +=     "<a href=\"/signout\" id = \"signout\">Signout</a>";
  body +=  "</div3>";

  body+=    "<h1>Account Information</h1>";
  body+=    "<div>";
  body+=      "<form action=\"/charge_wallet\" method=\"post\">";
  body+=        "<p>Balance : " + cur_balance + "$</p>";
  body+=        "<label for=\"deposit\">Deposit : </label>";
  body+=        "<input name=\"deposit\" type=\"number\" placeholder=\"0\" min = \"0\" required>";
  body+=        "<input type=\"submit\" value=\"Submit\">";
  body+=      "</form>";
  body+=    "</div>";

  body +=           "<a href=\"/\" class=\"button\" style=\"text-decoration: none;\"> Home </a>";
  body +=           "<br />";

  body+=  "</body>";
  body+= "</html>";

  res -> setBody(body);

  return res;
}

Response* WalletHandler::callback(Request* req){
  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);

  Response* res = new Response();

  if(controller -> is_user_buyer(user_sid)){
    res = wallet_page(user_sid);
  }
  else{
    res = Response::redirect("/");
  }

  res -> setSessionId(to_string(user_sid));
  return res;
}


Response* ChargeWalletHandler::callback(Request* req){
  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  string deposit = req -> getBodyParam("deposit");
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);

  stringstream ss(deposit);
  double cur_deposit;
  ss >> cur_deposit;

  controller -> charge_wallet(user_sid , cur_deposit);

  Response* res = new Response();
  res = Response::redirect("/wallet");
  res -> setSessionId(to_string(user_sid));
  return res;  
}

Response* CartHandler::cart_page(Request* req , SID user_sid){
  Response* res = new Response();
  res->setHeader("Content-Type", "text/html");

  string body = EMPTY;  
  string sub_rep = EMPTY;

  sub_rep = req->getQueryParam("q");

  double balance = controller -> get_wallet(user_sid);
  stringstream ss2;
  ss2 << balance;
  string cur_balance;
  ss2 >> cur_balance;

  int total_price = 0;

  string cart = controller -> get_cart(user_sid);
  stringstream ss(cart);

  vector < string > labels = {"productId" , "productName" , "offerId" , "sellerId" , "totalPrice" , "amount"};

  body+= "<!DOCTYPE html>";
  body+= "<html>";
  body+= "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  body+= "<link rel=\"stylesheet\" href=\"https://www.w3schools.com/w3css/4/w3.css\">";

  body+=  "<style>";
  
  body+=     ".button {";
  body+=        "position: fixed;";
  body+=        "top: 590px;";
  body+=        "left: 540px;";
  body+=        "font-weight: bold;";
  body+=         "background-color: #ff3300;";
  body+=         "width: 10%;";
  body+=         "color: white;";
  body+=         "padding: 14px 20px;";
  body+=         "margin: 8px 0;";
  body+=         "border: none;";
  body+=         "border-radius: 4px;";
  body+=         "cursor: pointer;";  
  body+=     "}";

  body+=     "input[type=password] {";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";

  body+=     "input[type=text]{";
  body+=       "width: 50%;";
  body+=       "padding: 12px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "display: inline-block;";
  body+=       "border: 1px solid #ccc;";
  body+=       "border-radius: 4px;";
  body+=       "box-sizing: border-box;";
  body+=     "}";


  body+=     "input[type=submit]{";
  body+=       "width: 80%;";
  body+=       "background-color: #33cc00;";
  body+=       "color: white;";
  body+=       "padding: 14px 20px;";
  body+=       "margin: 8px 0;";
  body+=       "border: none;";
  body+=       "border-radius: 4px;";
  body+=       "cursor: pointer;";  
  body+=     "}";


  body+=     "div {";
  body+=       "position: fixed;";
  body+=       "top: 100px;";
  body+=       "left: 0px;";
  body+=       "width: 55%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body+=     "}";

  body+=     "h1 {";
  body+=       "position: fixed;";
  body+=       "top: 170px;";
  body+=       "left: 550px;";
  body+=       "color: #000000;";
  body+=       "text-align: center;";
  body+=     "}";

  body+=     "div2 {";
  body+=           "background-color: #e6ac00;";
  body+=           "position: fixed;";
  body+=           "left: 50px;";
  body+=           "width: 30%;";
  body+=           "height: 200;";
  body+=           "border-radius: 1px;";
  body+=           "margin: auto;" ;
  body+=     "}";

  body+=     "body{";
  body+=       "text-align: center;";
  body+=     "}";

  body+=     "table{";
  body+=       "overflow-y:scroll;";
  body+=       "width: 100%;";
  body+=       "height: 500px;";
  body+=       "display:block;";
  body+=     "}";

  body+=  ".alert {";
  body+=    "padding: 20px;";
  body+=    "background-color: #33cc00;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".alert2 {";
  body+=    "padding: 20px;";
  body+=    "background-color: #ff3300;";
  body+=    "color: white;";
  body+=    "margin-bottom: 15px;";
  body+=  "}";

  body+=  ".closebtn {";
  body+=    "margin-left: 15px;";
  body+=    "color: white;";
  body+=    "font-weight: bold;";
  body+=    "float: right;";
  body+=    "font-size: 22px;";
  body+=    "line-height: 20px;";
  body+=    "cursor: pointer;";
  body+=    "transition: 0.3s;";
  body+=  "}";

  body+=  ".closebtn:hover {";
  body+=    "color: black;";
  body+=  "}";   

  body+=    "p{";
  body+=          "font-size: 30px;";
  body+=    "}";

  body +=    ".signout-part{";
  body+=       "position: fixed;";
  body+=       "top: 50px;";
  body+=       "left: 50px;";
  body+=       "width: 20%;";
  body+=       "border-radius: 3px;";
  body+=       "padding: 20px;";
  body+=       "margin: auto;" ;
  body +=    "}";

  body+=  "</style>";
  body +=   "<body background=\"/shop.jpg\">";

  string cur_username = controller -> get_username(user_sid);

  body +=  "<div3 class = \"signout-part\">";
  body +=     "<img src=\"/user.png\" style=\"width:10%;\">";
  body +=     "<label for=\"signout\">  Hi " + cur_username + ", </label>";
  body +=     "<a href=\"/signout\" id = \"signout\">Signout</a>";
  body +=  "</div3>";

  body +=     "<div>";
  body +=       "<table class=\"w3-table w3-striped w3-bordered\"  style=\"overflow-y:scroll;height: 300px; display:block;\">";
  body +=        "<thead>";
  body +=         "<tr class=\"w3-red\">";

  for(int label_number = 0 ; label_number < labels.size() ; label_number++){
    body +=           "<th>" + labels[label_number] + "</th>";
  }

  body +=         "</tr>";
  body +=        "</thead>";

  string cur_product_id , cur_product_name , cur_offer_id , cur_seller_id , price , amount;
  while(getline(ss , cur_product_id)){
      getline(ss , cur_product_name);
      getline(ss , cur_offer_id);
      getline(ss , cur_seller_id);
      getline(ss , price);
      getline(ss , amount);

      total_price += stoi(price);

      body +=  "<tr class=\"w3-gray\">";
      body +=     "<td>" + cur_product_id + "</td>";
      body +=     "<td>" + cur_product_name + "</td>";
      body +=     "<td>" + cur_offer_id + "</td>";
      body +=     "<td>" + cur_seller_id + "</td>";
      body +=     "<td>" + price + "</td>";
      body +=     "<td>" + amount + "</td>";
      body +=  "</tr>";
  }
  body +=       "</table>";


  body+=     "<div2>";
  if(sub_rep == OK){
    body+=          "<div2 class=\"alert\">";
    body+=             "<span class=\"closebtn\" onclick=\"this.parentElement.style.display='none';\">&times;</span>";
    body+=             SUB_DONE_MESSAGE;
    body+=          "</div2>""<br/>";
  }
  else if(sub_rep == BAD){
    body+=          "<div2 class=\"alert2\">";
    body+=             "<span class=\"closebtn\" onclick=\"this.parentElement.style.display='none';\">&times;</span>";
    body+=             SUB_ERROR_MESSAGE;
    body+=          "</div2>""<br/>";    
  }

  body+=      "<form action=\"/submit_cart\" method=\"post\">";
  body+=        "<p name=\"balance\">Balance : " + cur_balance + "$</p>";
  body+=        "<p name=\"total\">Total Price : " + to_string(total_price) + "$</p>";
  body+=        "<input type=\"submit\" value=\"Submit Cart\">";
  body+=      "</form>";  
  body+=     "</div2>";

  body +=           "<a href=\"/\" class=\"button\" style=\"text-decoration: none;\"> Home </a>";
  body +=           "<br />";

  body +=     "</div>";
  body +=   "</html>";

  res->setBody(body);

  return res;
}

Response* CartHandler::callback(Request* req){
  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);

  Response* res = new Response();

  if(controller -> is_user_buyer(user_sid)){
    res = cart_page(req , user_sid);
  }
  else{
    res = Response::redirect("/");
  }
  res -> setSessionId(to_string(user_sid));
  return res;  
}

Response* SubmitCartHandler::callback(Request* req){
  SID user_sid = NO_SID;
  string cur_sid = req -> getSessionId();
  if(cur_sid != EMPTY)
    user_sid = stoi(cur_sid);

  Response* res = new Response();

  string submit_report = controller -> submit_cart(user_sid);
  cout << submit_report << endl;

  if(submit_report == OK)
    res = Response::redirect("/cart?q=1");
  else
    res = Response::redirect("/cart?q=0");
  res -> setSessionId(to_string(user_sid));
  return res;  

}

Response *UploadHandler::callback(Request *req) {
  string name = req->getBodyParam("file_name");
  string file = req->getBodyParam("file");
  cout << name << " (" << file.size() << "B):\n" << file << endl;
  Response *res = Response::redirect("/");
  return res;
}

ColorHandler::ColorHandler(string filePath) : TemplateHandler(filePath) {}

map<string, string> ColorHandler::handle(Request *req) {
  map<string, string> context;
  string newName = "I am " + req->getQueryParam("name");
  context["name"] = newName;
  context["color"] = req->getQueryParam("color");
  return context;
}
