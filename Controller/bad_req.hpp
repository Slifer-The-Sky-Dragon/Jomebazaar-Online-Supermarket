#ifndef _BAD_REQ
#define _BAD_REQ

#include <exception>

class Bad_request : public std::exception {
public:
	const char* what() const throw() {
		return "Bad Request\n";
	}
};

#endif