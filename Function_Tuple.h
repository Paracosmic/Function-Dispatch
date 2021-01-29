#pragma once
#include <type_traits>
#include <tuple>
#include <vector>
#include <string>
#include "TransformArgument.h"
class FunctionTuple {
public:
	template<typename F, typename Tuple, size_t ...S >
	static decltype(auto) apply_tuple_impl(F&& fn, Tuple&& t, std::index_sequence<S...>)
	{
		auto f = std::forward<F>(fn);
		return f(std::get<S>(std::forward<Tuple>(t))...);
	}
	template<typename F, typename Tuple>
	static decltype(auto) apply_from_tuple(F&& fn, Tuple&& t)
	{

		std::size_t constexpr tSize
			= std::tuple_size<typename std::remove_reference<Tuple>::type>::value;


		return apply_tuple_impl(std::forward<F>(fn),
			std::forward<Tuple>(t),
			std::make_index_sequence<tSize>());
	}

	template<typename F, typename C, typename Tuple, size_t ...S >
	static decltype(auto) apply_from_tuple_impl(C& c, F&& fn, Tuple&& t, std::index_sequence<S...>)
	{
		auto f = std::forward<F>(fn);
		auto tup = std::forward<Tuple>(t);

		//auto cl = std::forward<C>(c);

		return (c.*f)(std::get<S>(tup)...);
	}



	template<typename R, typename C, typename CC, typename Tuple, typename... Args >
	static decltype(auto) apply_from_tuple(CC& c, R(C::*fn)(Args...), Tuple&& t)
	{
		std::size_t constexpr tSize
			= std::tuple_size<typename std::remove_reference<Tuple>::type>::value;

		return apply_from_tuple_impl(
			c,
			std::forward<R(C::*)(Args...)>(fn),
			std::forward<Tuple>(t),
			std::make_index_sequence<tSize>());
	}





	////////////////////////////////converts a function parameters to tuple
	template <typename R, typename... T>
	static std::tuple<T...> function_args(R(*)(T...))
	{
		return std::tuple<T...>();
	}
	//w
	template <typename R, typename... T>
	static std::tuple<T...> function_args_w(R(*)(T...))
	{
		return std::tuple<T...>();
	}
	template <typename C, typename R, typename... T>
	static std::tuple<T...>  function_args_w(R(C::*)(T...))
	{
		return std::tuple<T...>();
		// std::tuple<T...>();
	}
	//w
	template <typename... Args, std::size_t... Is>
	static auto create_tuple_impl(std::index_sequence<Is...>, const std::vector<std::string>& arguments) {
		return std::make_tuple(ArgumentUtil::transform_arg<Args>(arguments[Is])...);
	}

	template <typename... Args>
	static auto create_tuple(const std::vector<std::string>& arguments) {
		return create_tuple_impl<Args...>(std::index_sequence_for<Args...>{ }, arguments);
	}

	//static
	template <typename R, typename... T>
static	std::tuple<T...>  function_args(const std::vector<std::string>& arguments, R(*)(T...))
	{


		return create_tuple < T... >(arguments);
		// std::tuple<T...>();
	}
	//member function
	template <typename C, typename R, typename... T>
	static std::tuple<T...>  function_args(const std::vector<std::string>& arguments, R(C::*)(T...))
	{
		return create_tuple < T... >(arguments);
		// std::tuple<T...>();
	}


	template<class...Ts, std::size_t...Is>
	static void print_for_each(const std::tuple<Ts...> & tuple, std::index_sequence<Is...>) {
		using expander = int[];
		expander{
			0, (std::cout << TupleString::to_string(std::get<Is>(tuple)) , 0)...
		};
	}

	template<class...Ts>
	static void print_for_each(const std::tuple<Ts...> & tuple) {
		print_for_each(tuple, std::make_index_sequence<sizeof...(Ts)>());
	}
	///

	template<class...Ts, std::size_t...Is>
	static void to_string_for_each(const std::tuple<Ts...> & tuple, std::index_sequence<Is...>, std::string& out) {
		using expander = int[];
		expander{
			0, (out.append(TupleString::to_string(std::get<Is>(tuple))) , 0)...
		};
	}

	template<class...Ts>
	static void to_string_for_each(const std::tuple<Ts...> & tuple, std::string& out) {
		to_string_for_each(tuple, std::make_index_sequence<sizeof...(Ts)>(), out);
	}
	///
	///
	template<class...Ts, std::size_t...Is>
	static void token_for_each(const std::tuple<Ts...> & tuple, std::index_sequence<Is...>, std::vector<std::string>& out) {
		using expander = int[];
		expander{
			0, (out.push_back(TupleString::to_string(std::get<Is>(tuple))) , 0)...
		};
	}

	template<class...Ts>
	static void token_for_each(const std::tuple<Ts...> & tuple, std::vector<std::string>& out) {
		token_for_each(tuple, std::make_index_sequence<sizeof...(Ts)>(), out);
	}
	///

	//^1
	template<class...Ts, std::size_t...Is>
	static void generate_for_each(std::tuple<Ts...> & tuple, std::index_sequence<Is...>) {
		using expander = int[];
		expander{
			0, (std::get<Is>(tuple) = ArgumentUtil::generate_input(std::get<Is>(tuple)) , 0)...
		};
	}

	template<class...Ts>
	static void generate_for_each(std::tuple<Ts...> & tuple) {
		generate_for_each(tuple, std::make_index_sequence<sizeof...(Ts)>());
	}
	//^2


};