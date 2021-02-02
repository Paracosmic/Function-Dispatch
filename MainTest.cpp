

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
	static void static_member_function() 
	{
		std::cout << "Static Member Function!" << std::endl;
	};

};

v_int static_variable = 12345;

int main() 
{
	//container for maps
	Test t;
	Primitives& p = t;

	VirtualFunctionUtility v = VirtualFunctionUtility(p);



	//Reflect static functions
	ReflectGlobalStatic(v, static_test);
	ReflectGlobalStatic(v, static_test_int);
	ReflectGlobalStatic(v, static_test_int_double);
	ReflectStatic(v, Foo, static_member_function);

	//declare an instance of Foo
	Foo f;

	//Reflect member functions
	ReflectMember(v, Primitives, p, print);
	ReflectMember(v, VirtualFunctionUtility, v, PrintFunctions);

	ReflectMember(v, Foo, f, member_test);
	ReflectMember(v, Foo, f, member_test_int);

	///try to execute function
	//static
	v.TryExecute("static_test");
	v.TryExecute("static_test_int 1337");
	//member
	v.TryExecute("member_test");
	v.TryExecute("member_test_int 1337");

	v_int a = 9;
	v_int b = 69;
	v_int c =  1337;
	v_double d = 7.009;
	v_int_ptr ptr = &a.Default;
	v_string s = "ptr";
	
	ReflectVariable(t, static_variable);
	ReflectVariable(t, a);
	ReflectVariable(t, b);
	ReflectVariable(t, c);
	ReflectVariable(t, d);
	ReflectVariable(t, s);
	ReflectVariable(t, ptr);


	v.TryExecute("static_test_int_double 3 4.5");
	v.TryExecute("static_test_int_double 2 $d");
	v.TryExecute("static_test_int_double $a 5.75");
	//prints the value of the variable that s.
	//the value of s is an int pointer named ptr
	//ptr points to a which is the value of 9
	v.TryExecute("print $s");

	v.TryExecute("static_member_function");
 

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