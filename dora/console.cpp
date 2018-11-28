#include "console.h"


console::console()
{
	this->m_root = new directory("C:");
	this->m_cur = this->m_root;
	this->PATH += this->m_cur->get_name() + "/";
}

console::console(directory* root)
{
	this->m_root = root;
	this->m_cur = this->m_root;

	this->PATH += this->m_cur->get_name() + "/";
}

console::~console()
{
	delete this->m_root;
}

bool console::command(std::string input)
{
	std::vector<std::string> args = utils::split(input, ' ');
	std::string ctrls;
	ctrls.push_back(static_cast<char>(19));
	if (args[0] == "ls")
		bool result = this->ls();
	else if (args[0] == "mkdir")
	{
		if (args.size()>1)
		{
			unsigned int i = 1;
			while (args[i].empty())
			{
				i++;
			}
			this->mkdir(args[i]);
		}
	}
	else if (args[0] == "touch")
	{
		if (args.size()>1)
		{
			unsigned int i = 1;
			while (args[i].empty())
			{
				i++;
			}
			if (i + 1 < args.size())
			{
				if (!args[i + 1].empty())
					this->touch(args[i], std::stoi(args[i + 1]));
			}	
			else
				this->touch(args[i]);
		}
	}
	else if (args[0] == "pwd")
	{
		int result = this->pwd();
	}
	else if (args[0] == "pwd")
	{
		int result = this->pwd();
	}
	else if (args[0] == "rm")
	{
		if (args.size()>1)
		{
			unsigned int i = 1;
			while (args[i].empty())
			{
				i++;
			}
			return this->rm(args[i]);
		}
	}
	else if (args[0] == "rmdir")
	{
		if (args.size()>1)
		{
			unsigned int i = 1;
			while (args[i].empty())
			{
				i++;
			}
			return this->rmdir(args[i]);
		}
	}
	else if (args[0] == "cd")
	{
		if (args.size()>1)
		{
			unsigned int i = 1;
			while (args[i].empty())
			{
				i++;
			}
			return this->cd(args[i]);
		}
	}
	else if (args[0] == "export")
	{
		std::string generated = this->list_file(this->m_root, 1) + "\r\n";
		std::fstream output;
		output.open("file.json", std::ios::out | std::ios::binary);
		std::cout << generated;
		output << "{\r\n" + generated + "}\r\n";
		output.close();
	}
	else if (args[0] == "quit")
	{
		return this->quit();
	}
	else if (args[0] == "clear")
	{
		this->clear();
	}
	else if (args[0].empty())
	{}
	else
	{

		std::cout << " La commmande \"" << "\" n'existe pas ! " << std::endl;
		return false;
	}
	return true;
}

bool console::ls() const
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const unsigned int size = this->m_cur->get_content().size();
	std::cout << " Nombre de fichier et dossier total : " << size << std::endl;

	for (unsigned int i = 0; i < size; i++)
	{
		if (dynamic_cast<directory*>(this->m_cur->get_content()[i]))
		{
			SetConsoleTextAttribute(hConsole, 14);
			std::cout << " " << this->m_cur->get_content()[i]->get_name() << "/\t";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 13);
			std::cout << " " << this->m_cur->get_content()[i]->get_name() << "\t";
		}
		SetConsoleTextAttribute(hConsole, 0);
	}
	std::cout << "\n\r";
	return true;
}

bool console::mkdir(const std::string& name) const
{
	if (utils::name_check(name))
		this->m_cur->add_dir(name);
	else
		return false;
	return true;
}

bool console::touch(const std::string& name, ullong size) const
{
	if (utils::name_check(name))
		this->m_cur->add_file(name,size);
	else
		return false;
	return true;
}

bool console::pwd() const
{
	std::cout << " " << PATH << std::endl;
	return true;
}

bool console::rm(std::string path) const
{
	if (!path.empty())
	{
		if (!this->m_cur->find(path))
		{
			std::cout << " Ce fichier n'existe pas ! " << std::endl;
			return false;
		}
		if (dynamic_cast<directory*>(this->m_cur->find(path))){
			std::cout << " Vous ne pouvez pas supprimer " << path << " car c'est un dossier ! " << std::endl;
			return false;
		} else
		{
			this->m_cur->remove_elem(path);
		}
	} 
	else
	{
		return false;
	}
	return true;
}

