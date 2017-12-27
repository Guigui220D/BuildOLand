#pragma once
#include <iostream>
#include <vector>

class FileManager
{
public:
	FileManager();
	~FileManager();

	static bool createFolder(std::string folderName);
	static const std::vector<std::string> split(const std::string& s, const char& c);
	
};