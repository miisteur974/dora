#include "directory.h"

directory::directory()
{
	this->m_name = "";
	this->m_size = 0;
}

directory::directory(std::string name, file* f)
{
	this->m_name = name;
	if (f)
	{
		f->set_parent(this);
		this->content.push_back(f);
		this->m_size += f->get_size();
	}
}

directory::directory(directory& original)
	: file(original)
{
	this->content = original.get_content();
}

directory::~directory()
{
	for (unsigned int i = 0; i < this->content.size(); i++)
	{
		if (dynamic_cast<directory*>(this->content[i]))
		{
			delete dynamic_cast<directory*>(this->content[i]);
		}
		else
		{
			delete this->content[i];
		}
	}
}

std::vector<file*> directory::get_content() const
{
	return this->content;
}


bool directory::remove_elem(std::string& elem_name)
{
	if (dynamic_cast<directory*>(this->find(elem_name))){
		directory* tmp = dynamic_cast<directory*>(this->find(elem_name));
		std::vector<file*>::iterator it;
		int i = 0;
		for (it = this->content.begin(); it != this->content.end(); ++it)
		{
			if ((*it) == this->find(elem_name))
			{
				break;
			}
			i++;
		}
		this->content.erase(this->content.begin() + i);
		delete tmp;
	} 
	else
	{
		file* tmp = this->find(elem_name);
		std::vector<file*>::iterator it;
		int i = 0;
		for (it = this->content.begin(); it != this->content.end(); ++it)
		{
			if ((*it) == this->find(elem_name))
			{
				break;
			}
			i++;
		}
		this->content.erase(this->content.begin() + i);
		delete tmp;
	}
	
	return true;
}


file* directory::find(std::string name)
{
	std::vector<file*>::iterator it;
	for (it = this->content.begin(); it != this->content.end(); ++it)
	{
		if (((*it)->get_name() == name) || ((*it)->get_fullname() == name))
		{
			return *it;
		}
	}
	return nullptr;
}

bool directory::add_file(std::string name, ullong size)
{
	file* exist = this->find(name);
	if (exist)
	{
		std::cout << " Ce nom est deja utilise ! " << std::endl;
		return false;
	}
	file *fichier = new file(name, size);
	this->content.push_back(fichier);
	fichier->set_parent(this);
	file* remontada = this;
	while (remontada->get_parent())
	{
		remontada->set_size(remontada->get_size() + size);
		remontada = remontada->get_parent();
	}
	remontada->set_size(remontada->get_size() + size);
	return true;
}

bool directory::add_file(file* fil)
{
	if (!fil)
		return false;
	file* exist = this->find(fil->get_name());
	if (exist)
	{
		std::cout << " Ce nom est deja utilise ! " << std::endl;
		return false;
	}
	this->content.push_back(fil);
	fil->set_parent(this);
	file* remontada = this;
	while (remontada->get_parent())
	{
		remontada->set_size(remontada->get_size() + fil->get_size());
		remontada = remontada->get_parent();
	}
	remontada->set_size(remontada->get_size() + fil->get_size());
	return true;
}

bool directory::add_dir(std::string name)
{
	file* exist = this->find(name);
	if (exist)
	{
		std::cout << " Ce nom est deja utilise ! " << std::endl;
		return false;
	}
	directory* dir = new directory(name);
	this->content.push_back(dir);
	dir->set_parent(this);
	return true;
}

bool directory::add_dir(directory* dir)
{
	file* exist = this->find(dir->get_name());
	if (exist)
	{
		std::cout << " Ce nom est deja utilise ! " << std::endl;
		return false;
	}
	this->content.push_back(dir);
	dir->set_parent(this);
	return true;
}
