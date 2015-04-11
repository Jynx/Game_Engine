#include "IOManager.h"
#include "Errors.h"
#include <fstream>

bool IOManager::ReadFileToBuf(unsigned char*& buffer,
                             const std::string& filepath, int& bufSize) {
    std::ifstream file(filepath, std::ios::binary);
    if (file.fail()) {
        perror(filepath.c_str());
        return false;
    }

    // seek to end of file, 1:offset 2: seek to beg or end
    // then get file size.
    file.seekg(0, std::ios::end);
    int fileSize = file.tellg();  // grab size.
    file.seekg(0, std::ios::beg);

    fileSize -= file.tellg();  // subtract size of file header.
	buffer = new unsigned char[fileSize];
    // trick to get address of first element of buffer as a c_str + bytes to
    // read
    file.read((char*)buffer, fileSize);
    file.close();
    bufSize = fileSize;

    return true;
}