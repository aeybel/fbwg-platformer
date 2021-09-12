///UNUSED DOCUMENT DUE TO MANY, MANY, MANY BUGS
#pragma once
#include "ground.h"
#include <SDL.h>
#include <vector>

//Class for pushable blocks
class Block {
    public:
        //The block dimensions
        static const int BLOCK_WIDTH = 20;
        static const int BLOCK_HEIGHT = 20;

        //Initializes the variables
        Block(int x, int y);

        //Moves the block
        void move(int playerVelX, std::vector<Ground> walls);

        //Makes the block fall
        void fall(std::vector<Ground> walls);

        //Renders the block
        void render();

        //Returns the base rectangle
        SDL_Rect getRect();

    private:
        //The base rectangle
        SDL_Rect mRect;

        //The Y velocity
        double mVelY;
};
