#pragma once
#include <string>

class IOManager {
public:
	static bool ReadFileToBuf(unsigned char*& buffer, const std::string& filepath, int& bufSize);

};