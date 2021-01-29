#pragma once
#include "FunctionHandle.h"


void FunctionHandle::CallFunction() { std::cout << "not implemented \n"; };
void FunctionHandle::CallFunction(const std::vector<std::string>& str_param) { std::cout << "not implemented \n"; };
void FunctionHandle::SetClass(void* ptr, size_t size)
{
	if (this->class_size != 0)//{
	{
		if (size == this->class_size)
			this->void_class_ptr = ptr;
		else
		{
			
			std::cout << function_name << " : Invalid class detected!\n";
		}
	}
};

void FunctionHandle::PrintFunction() { std::cout << "not implemented \n"; };

void FunctionHandle::GenerateInput() { std::cout << "not implemented \n"; };
void FunctionHandle::SetFirstParam() {};
std::string FunctionHandle::ToString() { return ""; };
