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
	std::string name_temp = "@";
	name_temp.append(name);
	FunctionHandle* cached_function = GetFunctionHandle(name);
	
	ReflectMember_Name((*this), FunctionHandle, *cached_function, name.append("_cached"), CallFunctionWithCachedArguments);
	ReflectMember_Name((*this), FunctionHandle, *cached_function, name_temp, SetArgs);
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