#pragma once

#include <map>
#include <tuple>
#include <string>


	template<typename T>
	struct VirtualVarible
	{	
		T Default = 0;
		T* Pointer = &Default;
	
		std::string Name = "NULL";

		VirtualVarible() = delete;
		VirtualVarible(T value) : Default(value), Pointer(&Default){ };

		VirtualVarible(std::string name, T value) : Name(name),Default(value), Pointer(&Default) { };
	};
	typedef VirtualVarible<int> v_int;
	typedef VirtualVarible<double> v_double;
	typedef VirtualVarible<float> v_float;
	typedef VirtualVarible<bool> v_bool;

	template<typename T>
	struct VirtualVaribleMap
	{
		std::map<std::string, T**> Map;
		std::map<std::string, T*> DefaultMap;
		void Add(std::string name, T*& default_var) 
		{
			//TypeMap[name] = virtual_type_info::INT;
			DefaultMap[name] = default_var;
			Map[name] = &default_var;
		
		};

		void Add(std::string name, VirtualVarible<T>& default_var)
		{
			//TypeMap[name] = virtual_type_info::INT;
			DefaultMap[name] = &default_var.Default;
			Map[name] = &default_var.Pointer;

		};

		void Add(VirtualVarible<T>& default_var)
		{
			if (default_var.Name != "NULL") 
			{
				DefaultMap[default_var.Name] = &default_var.Default;
				Map[default_var.Name] = &default_var.Pointer;
			}

		};
	};


	typedef VirtualVaribleMap<int> IntMap;
	typedef VirtualVaribleMap<float> FloatMap;
	typedef VirtualVaribleMap<double> DoubleMap;
	typedef VirtualVaribleMap<bool> BoolMap;
	typedef VirtualVaribleMap<std::string> StringMap; 
	//bad name
	//allows for setting values and binding variables to one another through the console via string tokens
class Primitives
{
public:
	//primitives pre-defined
	VirtualVaribleMap<int> IntMap;
	VirtualVaribleMap<float> FloatMap;
	VirtualVaribleMap<double> DoubleMap;
	VirtualVaribleMap<bool> BoolMap;
	VirtualVaribleMap<std::string> StringMap;

	//TODO add pointer/ref types in addition to value primitives
};