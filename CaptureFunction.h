#pragma once
#include <string>
#include <tuple>
#include <vector>
#include "MetaFunction.h"
#include "FunctionHandle.h"


//template< typename F, typename... Args>
//size_t CaptureFuction(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, F f)
//{
//	return CaptureFuction_impl(function_container, name, f);
//};
//
//template< typename CC, typename F, typename... Args>
//size_t CaptureFuction(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, CC& c, F f)
//{
//	
//	return CaptureFuction_impl(function_container, name, c, f);
//};
//
//
//template< typename R, typename... Args>
//size_t CaptureFuction_impl(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, R(*ptr)(Args...))
//{
//	auto f = new MetaStaticFunctionData< R, Args...>;
//	f->FPtr = ptr;
//	function_container.emplace_back(std::move(f));
//
//	size_t index = function_container.size() - 1;
//
//	function_container[index]->function_name = name;
//	//function_container[index]->FPtr = ptr;
//	function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;
//
//	return index;
//};
//
////template<typename R, typename C, typename... Args>
////size_t CaptureFuction_impl(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, R(C::*ptr)(Args...))
////{
////	auto f = new MetaFunctionData< R, C, Args...>;
////	f->FPtr = ptr;
////	function_container.emplace_back(std::move(f));
////
////	size_t index = function_container.size() - 1;
////
////	function_container[index]->function_name = name;
////	//	function_container[index]->FPtr = ptr;
////	function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;
////
////	return index;
////};
//
//template<typename R, typename C, typename CC, typename... Args>
//size_t CaptureFuction_impl(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, CC& c, R(C::*ptr)(Args...))
//{
//	auto f = new MetaFunctionData< R, C, Args...>;
//	f->FPtr = ptr;
//	function_container.emplace_back(std::move(f));
//
//	size_t index = function_container.size() - 1;
//
//	function_container[index]->function_name = name;
//
//	//function_container[index]->FPtr = ptr;
//	function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;
//	//	std::cout << std::tuple_size<std::tuple<Args...>>::value << "  ";
//		//std::cout << sizeof(Args) << "  \n";
//	//	std::cout << sizeof(...) <<"\n";
//
//	return index;
//};
//
////
//
//template< typename R, typename... Args>
//size_t ReflectFuction_impl(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, R(*ptr)(Args...), const std::vector<std::string>& parameter_info)
//{
//	auto f = new MetaStaticFunctionData< R, Args...>;
//	f->FPtr = ptr;
//	function_container.emplace_back(std::move(f));
//
//	size_t index = function_container.size() - 1;
//
//	function_container[index]->function_name = name;
//	//function_container[index]->FPtr = ptr;
//	function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;
//
//	function_container[index]->Parameter_Info = parameter_info;
//
//	return index;
//};
//
//
//template<typename R, typename C, typename CC, typename... Args>
//size_t ReflectFuction_impl(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, CC& c, R(C::*ptr)(Args...), const std::vector<std::string>& parameter_info)
//{
//	auto f = new MetaFunctionData< R, C, Args...>;
//	f->FPtr = ptr;
//	function_container.emplace_back(std::move(f));
//
//	size_t index = function_container.size() - 1;
//
//	function_container[index]->function_name = name;
//
//	//function_container[index]->FPtr = ptr;
//	function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;
//
//	function_container[index]->Parameter_Info = parameter_info;
//	//	std::cout << std::tuple_size<std::tuple<Args...>>::value << "  ";
//		//std::cout << sizeof(Args) << "  \n";
//	//	std::cout << sizeof(...) <<"\n";
//
//	return index;
//};
//
//
////
//
//
//template< typename F, typename... Args>
//FunctionHandle CaptureFuctionH(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, F f)
//{
//	return CaptureFuction_implH(function_container, name, f);
//};
//
//template< typename CC, typename F, typename... Args>
//FunctionHandle CaptureFuctionH(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, CC& c, F f)
//{
//
//	return CaptureFuction_implH(function_container, name, c, f);
//};
//
//template< typename R, typename... Args>
//FunctionHandle CaptureFuction_implH(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, R(*ptr)(Args...))
//{
//	auto f = new MetaStaticFunctionData< R, Args...>;
//	f->FPtr = ptr;
//	//function_container.emplace_back(std::move(f));
//
//	//size_t index = function_container.size() - 1;
//
//	//function_container[index]->function_name = name;
//	////function_container[index]->FPtr = ptr;
//	//function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;
//
//	return *f;
//};
//
//template<typename R, typename C, typename... Args>
//FunctionHandle CaptureFuction_implH(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, R(C::*ptr)(Args...))
//{
//	auto f = new MetaFunctionData< R, C, Args...>;
//	f->FPtr = ptr;
//	//function_container.emplace_back(std::move(f));
//
//	//size_t index = function_container.size() - 1;
//
//	//function_container[index]->function_name = name;
//	////	function_container[index]->FPtr = ptr;
//	//function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;
//
//	return *f;
//};
//
//template<typename R, typename C, typename CC, typename... Args>
//FunctionHandle CaptureFuction_implH(std::vector<std::unique_ptr<FunctionHandle>>& function_container, std::string name, CC& c, R(C::*ptr)(Args...))
//{
//	auto f = new MetaFunctionData< R, C, Args...>;
//	f->FPtr = ptr;
//	//function_container.emplace_back(std::move(f));
//
//	//size_t index = function_container.size() - 1;
//
//	//function_container[index]->function_name = name;
//
//	//function_container[index]->FPtr = ptr;
//	//function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;
//	//	std::cout << std::tuple_size<std::tuple<Args...>>::value << "  ";
//		//std::cout << sizeof(Args) << "  \n";
//	//	std::cout << sizeof(...) <<"\n";
//
//	return *f;
//};
//
//
//
//
//
