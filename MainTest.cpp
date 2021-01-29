
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
void testFunc() { std::cout << "TEST FUNCTION SUCCESS" << std::endl; };
int main() 
{

	VirtualFunctionUtility Virtual_Function_Util;
	Virtual_Function_Util.Reflect_Static_Function("test", testFunc, {});

	Virtual_Function_Util.TryExecute("test");
	return 0;
}