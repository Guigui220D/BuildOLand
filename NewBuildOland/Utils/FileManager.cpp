#include "FileManager.h"
#include <Windows.h>
#include <sstream>
#include <iterator>

FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

//Creates a folder and returns true if success
//(Windows only)
bool FileManager::createFolder(std::string folderName) {

	std::vector<std::string> folders = split(folderName, '/');

	//Create a new folder every step
	for (unsigned int i = 0; i < folders.size(); i++) {

		if(folders[i] == "." || folders[i] == "..") {
			//It's not a valid folder, so don'text create a new folder
			continue;
		}

		//Create the path to the folder
		std::string folderToCreate = "";
		for(unsigned int j = 0; j <= i; j++) {
			folderToCreate += folders[j] + "/";
		}

		//Create the folder
		std::cout << folderToCreate << std::endl;

		if (CreateDirectoryA(folderToCreate.c_str(), NULL)) {
			//Success folder created
		} else if (GetLastError() == ERROR_ALREADY_EXISTS) {
			continue;
		} else {
			std::cout << "Error : Could not create folder " << folderToCreate << std::endl;
			//Could not create the folder
			return false;
		}

	}

	//Sucess, all the folder have been created
	return true;
}


const std::vector<std::string> FileManager::split(const std::string& s, const char& c) {
	std::string buff{""};
	std::vector<std::string> v;

	//For each character in the string
	//If it isn'text equal to the character c, add it to the buff
	//Else : add the buff to the array and reset the buff
	for(auto n:s) {
		if (n != c) {
			buff += n;
		} else if (n == c && buff != "") {
			v.push_back(buff);
			buff = "";
		}
	}
	if(buff != "") {
		v.push_back(buff);
	}

	//Finally return the array
	return v;
}





