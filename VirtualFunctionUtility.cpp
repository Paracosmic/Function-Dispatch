#include "VirtualFunctionUtility.h"


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
	std::cout << "\n---------Functions--------\n\n";
	for (auto itr : function_map)
	{
		//	std::cout << itr.first << " ";
		if((itr.first)[0] != '<') // cached functions - filter out
			if ((itr.first)[0] != '>') //set cache function parameters
		itr.second->PrintFunction();
	}
	std::cout << "\n---------Cached Functions--------\n\n";

	for (auto itr : function_map)
	{

		if ((itr.first)[0] == '<') // cached functions - filter out
			itr.second->PrintFunction();
	}
	std::cout << "\n---------Cache Function Parameters--------\n\n";

	for (auto itr : function_map)
	{

			if ((itr.first)[0] == '>') //set cache function parameters
				itr.second->PrintFunction();
	}
};

void VirtualFunctionUtility::BindClass(void * ptr, size_t size, std::string function_name)
{
	this->function_map[function_name]->SetClass(ptr, size);
};