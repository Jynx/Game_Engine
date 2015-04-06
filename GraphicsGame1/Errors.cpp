#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>

void FatalError(std::string errorString) {
    int tmp;
    std::cout << errorString << std::endl;
    std::cout << "Enter any key to quit" << std::endl;
    std::cin >> tmp;
    SDL_Quit();
}
