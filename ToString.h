#pragma once
#include <string>
template<class T> std::string to_string(T type);
template<> std::string to_string(int type) { return "INT "; };
template<> std::string to_string(double type) { return "DOUBLE "; };
template<> std::string to_string(std::string type) { return "STRING "; };
template<> std::string to_string(bool type) { return "BOOL "; };

