#include "Function.h"
#include "Function.h"

bool VirtualFunctionUtility::find(std::string& name)
{
	auto to_find = function_map.find(name);

	return 	(to_find != function_map.end());

}
FunctionHandle* VirtualFunctionUtility::GetFunctionHandle(std::string name)
{

	return function_map[name].get();
};


void VirtualFunctionUtility::CacheFunction(std::string name)
{
	std::string set_args = ">";
	std::string call_with_cached_args = "<";
	set_args.append(name);
	call_with_cached_args.append(name);
	FunctionHandle* cached_function = GetFunctionHandle(name);
	
	ReflectMember_Name((*this), FunctionHandle, *cached_function, call_with_cached_args, CallFunctionWithCachedArguments);
	ReflectMember_Name((*this), FunctionHandle, *cached_function, set_args, SetArgs);
};

void VirtualFunctionUtility::PrintFunctions()
{
	for (auto itr : function_map)
	{
		//	std::cout << itr.first << " ";

		itr.second->PrintFunction();
	}
};

void VirtualFunctionUtility::BindClass(void * ptr, size_t size, std::string function_name)
{
	this->function_map[function_name]->SetClass(ptr, size);
};