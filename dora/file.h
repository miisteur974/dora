#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "utils.h"
typedef unsigned long long ullong;

class file
{

protected:
	file*				m_parent;
	std::string			m_name;
	std::string			m_ext;
	ullong				m_size = 0;

public:

	file();
	file(std::string name, ullong size = 0);
	file(file &original);
	virtual ~file();

	// getters
	std::string				get_name()		const;
	ullong					get_size();
	std::string				get_fullname()	const;
	std::string				get_ext()		const;
	file*					get_parent()	const;

	//setters
	bool	set_name(std::string name);
	bool	set_size(ullong size);
	bool	set_extension(std::string ext);
	bool	set_parent(file* parent);

	// operators 
	file& operator=(file& b);

	void get_path();

};
