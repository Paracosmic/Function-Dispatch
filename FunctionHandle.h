#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <tuple>
#include "Function_Tuple.h"
#include "TupleString.h"

class FunctionHandle
{
public:
	std::string function_name = "null";
	
	std::string GetFName() { return function_name; };
	void SetFName(std::string name) { function_name = name; };

	std::vector<std::string> str_parameter;

	std::vector<std::string> Parameter_Info;


	size_t parameter_count = 0;
	//SMELLY
	void* void_class_ptr = nullptr;

	size_t class_size = 0;
	virtual void CallFunction();
	virtual void CallFunction(const std::vector<std::string>& str_param);
	virtual void CallFunctionWithCachedArguments();
	virtual void SetArgs(std::string args);

	template<typename... T>
	const void ParseInput(T... A)
	{

		const size_t count = std::tuple_size<std::tuple<T...>>::value;
		if (count == parameter_count)
		{

			std::tuple<T...> tuple;
			//anything other than a tuple of std::string is undefined
			if (TupleString::is_tuple_string(tuple))
			{
				
				str_parameter = { A... };
			}
			else 
			{
			
				std::cout << "Invalid Input! You need strings!" << "\n";
			
			};

			//[x]valid number of parameters
			//[x]all are string
			//[?]all conversions succesful? 
			//TryInput()
			CallFunction();

		}
		else
		{

			std::cout << "Expected " << parameter_count << " parameters, found "
				<< count << "\n";
		}

	}

	template <typename... T>
	void SetArguments()
	{
		FunctionTuple::apply_from_tuple(FPtr, arguments);

	}

	template<typename... T>
	void operator()(T... A)
	{
		ParseInput(A...);
	}


	void SetClass(void* ptr, size_t size);

	virtual void PrintFunction();

	virtual void GenerateInput();
	virtual void SetFirstParam();
	virtual std::string ToString();
	//TODO move or find a more generic function
	std::vector<std::string> Tokenize(std::string line)
	{
		bool is_string = false;
		std::vector<std::string> tokens;
		std::string token = "";
		for (auto& chr : line)
		{
			if (chr == '"') {
				is_string = !is_string;
				//continue;
			}

			if (!is_string)
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
			else
			{

				token.push_back(chr);

			}

		}

		tokens.push_back(token);

		return tokens;

	};

	virtual size_t ParameterCount();
};

template<typename R, typename... Args>
class MetaStaticFunctionData : public FunctionHandle
{
public:
	R(*function_pointer)(Args...);
	std::tuple<Args...> arguments;


	//	R return_value;



	void SetArgs(std::string args) override 
	{
		arguments = FunctionTuple::function_args(Tokenize(args), function_pointer);
	}
	 std::string ToString() override
	{
		std::string out = function_name;
		out.append(" : ");
		std::vector<std::string> tokens; 
		FunctionTuple::token_for_each(arguments, tokens);

		if (ParameterCount() == 0)
		{
			out.append("NO_PARAMETERS");
		}
		if (Parameter_Info.size() == tokens.size())
		{
			

			for (int i = 0; i < tokens.size(); ++i)
			{
				out.append("<").append(tokens[i]).append("").append(Parameter_Info[i]).append("> ");

			}


			return  out;
		}



	

		FunctionTuple::to_string_for_each(arguments, out);

		return  out;
	};

	void CallFunctionWithCachedArguments() override 
	{
		FunctionTuple::apply_from_tuple(function_pointer, arguments);
	
	}


	void CallFunction() override
	{

		if (std::tuple_size<std::tuple<Args...>>::value == str_parameter.size())
		{
			//populate a tuple of f function parameters from a vector of parameters
			//note: parameter types must match when converted from string
			arguments = FunctionTuple::function_args(str_parameter, function_pointer);

			FunctionTuple::apply_from_tuple(function_pointer, arguments);
		}
		else
		{
			std::cout << "Expected " << std::tuple_size<std::tuple<Args...>>::value << " parameters, found "
				<< str_parameter.size() << "\n";
		}
	};


