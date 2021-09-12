#pragma once
#include <SDL.h>
#include <iostream>

//Texture wrapper class
class LTexture {
    public:
        //Initializes variables
        LTexture();

        //Deallocates memory
        ~LTexture();

        //Loads image at specified path
        bool loadFromFile(std::string path);

        //Deallocates texture
        void free();

        //Renders texture at given point
        void render(int x, int y, SDL_Rect* clip = NULL);

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;
};
