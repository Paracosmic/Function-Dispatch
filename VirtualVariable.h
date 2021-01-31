#pragma once

#include <map>
#include <tuple>
#include <string>
#include <algorithm>
#define GenName(VariableName) # VariableName

#define ReflectVariable(P, V) P.Add(GenName(V), V);

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


		T& Get(std::string name)  { return **Map[name]; };
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
	enum class PrimitiveType{INT,FLOAT,DOUBLE,BOOL,STRING};
	//primitives pre-defined
	VirtualVaribleMap<int> IntMap;
	VirtualVaribleMap<float> FloatMap;
	VirtualVaribleMap<double> DoubleMap;
	VirtualVaribleMap<bool> BoolMap;
	VirtualVaribleMap<std::string> StringMap;
	std::map<std::string,PrimitiveType> VariableNames;
	bool NameIsAvailable(std::string name) 
	{
		auto itr = VariableNames.find(name);

		if (itr == VariableNames.end())
		{
			return true;
		}
		return false;
	};
	template<class T>  void Add(std::string name, T* type);
	template<> void Add(std::string name, int* type)
	{
		if (NameIsAvailable(name)) {
			this->IntMap.Add(name, type);
			VariableNames.emplace(name,PrimitiveType::INT);
		}
	};
	template<> void Add(std::string name, double* type)
	{
		if(NameIsAvailable(name))
		{
		this->DoubleMap.Add(name, type);
		VariableNames.emplace(name, PrimitiveType::DOUBLE);
		}
	};
	template<> void Add(std::string name, std::string* type)
	{
		if(NameIsAvailable(name)){
		this->StringMap.Add(name, type);
		VariableNames.emplace(name, PrimitiveType::STRING);
		}
	};
	template<> void Add(std::string name, bool* type)
	{
		if(NameIsAvailable(name)){
		this->BoolMap.Add(name, type);
		VariableNames.emplace(name, PrimitiveType::BOOL);
		}
	};
	template<> void Add(std::string name, float* type)
	{
		if(NameIsAvailable(name)){
		this->FloatMap.Add(name, type);
		VariableNames.emplace(name, PrimitiveType::FLOAT);
		
		}
	};
	//

	template<class T>  void Add(std::string name, T& type);
	template<> void Add(std::string name, v_int& type)
	{
		if (NameIsAvailable(name)) {
			type.Name = name;
		VariableNames.emplace(name, PrimitiveType::INT);
			this->IntMap.Add(name, type);
	
	}
	};
	template<> void Add(std::string name, v_double& type)
	{
		if (NameIsAvailable(name))
		{
			this->DoubleMap.Add(name, type);
			VariableNames.emplace(name, PrimitiveType::DOUBLE);
		}
	};

	template<> void Add(std::string name, v_bool& type)
	{
		if (NameIsAvailable(name)) {
			this->BoolMap.Add(name, type);
			VariableNames.emplace(name, PrimitiveType::BOOL);
		}
	};
	template<> void Add(std::string name, v_float& type)
	{
		if (NameIsAvailable(name)) {
			this->FloatMap.Add(name, type);
			VariableNames.emplace(name, PrimitiveType::FLOAT);

		}
	};

	template<> void Add(std::string name, v_string& type)
	{
		if (NameIsAvailable(name)) {
			this->StringMap.Add(name, type);
			VariableNames.emplace(name, PrimitiveType::STRING);
		}
	};

	std::string TryGet(std::string name)
	{
		if (!NameIsAvailable(name))
		{
			auto itr = VariableNames.find(name);

			
			PrimitiveType t = itr->second;

			if(itr != VariableNames.end())

			switch (t)
			{

			case PrimitiveType::INT:
			{ 
			//	std::cout << std::endl;
				return std::to_string(IntMap.Get(name));
				break;
			}
			case PrimitiveType::BOOL:
			{
				return std::to_string(BoolMap.Get(name));
				break;
			}
			case PrimitiveType::FLOAT:
			{ 
				return std::to_string(FloatMap.Get(name));
				break; 
			}
			case PrimitiveType::DOUBLE:
			{ 
			return std::to_string(DoubleMap.Get(name));
				break;
			}
			case PrimitiveType::STRING:
			{
				return StringMap.Get(name);
				break;
			}
			}
		}
	
		return "NULL";
	};


	void print(std::string n)
	{
		std::cout << TryGet(n) << std::endl;;
	}
	//TODO add pointer/ref types in addition to value primitives
};