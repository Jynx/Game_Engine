#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

namespace Sengine {
	void FatalError(const std::string& errorString) {
		int tmp;
		std::cout << errorString << std::endl;
		std::cout << "Enter any key to quit" << std::endl;
		std::cin >> tmp;
		SDL_Quit(); // does this actually quit?
		exit(1); // temporary perhaps
	}
}
