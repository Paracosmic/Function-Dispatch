#pragma once

#include <map>
#include <tuple>
#include <string>
#include <algorithm>
#include <sstream> 
#include <iostream>
#define GenName(VariableName) # VariableName
#define ReflectVariable(P, V) P.Add(GenName(V), V)

template<typename T>
struct VirtualVarible
{
	T Default = 0;
	T* Pointer = &Default;

	std::string Name = "NULL";

	VirtualVarible() = delete;
	VirtualVarible(T value) : Default(value), Pointer(&Default) { };

	VirtualVarible(std::string name, T value) : Name(name), Default(value), Pointer(&Default) { };
};
typedef VirtualVarible<int> v_int;
typedef VirtualVarible<double> v_double;
typedef VirtualVarible<float> v_float;
typedef VirtualVarible<bool> v_bool;
typedef VirtualVarible<std::string> v_string;




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


	T& Get(std::string name) { return **Map[name]; };
	void Set(std::string name, T value) { **Map[name] = value; };
};
typedef int type_id;
static struct type_info_v
{
	static const type_id INT = 0;
	static const type_id FLOAT = 1;
	static const type_id DOUBLE = 2;
	static const type_id BOOL = 3;
	static const type_id STRING = 4;
	static const type_id LONG_INT = 5;
};

template<class T> static type_id GetTypeID(T type);
template<> static type_id GetTypeID(int type) { return type_info_v::INT; };
template<> static type_id GetTypeID(double type) { return type_info_v::DOUBLE; };
template<> static type_id GetTypeID(std::string type) { return type_info_v::STRING; };
template<> static type_id GetTypeID(bool type) { return type_info_v::BOOL; };
template<> static type_id GetTypeID(float type) { return type_info_v::FLOAT; };
template<> static type_id GetTypeID(long int type) { return type_info_v::LONG_INT; };


//string to value actually
template<class T> static T string_to_type(std::string value, T type);
template<> static int string_to_type(std::string value, int type) { return std::stoi(value); };
template<> static double string_to_type(std::string value, double type) { return std::stod(value); };
template<> static std::string string_to_type(std::string value, std::string type) { return value; };
template<> static bool string_to_type(std::string value, bool type) { return std::stoi(value); };
template<> static float string_to_type(std::string value, float type) { return std::stof(value); };
template<> static long int string_to_type(std::string value, long int type) { return std::stoi(value); };

struct VirtualVariableMapGetSet
{
	virtual std::string Get(std::string name) = 0;
	virtual void Set(std::string name, std::string value) = 0;
};
//template boiler-plate that recurses through each type and inherits from that type into a base<type> template that implements functions/maps 
template <typename First, typename... Rest>
struct VirtualVaribleMapBase : public VirtualVaribleMapBase<First>, public VirtualVaribleMapBase<Rest...> {
	//functions to generate for each type
	using VirtualVaribleMapBase<First>::Add;
	using VirtualVaribleMapBase<Rest...>::Add;
	using VirtualVaribleMapBase<First>::Get;
	using VirtualVaribleMapBase<Rest...>::Get;
	using VirtualVaribleMapBase<First>::Set;
	using VirtualVaribleMapBase<Rest...>::Set;

};

//class template for generated type
template <typename First>
struct VirtualVaribleMapBase<First> {

	//each type gets a variable map of its type
	VirtualVaribleMap<First> Map;



	void Add(std::string name, VirtualVarible<First>& type, std::map<std::string, int>& VariableNames)
	{
		type.Name = name;
		VariableNames.emplace(name, GetTypeID(type.Default));
		VirtualVaribleMapBase<First>::Map.Add(name, type);
	};

	std::string Get(std::string name)
	{
		return std::to_string(VirtualVaribleMapBase<First>::Map.Get(name));
	};

	void Set(std::string name, First value)
	{
		VirtualVaribleMapBase<First>::Map.Set(name, value);
	};
};

//Helper class 
template <typename First, typename... Rest>
struct VirtualVariableTemplate
{
	std::tuple<First, Rest...> types; // all types to be reflected
	VirtualVaribleMapBase<First, Rest...> BaseMap; //template that generates a base class with a map to each type
	std::map<std::string, int> VariableNames; //a map of names and types represented as an integer(int)

	//Is this name available?
	bool NameIsAvailable(std::string name)
	{
		auto itr = VariableNames.find(name);

		if (itr == VariableNames.end())
		{
			return true;
		}
		return false;
	};

	template<typename T>
	void Add(std::string name, VirtualVarible<T>& type)
	{
		if (NameIsAvailable(name))
		{
			BaseMap.VirtualVaribleMapBase<T>::Add(name, type, VariableNames);
		}
	};




	template<typename T>
	static void CheckType(VirtualVariableTemplate* explicit_this, std::string name, int target, T var, std::string& to_return)
	{
		//if this is the type we are looking for
		if (target == GetTypeID(var))
		{
			//set the to_return string to the to_string value 
			to_return = explicit_this->BaseMap.VirtualVaribleMapBase<T>::Get(name);



		};
	};

	template<class...Ts, std::size_t...Is>
	static std::string FindPrimitiveType(VirtualVariableTemplate* explicit_this, std::string name, int target, std::tuple<Ts...>& tuple, std::index_sequence<Is...>) {

		std::string to_return = "";
		using expander = int[];
		expander{
			0, (CheckType(explicit_this,name,target,std::get<Is>(tuple),to_return), 0)...
		};


		return to_return;
	}

	template<class...Ts>
	static std::string FindPrimitiveType(VirtualVariableTemplate* explicit_this, std::string name, int target, std::tuple<Ts...>& tuple) {
		return FindPrimitiveType(explicit_this, name, target, tuple, std::make_index_sequence<sizeof...(Ts)>());
	}
	///





	//safe
	std::string GetPrimitive(std::string name)
	{
		auto itr = VariableNames.find(name);
		if (itr != VariableNames.end()) {



			return FindPrimitiveType(this, name, itr->second, types);
		}
		else
		{
			return "NOT-FOUND";
		}
	};
	///----------

	template<typename T>
	static void SetType(VirtualVariableTemplate* explicit_this, std::string name, std::string value, int target, T var)
	{

		//if this is the type we are looking for
		if (target == GetTypeID(var))
		{
			//set the to_return string to the to_string value 
			auto t = string_to_type(value, var);
			explicit_this->BaseMap.VirtualVaribleMapBase<T>::Set(name, t);

		};
	};


	template<class...Ts, std::size_t...Is>
	static void SetPrimitiveType(VirtualVariableTemplate* explicit_this, std::string name, std::string value, int target, std::tuple<Ts...>& tuple, std::index_sequence<Is...>) {


		using expander = int[];
		expander{
			0, (SetType(explicit_this,name,value,target,std::get<Is>(tuple)), 0)...
		};



	}

	template<class...Ts>
	static void SetPrimitiveType(VirtualVariableTemplate* explicit_this, std::string name, std::string value, int target, std::tuple<Ts...>& tuple) {
		SetPrimitiveType(explicit_this, name, value, target, tuple, std::make_index_sequence<sizeof...(Ts)>());
	}





	void SetPrimitive(std::string name, std::string value)
	{
		auto itr = VariableNames.find(name);
		if (itr != VariableNames.end()) {

			SetPrimitiveType(this, name, value, itr->second, types);
		}
		else
		{

		}

	}
};






