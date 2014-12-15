#ifndef TO_STRING_HPP
#define TO_STRING_HPP

#include <string>
#include <sstream>

template<typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#endif
