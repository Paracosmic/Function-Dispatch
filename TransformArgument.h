#pragma once
#include <string>
#include <iostream>
class ArgumentUtil 
{
public:


	template<class T> static T transform_arg(std::string const &s);
	template<> static double transform_arg(std::string const &s) 
	{ 
		std::string ret = s;
		double d = 0.0f;
		bool isneg = false;
		if (s[0] == '-') 
		{
			

		ret = s.substr(1,s.size());
		isneg = true;
		}

		if(isdigit(ret[0]))
		{
		 d = std::stod(ret);
		}
		else 
		{
			std::cout << "Argument '" <<ret << "' is invalid. Expected value type: double.\n";
		};
		if (isneg)
			d = -d;
		return d; 
	}
	template<> static int transform_arg(std::string const &s)
	{
		std::string ret = s;
		int d = 0;
		bool isneg = false;
		if (s[0] == '-')
		{


			ret = s.substr(1, s.size());
			isneg = true;
		}

		if (isdigit(ret[0]))
		{
			d = std::stoi(ret);
		}
		else
		{
			std::cout << "Argument '" << ret << "' is invalid. Expected value type: double.\n";
		};
		if (isneg)
			d = -d;
		return d;
	
	}
	template<> static std::string transform_arg(std::string const &s) { return s; }
	template<> static float transform_arg(std::string const &s) 
	{
		std::string ret = s;
		float d = 0;
		bool isneg = false;
		if (s[0] == '-')
		{


			ret = s.substr(1, s.size());
			isneg = true;
		}

		if (isdigit(ret[0]))
		{
			d = std::stof(ret);
		}
		else
		{
			std::cout << "Argument '" << ret << "' is invalid. Expected value type: double.\n";
		};
		if (isneg)
			d = -d;
		return d;
	}

	template<class T> static  T generate_input(T type);
	template<> static int generate_input(int type) { return 424242; };
	template<> static double generate_input(double type) { return 0.01010101010; };
	template<> static float generate_input(float type) { return 0.01010101010f; };
	template<> static std::string generate_input(std::string type) { return "generatedxDXDXD"; };
	 template<> static bool generate_input(bool type) { return true; };
};