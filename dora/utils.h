#pragma once
#include <iostream>
#include <string>
#include <vector>

class utils
{
public:

	static std::vector<std::string> split(std::string a, char limiter);
	static std::string				join(std::vector<std::string> string_tab, char c = 0);
	static bool						name_check(std::string name); 
};
