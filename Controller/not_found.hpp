#ifndef _NOT_FOUND_HPP
#define _NOT_FOUND_HPP

#include <exception>

class Not_found : public std::exception {
public:
	const char* what() const throw() {
		return "Not Found\n";
	}
};


#endif