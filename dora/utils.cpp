#include "utils.h"

std::vector<std::string> utils::split(std::string a, char limiter)
{
	std::vector<std::string> tab;
	if (a.size() <= 1)
	{
		tab.push_back(a);
		return tab;
	}
	unsigned i = 0, count = 0;
	for (i = 0; i < a.size(); i++)
	{
		if ( a[i] == limiter)
		{
			count++;
		}
	}
	if (count < 1)
	{
		tab.push_back(a);
		return tab;
	} 
	else
	{
		tab.emplace_back();
		count = 0;
		for (i = 0; i < a.size(); i++)
		{
			if ( a[i] != limiter)
			{
				tab[count] += a[i];
			}
			else
			{
				count++;
				tab.emplace_back();
			}
		}
	}
	return tab;
}

std::string utils::join(std::vector<std::string> string_tab ,char c)
{
	std::string final;
	if (c == 0)
	{
		for (unsigned int i = 0; i < string_tab.size(); i++)
		{
			final += string_tab[i];
		}
	}
	else
	{
		if (string_tab.empty())
			return final;

		final += string_tab[0]+c;
		if (string_tab.size() < 2)
			return final;

		for (unsigned int i = 1; i < string_tab.size() - 1; i++)
		{
			final += string_tab[i] + c;
		}
	}
	return final;
}

bool utils::name_check(std::string name)
{
	std::string schar = "\"/#~@$";
	for (unsigned int i = 0; i < schar.size(); i++)
	{
		for (unsigned int j = 0; j < name.size(); j++)
		{
			if (name[j] == schar[i])
			{
				std::cout << " Vous ne pouvez pas utiliser le caractere : \"" << schar[i] << "\" !" << std::endl;
				return false;
			}
		}
	}
	return true;
}

