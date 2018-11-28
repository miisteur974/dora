#include "file.h"

file::file()
{
	this->m_name = "";
	this->m_ext = "";
	this->m_parent = nullptr;
}

file::file(std::string name, ullong size)
{
	if (!name.empty())
	{
		std::vector<std::string> fullName = utils::split(name, '.');
		this->m_name = fullName[0];
		for (unsigned int i = 1; i < fullName.size() - 1; i++)
			this->m_name += fullName[i];
		if (fullName.size() > 1)
			this->m_ext = fullName[fullName.size() - 1];
	}
	else
	{
		this->m_name = name;
	}
	this->m_size = size;
}

file::file(file& original)
{
	this->m_name = original.get_name();
	this->m_ext = original.get_ext();
	this->m_size = original.get_size();
}

file::~file()
{}

std::string file::get_name() const
{
	return this->m_name;
}

std::string file::get_ext() const
{
	return this->m_ext;
}

file* file::get_parent() const
{
	return this->m_parent;
}

std::string file::get_fullname() const
{
	std::string full = this->m_name;
	if (!this->m_ext.empty())
		full += ".";
	full += this->m_ext;
	return full;
}

ullong file::get_size()
{
	return this->m_size;
}

bool file::set_name(std::string name)
{
	this->m_name = name;
	return true;
}

bool file::set_size(ullong size)
{
	this->m_size = size;
	return true;
}

bool file::set_extension(std::string ext)
{
	this->m_ext = ext;
	return true;
}

bool file::set_parent(file* parent)
{
	if (!parent)
		return false;
	this->m_parent = parent;
	return true;
}

file& file::operator=(file& b)
{
	if (this != &b)
	{
		this->m_name = b.get_name();
		this->m_ext = b.get_ext();
		this->m_size = b.get_size();
	}
	return *this;
}

void file::get_path()
{
	file* tmp = this;
	while (tmp->get_parent())
	{
		std::cout << tmp->get_name();
		tmp = tmp->get_parent();
	}
}




