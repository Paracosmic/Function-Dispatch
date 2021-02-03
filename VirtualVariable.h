#pragma once

#include <map>
#include <tuple>
#include <string>
#include <algorithm>
#include <sstream> 
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
};



//bad name

//allows for setting values and binding variables to one another through the console via string tokens

typedef int type_id;


class Primitives
{

public:



	static struct type_info
	{
		static const type_id INT = 0;
		static const type_id FLOAT = 1;
		static const type_id DOUBLE = 2;
		static const type_id BOOL = 3;
		static const type_id STRING = 4;
	};

	//primitives pre-defined
	VirtualVaribleMap<int> IntMap;
	VirtualVaribleMap<float> FloatMap;
	VirtualVaribleMap<double> DoubleMap;
	VirtualVaribleMap<bool> BoolMap;
	VirtualVaribleMap<std::string> StringMap;

	//mapping between the variables name, and the type (represented by an integer)
	//without this, know what map to look in to return the value would be impossible
	std::map<std::string, type_id> VariableNames;


	bool NameIsAvailable(std::string name)
	{
		auto itr = VariableNames.find(name);

		if (itr == VariableNames.end())
		{
			return true;
		}
		return false;
	};


	void Add(std::string name, int* type)
	{
		if (NameIsAvailable(name)) {
			this->IntMap.Add(name, type);
			VariableNames.emplace(name, type_info::INT);
		}
	};
	void Add(std::string name, double* type)
	{
		if (NameIsAvailable(name))
		{
			this->DoubleMap.Add(name, type);
			VariableNames.emplace(name, type_info::DOUBLE);
		}
	};
	void Add(std::string name, std::string* type)
	{
		if (NameIsAvailable(name)) {
			this->StringMap.Add(name, type);
			VariableNames.emplace(name, type_info::STRING);
		}
	};
	void Add(std::string name, bool* type)
	{
		if (NameIsAvailable(name)) {
			this->BoolMap.Add(name, type);
			VariableNames.emplace(name, type_info::BOOL);
		}
	};
	void Add(std::string name, float* type)
	{
		if (NameIsAvailable(name)) {
			this->FloatMap.Add(name, type);
			VariableNames.emplace(name, type_info::FLOAT);

		}
	};
	//


	void Add(std::string name, v_int& type)
	{
		if (NameIsAvailable(name)) {
			type.Name = name;
			VariableNames.emplace(name, type_info::INT);
			this->IntMap.Add(name, type);

		}
	};
	void Add(std::string name, v_double& type)
	{
		if (NameIsAvailable(name))
		{
			this->DoubleMap.Add(name, type);
			VariableNames.emplace(name, type_info::DOUBLE);
		}
	};

	void Add(std::string name, v_bool& type)
	{
		if (NameIsAvailable(name)) {
			this->BoolMap.Add(name, type);
			VariableNames.emplace(name, type_info::BOOL);
		}
	};
	void Add(std::string name, v_float& type)
	{
		if (NameIsAvailable(name)) {
			this->FloatMap.Add(name, type);
			VariableNames.emplace(name, type_info::FLOAT);

		}
	};

	void Add(std::string name, v_string& type)
	{
		if (NameIsAvailable(name)) {
			this->StringMap.Add(name, type);
			VariableNames.emplace(name, type_info::STRING);
		}
	};

	virtual std::string TryGet(std::string name)
	{
		//if (!NameIsAvailable(name))
		//{
			auto itr = VariableNames.find(name);


			int t = itr->second;

			if (itr != VariableNames.end())

				GetPrimitive(name,t);
		//}

		return "NULL";
	};

	std::string GetPrimitive(std::string name, type_id id) 
	{
		switch (id)
		{

		case type_info::INT:
		{
			//	std::cout << std::endl;
			return std::to_string(IntMap.Get(name));
			break;

		}
		case type_info::BOOL:
		{
			return std::to_string(BoolMap.Get(name));
			break;
		}
		case type_info::FLOAT:
		{
			return std::to_string(FloatMap.Get(name));
			break;
		}
		case type_info::DOUBLE:
		{
			return std::to_string(DoubleMap.Get(name));
			break;
		}
		case type_info::STRING:
		{
			return StringMap.Get(name);
			break;
		}
		default: {	return "NULL-GET"; }
		}
	
	};

	void print(std::string n)
	{
		std::cout << n << " = " << TryGet(n) << std::endl;;
	}
	//TODO add pointer/ref types in addition to value primitives



};


typedef VirtualVarible<int*> v_int_ptr;
//Test Class for expanding primitives WIP
class Test : public Primitives
{
public:
	VirtualVaribleMap<int*> IntPtrMap;

	static struct type_info : public Primitives::type_info
	{
		static const type_id INT_PTR = 5;
	};


	template <typename T>
	void Add(std::string name, T& type)
	{
		Primitives::Add(name,type);
	};

	void Add(std::string name, v_int_ptr& type)
	{
		if (NameIsAvailable(name)) {
			type.Name = name;
			VariableNames.emplace(name, type_info::INT_PTR);
			this->IntPtrMap.Add(name, type);

		}
	};

	virtual std::string TryGet(std::string name) override
	{
		if (!NameIsAvailable(name))
		{
			auto itr = VariableNames.find(name);


			int id = itr->second;

			if (itr != VariableNames.end())
				switch (id)
				{

				case type_info::INT_PTR:
				{


					return std::to_string((int)IntPtrMap.Get(name));

				}


				default:
				{

					return GetPrimitive(name, id);
				}


				}
		}

		return "NULL";
	};

};