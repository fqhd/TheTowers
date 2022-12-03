#include "FilePathManager.hpp"
#include <filesystem>

std::string rootDirectory;

std::string getProjectRootDirectory(){
	std::string path;
	std::cout << "This is a workaround to executables ending up in different folder locations on different Operating Systems." << std::endl;
	std::cout << "You will only be prompted to enter this once." << std::endl;
	std::cout << "Enter the absolute path to the root folder of the project: ";
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