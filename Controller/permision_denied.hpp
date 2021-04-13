#ifndef _PERMISION_DENIED_HPP
#define _PERMISION_DENIED_HPP

#include <exception>

class Permision_denied : public std::exception {
public:
	const char* what() const throw() {
		return "Permission Denied\n";
	}
};


#endif