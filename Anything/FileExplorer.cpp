#include "FileExplorer.h"

void FileExplorer::commandMenu(std::vector<std::string> vec_dir_files, std::string dir)
{
	for (int i = 0; i != vec_dir_files.size(); i++)
	{
		printf("[%i]%s\n", i, vec_dir_files[i].c_str());
	}

	std::cout << std::endl;
	std::cout << "Input {file number} {commmand} {extra arguments}" << std::endl;
	std::cout << "Commands: \nd - Delete\nh - Hide\nu - unhide\ne - enter" << std::endl;
	std::cout << "Example: 0 d (Deletes the first file listed)" << std::endl << std::endl;
	std::cout << "Command: ";
	int file;
	char operation;
	std::cin >> file >> operation;
	std::string selectedFile = vec_dir_files[file];

	switch (operation)
	{
		case 'd': //remove the file
			remove(selectedFile.c_str());
			break;
		case 'h':
			util::file_change_attributes(selectedFile, util::file_hidden);
			break;
		case 'u':
			util::file_change_attributes(selectedFile, util::file_normal);
			break;
		case 'e':
			getDir(selectedFile);
			break;
		default:
			std::cout << "Incorrect command\n\n";
			commandMenu(vec_dir_files, dir);
			break;
	}

	getDir(selectedFile.substr(0, selectedFile.find_last_of('\\')));
}

void FileExplorer::getDir(std::string dir)
{
	std::vector<std::string> vec_dir_files;
	int counter = 0;

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

		if (std::experimental::filesystem::is_directory(fpath))
			fpath += '\\';

		vec_dir_files.push_back(fpath);
		counter++;
	}
	commandMenu(vec_dir_files, dir);
}

void FileExplorer::getFileSize(std::experimental::filesystem::path const& dir)
{
	try
	{
		if (std::experimental::filesystem::is_directory(dir))
		{
			for (const auto& entry : std::experimental::filesystem::directory_iterator(dir))
			{
				if (std::experimental::filesystem::is_directory(entry.path()))
				{
					getFileSize(entry.path());
				}
				else
				{
					std::cout << entry.path() << "\t\t" << std::experimental::filesystem::file_size(entry.path()) * 0.0009765625 << "\n"; //temp output in KB
				}
			}
		}
		else
		{
			std::cout << dir << "\t\t" << std::experimental::filesystem::file_size(dir) * 0.0009765625 << "\n"; //temp output in KB
		}
	}
	catch (const std::exception& e) { std::cout << e.what(); }
}

void FileExplorer::dirChoose()
{
	std::string chosenDir;
	std::cout << "Please input a directory path to open: " << std::endl;
	std::cin >> chosenDir;
	getDir(chosenDir);
}

int main()
{
	FileExplorer::dirChoose();
}
