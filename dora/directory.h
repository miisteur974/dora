#pragma once
#include "file.h"
#include "utils.h"

class directory : public file
{

protected:
	std::vector<file*> content;

public:
	
	directory();
	directory(std::string name, file* f = nullptr);
	directory(directory &original);
	~directory();

	// getters
	std::vector<file*>			get_content()	const;
	bool						remove_elem(std::string& elem_name);
	file*						find(std::string name);

	// operations
	bool	add_file(std::string name, ullong size = 0);
	bool	add_file(file* fil);
	bool	add_dir(std::string name);
	bool	add_dir(directory* dir);
	
};