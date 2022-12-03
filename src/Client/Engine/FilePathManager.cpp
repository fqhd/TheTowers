#include "FilePathManager.hpp"
#include <filesystem>
#include <fstream>

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
	std::ifstream is("RootDirPath.txt");
	if(is.fail()){
	    rootDirectory = getProjectRootDirectory();
		std::ofstream os("RootDirPath.txt");
		if(os.fail()){
			std::cout << "FilePathManager:: Couldn't create RootDirPath.txt" << std::endl;
		}else{
			os << rootDirectory << std::endl;
		}
		os.close();
	}else{
		is >> rootDirectory;
	}
	is.close();
}

const std::string& FilePathManager::getRootFolderDirectory(){
    return rootDirectory;
}