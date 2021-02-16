

#include "VirtualFunctionUtility.h"
#include "FunctionHandle.h"
//

#include "Function_Tuple.h"
#include "TupleString.h"
#include "TransformArgument.h"
//
#include <iostream>
#include <string>

#include "VirtualVariable.h"
#include <chrono>

#include <tuple>


void static_test() { std::cout << "STATIC TEST FUNCTION SUCCESS" << std::endl; };
void static_test_int(int i) { std::cout << "STATIC TEST FUNCTION SUCCESS " << i  << std::endl; };

void static_test_int_double(int i, double d) { 
	std::cout << d << " STATIC TEST FUNCTION SUCCESS " << i << std::endl; 
};

class Foo 
{
public:
	void member_test() { std::cout << "MEMBER TEST FUNCTION SUCCESS" << std::endl; };
	void member_test_int(int i) { std::cout << "MEMBER TEST FUNCTION SUCCESS " << i << std::endl; };
	static void static_member_function() 
	{
		std::cout << "Static Member Function!" << std::endl;
	};
void caller_function(int ii, int x, double d, float f)
{
	int i = 10;
	i = i * i;

};

};

v_int static_variable = 12345;


void say(std::string shout)
{
	std::cout << shout << "\n";
}



int main() 
{
	

	//all the programmer has to do to add a new type is make sure GetTypeID and string_to_value get updated
	//the rest is generated! 
	VirtualVariableTemplate < int, float, double, long int> basemap_help;

	v_int v_i = 999;
	v_float v_f = 99.9f;
	v_float v_d = 939.9;
	VirtualVarible<long int> v_li = 1337;
	basemap_help.Add("aaa", v_i);
	basemap_help.Add("b", v_d);
	basemap_help.Add("a", v_f);
	basemap_help.Add("v", v_li);


	basemap_help.SetPrimitive("aaa", "11");
	basemap_help.SetPrimitive("aa", "22");
	basemap_help.SetPrimitive("a", "33");
	basemap_help.SetPrimitive("v", "13337");

//	std::cout << DefBaseHelper::g_type(2, basemap_help.types) << "\n\n\n\n";;
	std:: cout<< basemap_help.GetPrimitive("aaa") << "\n";
	std::cout << basemap_help.GetPrimitive("aa")  << "\n";
	std::cout << basemap_help.GetPrimitive("a")   << "\n";
	std::cout << basemap_help.GetPrimitive("v") << "\n";
	//container for maps
	//Test t;
	//Primitives& p = t;

	VirtualFunctionUtility<decltype(basemap_help)> v = VirtualFunctionUtility<decltype(basemap_help)>(basemap_help);

	//declare an instance of Foo
	Foo f;
	ReflectMember(v, Foo,f,caller_function);
	//Reflect static functions
	ReflectGlobalStatic(v, static_test);
	ReflectGlobalStatic(v, static_test_int);
    ReflectGlobalStatic(v, static_test_int_double);
	ReflectStatic(v, Foo, static_member_function);
	ReflectGlobalStatic(v, say);


	//Reflect member functions


//	ReflectMember(v, Primitives, p, TrySet);
//	ReflectMember(v, Primitives, p, print);
//	ReflectMember(v, VirtualFunctionUtility, v, PrintFunctions);

	ReflectMember(v, Foo, f, member_test);
	ReflectMember(v, Foo, f, member_test_int);

	///try to execute function
	//static
	v.TryExecute("static_test");
	v.TryExecute("static_test_int 6");
	//member
	v.TryExecute("member_test");
	v.TryExecute("member_test_int 1337");

	v_int a = 9;
	v_int b = 69;
	v_int c =  1337;
	v_double d = 7.009;
	//v_int_ptr ptr = &a.Default;
	v_string s = "ptr";
	
	//ReflectVariable(t, static_variable);
	//ReflectVariable(t, a);
	//ReflectVariable(t, b);
	//ReflectVariable(t, c);
	//ReflectVariable(t, d);
	//ReflectVariable(t, s);
	//ReflectVariable(t, ptr);


	//v.TryExecute("static_test_int_double 3 4.5");
//	v.TryExecute("static_test_int_double 2 $d");
//	v.TryExecute("static_test_int_double $a 5.75");

	//prints the value of the variable that s.
	//the value of s is an int pointer named ptr
	//ptr points to a which is the value of 9
//	v.TryExecute("print $s");

	//v.TryExecute("static_member_function");
 
	//for(auto& itr : v.function_map)
//	v.CacheFunction(itr.first);

	//call the function that was cached by adding _cached

	v.TryExecute("static_test_int_double $a $b");
//	v.TryExecute("<static_test_int_double");


	for (int it = 0; it < 100; ++it)
	{
		//Time test
		auto start = std::chrono::steady_clock::now();
		std::string ss = "";
		for (int i = 0; i < 10000; ++i)
		{
			v.TryExecute("caller_function $a $a $d $d");
			//basemap_help.GetPrimitive("aaa");
			//basemap_help.GetPrimitive("aaa");
			//basemap_help.GetPrimitive("aaa");
			//basemap_help.GetPrimitive("aaa");
			//v.TryExecute("caller_function 0 0 0 0");

		}
		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	}

	//function command loop
	//type the name of the function and the parameter values
	while(true)
	{ 
		std::cout << std::endl;
		std::string input;		
		std::getline ( std::cin, input);
		v.TryExecute(input);
	
	}


	return 0;
}



					//template <typename First, typename... Rest>
					//struct Base : public Base<First>, public Base<Rest...> {
					//	using Base<First>::func;
					//	using Base<Rest...>::func;
					//	using Base<First>::test;
					//	using Base<Rest...>::test;
					//};

					//template <typename First>
					//struct Base<First> {
					//	First func(First object)
					//	{



					//	}
					//	void test(First object)
					//	{



					//	}
					//};