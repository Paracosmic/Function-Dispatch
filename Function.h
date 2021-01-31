#pragma once
#include <map>
#include <vector>
#include <tuple>
#include <string>
#include "MetaFunction.h"
#include "FunctionHandle.h"
#include "VirtualVariable.h"

class VirtualFunctionUtility
{
public:

	std::vector<std::shared_ptr<FunctionHandle>> function_container;
	std::map<std::string, std::shared_ptr<FunctionHandle>> function_map;
	VirtualFunctionUtility(IntMap& maptest) : imap(maptest){};

	bool find(std::string& name);

	IntMap& imap;




	template< typename F, typename... Args>
	size_t Reflect_Static_Function(std::string name, F f, const std::vector<std::string>& parameter_info = {})
	{

		return Reflect_Static_Function_impl(function_container, name, f, parameter_info);

	};

	template< typename CC, typename F, typename... Args>
	size_t Reflect_Member_Function(std::string name, CC& c, F f, const std::vector<std::string>& parameter_info = {})
	{
		return Reflect_Member_Function_impl(function_container, name, c, f, parameter_info);
	};



	template< typename R, typename... Args>
	size_t Reflect_Static_Function_impl(std::vector<std::shared_ptr<FunctionHandle>>& function_container, std::string name, R(*ptr)(Args...), const std::vector<std::string>& parameter_info)
	{
		//TODO PROPERLY HANDLE DELETION
		auto f = new MetaStaticFunctionData< R, Args...>;
		f->FPtr = ptr;
		function_container.emplace_back(std::move(f));

		size_t index = function_container.size() - 1;

		function_container[index]->function_name = name;
		//function_container[index]->FPtr = ptr;
		function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;

		function_container[index]->Parameter_Info = parameter_info;


		function_map[name] = function_container[index];
		//shared_function_container.emplace_back(std::move(*itr));
		return index;
	};


	template<typename R, typename CC, typename... Args>
	size_t Reflect_Member_Function_impl(std::vector<std::shared_ptr<FunctionHandle>>& function_container, std::string name, CC& c, R(CC::* ptr)(Args...), const std::vector<std::string>& parameter_info)
	{
		//TODO PROPERLY HANDLE DELETION
		auto f = new MetaFunctionData< R, CC, Args...>;
		f->FPtr = ptr;
		function_container.emplace_back(std::move(f));

		size_t index = function_container.size() - 1;

		function_container[index]->function_name = name;

		//function_container[index]->FPtr = ptr;
		function_container[index]->parameter_count = std::tuple_size<std::tuple<Args...>>::value;

		function_container[index]->Parameter_Info = parameter_info;
		//	std::cout << std::tuple_size<std::tuple<Args...>>::value << "  ";
			//std::cout << sizeof(Args) << "  \n";
		//	std::cout << sizeof(...) <<"\n";
		function_map[name] = function_container[index];


		BindClass(&c, sizeof(c), name);


		return index;
	};



	void PrintFunctions();

	//binds the class object to the virtualized member function
	void BindClass(void * ptr, size_t size, std::string function_name);


	template <typename... T>
	const void operator()(const std::string& function_name, const T&... args)
	{

		function_map[function_name]->ParseInput(args...);

	};


	template <typename... T>
	const void Call(const std::string& function_name, const T&... args)
	{

		function_map[function_name]->ParseInput(args...);

	};


	//TODO move or find a more generic function
	std::vector<std::string> Tokenize(std::string line)
	{
		std::vector<std::string> tokens;
		std::string token = "";
		for (auto& chr : line)
		{
			if (chr != ' ')
			{
				//	token.append(std::string(&chr));
				token.push_back(chr);
				//	token.append(&chr);
			}
			else {

				tokens.push_back(token);
				token = "";

			}
		}

		tokens.push_back(token);

		return tokens;

	};
	

	void FindAndReplaceVirtualVariables(std::vector<std::string>& tokens)
	{
		//check each token
		for (auto& token : tokens)
		{
			//is a virtual variable
			if (token[0] == '$')
			{
				std::string var_name = token.substr(1,token.size());
				token = std::to_string(**imap.Map[var_name]);
				int i = **imap.Map[var_name];


			}
		}
	
	}
	//deprecated
	const void Execute(const std::string& command)
	{
		std::vector<std::string> tokens = Tokenize(command);
		std::string name = tokens[0];
		tokens.erase(tokens.begin());
		function_map[name]->CallFunction(tokens);

	};
	/*
	ret : true if executed, false if invalid
	param0 : name of function
	param1 : outbound error message
	*/
	const bool TryExecute(const std::string& command, std::string& out_log)
	{

		//First break the string up into tokens 
		std::vector<std::string> tokens = Tokenize(command);

		//token[0] is standard for the function name
		//store this in a string for later
		std::string name = tokens[0];

		//erase token[0] as it is no longer needed as a token
		tokens.erase(tokens.begin());

		//look for the function
		auto found = function_map.find(name);


		//function found, set parameters
		if (found != function_map.end())
		{

			//Call the function 
			function_map[name]->CallFunction(tokens);
			//return true since it was properly executed 
			return true;
		}
		else if (found == function_map.end())
		{

			std::string errout = name; errout.append(" is an invalid function.");
			out_log.append(errout);

		}
		return false;
	};

	/*
	ret : true if executed, false if invalid
	 param0 : name of function
	Uses std::cout to log errors
	*/
	const bool TryExecute(const std::string& command)
	{
		//First break the string up into tokens 
		std::vector<std::string> tokens = Tokenize(command);

		FindAndReplaceVirtualVariables(tokens);
		
		//token[0] is standard for the function name
		//store this in a string for later
		std::string name = tokens[0];

		//erase token[0] as it is no longer needed as a token
		tokens.erase(tokens.begin());

		//look for the function
		auto found = function_map.find(name);


		//function found, set parameters
		if (found != function_map.end())
		{

			//Call the function 
			function_map[name]->CallFunction(tokens);
			//return true since it was properly executed 
			return true;
		}
		else if (found == function_map.end())
		{

			std::string errout = name; errout.append(" is an invalid function.");
			std::cout << errout;
		}
		return false;
	};

};