	void CallFunction(const std::vector<std::string>& str_param) override
	{

		if (std::tuple_size<std::tuple<Args...>>::value == str_param.size())
		{
			//populate a tuple of f function parameters from a vector of parameters
			//note: parameter types must match when converted from string
			arguments = FunctionTuple::function_args(str_param, function_pointer);
			FunctionTuple::apply_from_tuple(function_pointer, arguments);
		}
		else
		{
			std::cout << "Expected " << std::tuple_size<std::tuple<Args...>>::value << " parameters, found "
				<< str_parameter.size() << "\n";
		}
	};


	void SetArguments(Args... args)
	{
		arguments = std::make_tuple(args...);

	};

	R operator()(std::tuple<Args...> args)
	{
		return apply_from_tuple(function_pointer, args);
	};


	R operator()(Args... args)
	{
		return (*function_pointer)(args...);
	};

	void PrintFunction() override
	{
		std::cout << ToString() << "\n";

	};

	size_t ParameterCount() override 
	{
		return std::tuple_size<	std::tuple<Args...>>();
	};
};

template<typename R, typename CC, typename... Args>
class MetaFunctionData : public FunctionHandle
{
public:
	R(CC::*function_pointer)(Args...);
	std::tuple<Args...> arguments;
	//R return_value;
	CC* class_object = nullptr;
	MetaFunctionData()

	{
		class_size = sizeof(CC);
	};

	void SetArgs(std::string args) override
	{
		arguments = FunctionTuple::function_args(Tokenize(args), function_pointer);
	}
	std::string ToString() override
	{
		std::string out = function_name;
		out.append(" : ");
		std::vector<std::string> tokens;
		FunctionTuple::token_for_each(arguments, tokens);


		if (ParameterCount() == 0)
		{
			out.append("NO_PARAMETERS");
		}


		if (Parameter_Info.size() == tokens.size())
		{


			for (int i = 0; i < tokens.size(); ++i)
			{
				out.append("<").append(tokens[i]).append("").append(Parameter_Info[i]).append("> ");

			}


			return  out;
		}





		FunctionTuple::to_string_for_each(arguments, out);
		return  out;
	};



	void TryVoidPointer(std::tuple<Args...> args)
	{
		if (void_class_ptr != nullptr)
		{

			CC* ptr = static_cast<CC*>(void_class_ptr);

			if (ptr != nullptr) {
				FunctionTuple::apply_from_tuple(*ptr, function_pointer, args);
			}
		}
	}

	void CallFunctionWithCachedArguments() override 
	{
		//TODO only need to do this once after each time you bind a member function to its owning class
		TryVoidPointer(arguments);
	}

	void CallFunction() override
	{

		if (std::tuple_size<std::tuple<Args...>>::value == str_parameter.size())
		{
			//populate a tuple of f function parameters from a vector of parameters
			//note: parameter types must match when converted from string
			arguments = FunctionTuple::function_args(str_parameter, function_pointer);

			TryVoidPointer(arguments);
			//	apply_f(*class_object, FPtr, arguments);
		}
		else
		{
			std::cout << "Expected " << std::tuple_size<std::tuple<Args...>>::value << " parameters, found "
				<< str_parameter.size() << "\n";
		}
	};

	void CallFunction(const std::vector<std::string>& str_param) override
	{

		if (std::tuple_size<std::tuple<Args...>>::value == str_param.size())
		{
			//populate a tuple of f function parameters from a vector of parameters
			//note: parameter types must match when converted from string
			arguments = FunctionTuple::function_args(str_param, function_pointer);

			TryVoidPointer(arguments);
			//	apply_f(*class_object, FPtr, arguments);
		}
		else
		{
			std::cout << "Expected " << std::tuple_size<std::tuple<Args...>>::value << " parameters, found "
				<< str_param.size() << "\n";
		}
	};


	void SetClass(CC* class_to_use)
	{
		class_object = class_to_use;
	};

	void SetArguments(Args... args)
	{
		arguments = std::make_tuple(args...);

	};


	void GenerateInput() override
	{
		FunctionTuple::generate_for_each(arguments);
		//	apply_f(*(static_cast<CC*>(void_class_ptr)), FPtr, arguments);
		TryVoidPointer(arguments);
	};

	R operator()(Args... args)
	{
		return (class_object->*FPtr)(args...);
	};

	void PrintFunction() override
	{
		std::cout <<  ToString() << "\n";


	};

	size_t ParameterCount() override
	{
		return std::tuple_size<	std::tuple<Args...>>();
	};
};

