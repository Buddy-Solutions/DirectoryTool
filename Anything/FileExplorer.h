#pragma once
#include "stdafx.h"
#include "util.h"

namespace FileExplorer
{
	void commandMenu(std::vector<std::string> vec_dir_files, std::string dir);
	void getDir(std::string dir);
	void getFileSize(std::experimental::filesystem::path const& dir);
	void dirChoose();
}