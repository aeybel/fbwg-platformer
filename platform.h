#pragma once
#include <SDL.h>

class Platform {
    public:
        //Initializes the variables
        Platform(int x, int y, int w, int h);

        //Renders the image on the screen
        void render();

        //Get the rectangle
        SDL_Rect getRect();

    private:
        //The base rectangle
        SDL_Rect mRect;
};
