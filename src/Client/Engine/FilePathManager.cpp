#include "FilePathManager.hpp"
#include <filesystem>

std::string rootDirectory;

std::string getProjectRootDirectory(){
	std::string path;
	std::cout << "Enter your root folder: ";
	std::cin >> path;
	while(!std::filesystem::is_directory(std::filesystem::path(path))){
		std::cout << "That is not a valid path, try again: ";
		std::cin >> path;
	}
	return path;
}

void FilePathManager::init(){
    rootDirectory = getProjectRootDirectory();
}

const std::string& FilePathManager::getRootFolderDirectory(){
    return rootDirectory;
}