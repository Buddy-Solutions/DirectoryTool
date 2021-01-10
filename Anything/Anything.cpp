#include <iostream>
#include <vector>
#include <Windows.h>

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING 
#include <experimental/filesystem>

int indexOf(std::vector<std::string> vec, std::string value)
{
	int counter = -1;
	for (int i = 0; i != vec.size(); i++)
	{
		counter++;
		if (vec[i] == value)
			return counter;
	}
}

std::vector<std::string> vec_paths;
std::vector<std::string> vec_logged;

bool alreadyLogged(std::string path)
{
	for (std::string x : vec_logged)
	{
		if (x == path)
			return true;
	}
	return false;
}

void displayDir(std::string dir)
{
	for (const auto& entry : std::experimental::filesystem::directory_iterator(dir))
	{
		auto path = entry.path();
		auto fpath = entry.path().parent_path().generic_string() + "\\" + entry.path().filename().generic_string();				

		//Normalize path
		for (int i = 0; i != fpath.size(); i++)
		{
			if (fpath[i] == '/')
				fpath[i] = '\\';

		}

		if (std::experimental::filesystem::is_directory(path))
		{
			fpath += "\\";
			vec_paths.push_back(fpath);
		}

		if (alreadyLogged(fpath))
		{
			std::cout << "Finished" << std::endl;
			while (true)
			{
				Sleep(10000);
			}
		}

		if (fpath.find("C:\\Windows") != std::string::npos)
		{
			continue;
		}

		if (fpath.find("nigger.txt") != std::string::npos)
		{
			std::cout << "Nigger spotted" << std::endl;
			Sleep(3000);
		}

		std::cout << fpath << std::endl;
		vec_logged.push_back(fpath);
	}
}

int main()
{
	displayDir("C:\\");	
	for (int i = 0; i != vec_paths.size(); i++)
	{
		displayDir(vec_paths[i]);
	}
}