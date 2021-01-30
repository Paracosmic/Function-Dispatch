
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
void static_test_func() { std::cout << "STATIC TEST FUNCTION SUCCESS" << std::endl; };
void static_test_func_int_param(int i) { std::cout << "STATIC TEST FUNCTION SUCCESS " << i  << std::endl; };

class Foo 
{
public:
	void member_test_func() { std::cout << "MEMBER TEST FUNCTION SUCCESS" << std::endl; };
	void member_test_func_int_param(int i) { std::cout << "MEMBER TEST FUNCTION SUCCESS " << i << std::endl; };

};
int main() 
{

	VirtualFunctionUtility Virtual_Function_Util;
	//Reflect static functions
	Virtual_Function_Util.Reflect_Static_Function("static-test", static_test_func, {});
	Virtual_Function_Util.Reflect_Static_Function("static-test-int", static_test_func_int_param, {});

	//declare an instance of Foo
	Foo f;
	//Reflect member functions
	Virtual_Function_Util.Reflect_Member_Function("member-test",f, &Foo::member_test_func, {});
	Virtual_Function_Util.Reflect_Member_Function("member-test-int",f, &Foo::member_test_func_int_param, {});

	///try to execute function
	//static
	Virtual_Function_Util.TryExecute("static-test");
	Virtual_Function_Util.TryExecute("static-test-int 1337");
	//member
	Virtual_Function_Util.TryExecute("member-test");
	Virtual_Function_Util.TryExecute("member-test-int 1337");


	//function command loop
	//type the name of the function and the parameter values
	while(true)
	{ 
		std::string input;		
		std::getline ( std::cin, input);
		Virtual_Function_Util.TryExecute(input);
	
	}


	return 0;
}