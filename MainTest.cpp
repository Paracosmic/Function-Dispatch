
#include "CaptureFunction.h"
#include "Function.h"
#include "FunctionHandle.h"
//
#include "function.h"
#include "Function_Tuple.h"
#include "TupleString.h"
#include "TransformArgument.h"
//
#include <iostream>
#include <string>

#include "VirtualVariable.h"


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
	static void f() 
	{
		std::cout << "FFFFFFFFFFFFFFFF" << std::endl;
	};

};
int main() 
{
	//container for maps
	Primitives p;

	VirtualFunctionUtility Virtual_Function_Util = VirtualFunctionUtility(p);
	//Reflect static functions

	ReflectGlobalStatic(Virtual_Function_Util, static_test)
	///Virtual_Function_Util.Reflect_Static_Function(GenName(static_test), static_test, {});
	ReflectGlobalStatic(Virtual_Function_Util, static_test_int)
	ReflectGlobalStatic(Virtual_Function_Util, static_test_int_double)
	ReflectStatic(Virtual_Function_Util, Foo,f)

	//declare an instance of Foo
	Foo f;

	//Reflect member functions
	ReflectMember(Virtual_Function_Util, Primitives, p, print)
	ReflectMember(Virtual_Function_Util,		Foo, f, member_test)
	ReflectMember(Virtual_Function_Util,		Foo, f, member_test_int)

	///try to execute function
	//static
	Virtual_Function_Util.TryExecute("static_test");
	Virtual_Function_Util.TryExecute("static_test_int 1337");
	//member
	Virtual_Function_Util.TryExecute("member_test");
	Virtual_Function_Util.TryExecute("member_test_int 1337");

	v_int a = 9;
	v_int b = 69;
	v_int c =  1337;
	v_double d = 7.009;
	v_string s = "Normal string!";

	ReflectVariable( p , a)
	ReflectVariable( p , b)
	ReflectVariable( p , c)
	ReflectVariable( p , d)
	ReflectVariable( p , s)

	//why is value $a null?
	Virtual_Function_Util.TryExecute("static_test_int_double 3 4.5");

	Virtual_Function_Util.TryExecute("static_test_int_double 2 $d");

	Virtual_Function_Util.TryExecute("static_test_int_double $a 5.75");


	Virtual_Function_Util.TryExecute("print a");

	Virtual_Function_Util.TryExecute("f");

	//function command loop
	//type the name of the function and the parameter values
	while(true)
	{ 
		std::cout << std::endl;
		std::string input;		
		std::getline ( std::cin, input);
		Virtual_Function_Util.TryExecute(input);
	
	}


	return 0;
}