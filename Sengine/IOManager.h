#pragma once
#include <string>

namespace Sengine {
	class IOManager {
	public:
		static bool ReadFileToBuf(unsigned char*& buffer, const std::string& filepath, int& bufSize);

	};
}