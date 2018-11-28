#pragma once
#include <Windows.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "directory.h"

typedef std::vector<std::string> vstring;
class console
{
protected:
	directory*		m_root;
	directory*		m_cur;
	std::string		PATH;
	bool			logout = false;
	bool		ls() const;
	bool		mkdir(const std::string& name) const;
	bool		touch(const std::string& name, ullong size = 0) const;
	bool		pwd() const;
	bool		rm(std::string path) const;
	bool		rmdir(std::string path) const;
	bool		cd(const std::string& path);
	bool		quit();
	void		clear();
	std::string	list_file(file* fichier, int state);
	//bool		export_container(std::string name);
	//bool		import_container(std::string name);

public:
	console();
	console(directory* root);
	~console();
	bool		command(std::string input);
	directory*	get_root();
	directory*	get_cur();
	std::string get_path();
	bool		start();
	
};
