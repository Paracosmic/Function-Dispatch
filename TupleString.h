#pragma once
#include <string>

class TupleString {
public:
	template<class T> static std::string to_string(T type);
	template<> static std::string to_string(int type) { return "INT "; };
	template<> static std::string to_string(double type) { return "DOUBLE "; };
	template<> static std::string to_string(std::string type) { return "STRING "; };
	template<> static std::string to_string(bool type) { return "BOOL "; };
	template<> static std::string to_string(float type) { return "FLOAT "; };
	template <typename T>
	static bool IsString(T var) { return false; };

	template<>
	static bool IsString(std::string var) { return true; };

	template<>
	static bool IsString(const char* var) { return true; };

	template<class...Ts, std::size_t...Is>
	static bool is_tuple_string(std::tuple<Ts...> & tuple, std::index_sequence<Is...>) {
		bool is_true = true;
		using expander = int[];
		expander{
			0, (is_true = is_true && IsString(std::get<Is>(tuple)) , 0)...
		};
		return is_true;
	}

	template<class...Ts>
	static bool is_tuple_string(std::tuple<Ts...> & tuple) {
		return is_tuple_string(tuple, std::make_index_sequence<sizeof...(Ts)>());
	}
};