bool console::rmdir(std::string path) const
{
	if (!path.empty())
	{
		if (!this->m_cur->find(path))
		{
			std::cout << " Ce dossier n'existe pas ! " << std::endl;
			return false;
		}
		if (!dynamic_cast<directory*>(this->m_cur->find(path))) {
			std::cout << " Vous ne pouvez pas supprimer " << path << " car c'est un fichier ! " << std::endl;
			return false;
		}
		else
		{
			this->m_cur->remove_elem(path);
		}
	}
	else
	{
		return false;
	}
	return true;
}

bool console::cd(const std::string& path)
{
	const unsigned int size = this->m_cur->get_content().size();
	if (path == "..")
	{
		vstring tmp;
		if (this->m_cur->get_parent() != nullptr)
		{
			tmp = utils::split(this->PATH, '/');
			tmp.pop_back();
			this->PATH = utils::join(tmp, '/');
			this->m_cur = dynamic_cast<directory*>(this->m_cur->get_parent());
		}
	} else if (path == ".")
	{}
	else
	{
		if (!this->m_cur->find(path))
		{
			vstring tmp = utils::split(path, '/');
			if (tmp[0] == this->m_root->get_name())
			{
				directory* cursor = this->m_root;
				bool asFailed = false;
				for (unsigned int i = 1; i<tmp.size(); i++)
				{
					if (cursor->find(tmp[i]))
						cursor = dynamic_cast<directory*>(cursor->find(tmp[i]));
					else
					{
						std::cout << " le fichier \"" << tmp[i] << "\" n'existe pas " << std::endl;
						asFailed = true;
						break;
					}
				}
				if (!asFailed)
				{
					this->m_cur = cursor;
					this->PATH = path;
					return true;
				}
			}
			else if (tmp[0] == ".." || tmp[0] == ".")
			{
				directory* dtmp = this->m_cur;
				std::string stmp = this->PATH;
				bool result = true;
				for (unsigned int i = 0;i < tmp.size(); i++)
				{
					result = this->cd(tmp[i]);
				}
				if (!result)
				{
					this->m_cur = dtmp;
					this->PATH = stmp;
					return false;
				}
				else
				{
					return true;
				}
				
			}
			std::cout << " \"" << path << "\" n'existe pas ! " << std::endl;
			return false;
		}
		if (dynamic_cast<directory*>(this->m_cur->find(path))){
			this->m_cur = dynamic_cast<directory*>(this->m_cur->find(path));
			this->PATH += path + "/";
		}
		else
		{
			std::cout << " Le fichier \"" << path << "\" n'est pas un dossier ! " << std::endl;
			return false;
		}
	}
	
	return true;
}

bool console::quit()
{
	this->logout = true;
	return true;
}

void console::clear()
{
	system("cls");
}

directory* console::get_root()
{
	return this->m_root;
}

directory* console::get_cur()
{
	return this->m_cur;
}

std::string console::get_path()
{
	return this->PATH;
}

bool console::start()
{
	std::string cmd;
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (!this->logout)
	{
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << " root@thefakepc: ";
		SetConsoleTextAttribute(hConsole, 11);
		std::cout << "[ " << this->get_path() << " ] ~$  ";
		SetConsoleTextAttribute(hConsole, 15);
		std::getline(std::cin, cmd);
		this->command(cmd);
		cmd.clear();
	}
	return true;
}

std::string console::list_file(file* fichier, int state)
{
	std::string liste,tab,type;
	const std::string newline = "\r\n";
	for (int i = 0; i < state; i++)
		tab += "\t";
	const std::string tabm = tab;
	liste += tab +"\""+ fichier->get_name() + "\"" + " : {" + newline;
	tab += "\t";
	if (dynamic_cast<directory*>(fichier))
		type = "directory";
	else
		type = "file";
	liste += tab + "\"" + "-type" + "\"" + ":" + "\"" + type + "\"" + "," + newline;
	liste += tab + "\""+ "-ext" + "\"" + ":" + "\"" + fichier->get_ext() + "\"" + "," + newline;

	if (type == "directory")
	{
		liste += tab + "\"" + "-size" + "\"" + ":" +"\"" + std::to_string(fichier->get_size()) + "\"" + "," + newline;
		directory* tmp = dynamic_cast<directory*>(fichier);
		liste += tab + "\"" + "content" + "\"" + ": {" + newline;
		for (unsigned int i = 0; i<tmp->get_content().size(); i++)
		{
			liste += list_file(tmp->get_content()[i], state+2);
			if (i < tmp->get_content().size()-1)
				liste += ",";
			liste += newline;
		}
		liste += tab + "}" + newline;
	}
	else
		liste += tab + "\"" + "-size" + "\"" + ":" + "\"" + std::to_string(fichier->get_size()) + "\"" + newline;
	liste += tabm + "}";
	return liste;
}