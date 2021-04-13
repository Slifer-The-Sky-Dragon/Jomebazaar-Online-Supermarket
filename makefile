CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp Controller/controller.cpp Controller/controller.hpp Controller/bad_req.hpp Controller/permision_denied.hpp
	$(CC) $(CF) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/product.o: Controller/product.cpp Controller/product.hpp Controller/user.hpp
	$(CC) $(CF) -c Controller/product.cpp -o $(BUILD_DIR)/product.o

$(BUILD_DIR)/mobile.o: Controller/mobile.cpp Controller/mobile.hpp Controller/product.hpp Controller/bad_req.hpp
	$(CC) $(CF) -c Controller/mobile.cpp -o $(BUILD_DIR)/mobile.o

$(BUILD_DIR)/car.o: Controller/car.cpp Controller/car.hpp Controller/product.hpp Controller/bad_req.hpp
	$(CC) $(CF) -c Controller/car.cpp -o $(BUILD_DIR)/car.o

$(BUILD_DIR)/tv.o: Controller/tv.cpp Controller/tv.hpp Controller/product.hpp Controller/bad_req.hpp
	$(CC) $(CF) -c Controller/tv.cpp -o $(BUILD_DIR)/tv.o

$(BUILD_DIR)/user.o: Controller/user.cpp Controller/user.hpp Controller/bad_req.hpp
	$(CC) $(CF) -c Controller/user.cpp -o $(BUILD_DIR)/user.o

$(BUILD_DIR)/buyer.o: Controller/buyer.cpp Controller/buyer.hpp Controller/user.hpp Controller/user.cpp Controller/offer.hpp Controller/offer.cpp Controller/order.hpp Controller/order.cpp Controller/bad_req.hpp Controller/not_found.hpp
	$(CC) $(CF) -c Controller/buyer.cpp -o $(BUILD_DIR)/buyer.o

$(BUILD_DIR)/controller.o: Controller/controller.cpp Controller/controller.hpp Controller/user.hpp Controller/user.cpp Controller/offer.hpp Controller/offer.cpp Controller/shop.hpp Controller/shop.cpp Controller/buyer.hpp Controller/buyer.cpp Controller/seller.hpp Controller/bad_req.hpp Controller/permision_denied.hpp
	$(CC) $(CF) -c Controller/controller.cpp -o $(BUILD_DIR)/controller.o

$(BUILD_DIR)/offer.o: Controller/offer.cpp Controller/offer.hpp Controller/user.hpp Controller/user.cpp Controller/product.hpp Controller/product.cpp Controller/seller.hpp
	$(CC) $(CF) -c Controller/offer.cpp -o $(BUILD_DIR)/offer.o

$(BUILD_DIR)/order.o: Controller/order.cpp Controller/order.hpp Controller/product.hpp Controller/product.cpp Controller/offer.hpp Controller/offer.cpp
	$(CC) $(CF) -c Controller/order.cpp -o $(BUILD_DIR)/order.o

$(BUILD_DIR)/shop.o: Controller/shop.cpp Controller/shop.hpp Controller/product.hpp Controller/product.cpp Controller/mobile.hpp Controller/mobile.cpp Controller/car.hpp Controller/car.cpp Controller/tv.hpp Controller/tv.cpp Controller/offer.hpp Controller/offer.cpp Controller/user.hpp Controller/user.cpp Controller/buyer.hpp Controller/buyer.cpp Controller/order.hpp Controller/order.cpp Controller/seller.hpp
	$(CC) $(CF) -c Controller/shop.cpp -o $(BUILD_DIR)/shop.o

$(BUILD_DIR)/main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp Controller/controller.cpp Controller/controller.hpp Controller/shop.cpp Controller/shop.hpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/product.o $(BUILD_DIR)/mobile.o $(BUILD_DIR)/car.o $(BUILD_DIR)/tv.o $(BUILD_DIR)/user.o $(BUILD_DIR)/buyer.o $(BUILD_DIR)/controller.o $(BUILD_DIR)/offer.o $(BUILD_DIR)/order.o $(BUILD_DIR)/shop.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/product.o $(BUILD_DIR)/mobile.o $(BUILD_DIR)/car.o $(BUILD_DIR)/tv.o $(BUILD_DIR)/user.o $(BUILD_DIR)/buyer.o $(BUILD_DIR)/controller.o $(BUILD_DIR)/offer.o $(BUILD_DIR)/order.o $(BUILD_DIR)/shop.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
