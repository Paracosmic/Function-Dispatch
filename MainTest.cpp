
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
	//container for maps
	Primitives p;

	VirtualFunctionUtility Virtual_Function_Util = VirtualFunctionUtility(p.IntMap);
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

	VirtualVarible<int> a = 9;


	v_int b = 69;

	//can assign name here, harder to read though
	v_int c = { "VariableC", 1337 };

	

	//also valid
	IntMap intmap;
	//get map for int
	auto& map = p.IntMap;

	//type deduction here?
	map.Add("VariableA", a);

	//note that VariableA and VariableB are in seperate maps!!!
	map.Add("VariableB", b);

	intmap.Add(c);
	 //access the built in the mapped variable
	int& a_ref = **p.IntMap.Map["VariableA"];

	//access the user defined mapped variable
	int& b_ref = **p.IntMap.Map["VariableB"]; 


	//access the user defined mapped variable with the name assigned at initialization (safer)
	int& c_ref = **intmap.Map["VariableC"];
	//test to see if we actually get the value
	std::cout << a_ref << " - " << b_ref << " - " << c_ref << std::endl;

	//function command loop
	//type the name of the function and the parameter values


	Virtual_Function_Util.TryExecute("static-test-int $VariableA");
	while(true)
	{ 
		std::string input;		
		std::getline ( std::cin, input);
		Virtual_Function_Util.TryExecute(input);
	
	}


	return 0;
}