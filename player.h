#pragma once
#include "spritetypes.h"
#include "ground.h"
#include "lever.h"
#include "blocks.h"
#include <SDL.h>
#include <vector>
#include <iostream>

class Lever;

//Player class
class Player {
    public:
        //The dimensions of the player sprite
        static const int PLAYER_WIDTH = 20;
        static const int PLAYER_HEIGHT = 20;

        //Maximum axis velocity of the player
        static const int PLAYER_VEL = 3;

        //Jump velocity
        static const int PLAYER_JUMPVEL = 12;

        //The boarder for the collider
        static const int PLAYER_COLLIDER_BOARDER = 4;

        //Initializes the variables
        Player(SpriteType sprite);

        //Takes events
        void handleEvent(SDL_Event& e, std::vector<Ground>& walls);

        //Moves the player, returns false if player dies
        bool move(std::vector<Ground> walls, int wallVelY , std::vector<Lever> levers/*, Block myBlock*/);

        //Shows the player sprite on the screen
        void render();

        //Loads the player position for the levels
        void loadPlayerPos(int level);

        //Gets the base rectangles
        SDL_Rect getRect();

        //Adjusts the player velocity based on a wall velocity
        void adjustVel(int wallVelY);

    private:
        //The X and Y offsets of the player
        int mPosX, mPosY;

        //The velocity of the player
        double mVelX, mVelY;

        //Player base rectangle
        SDL_Rect mRect;

        //Player collision boxes
        std::vector<SDL_Rect> mColliders;

        //Link to player sprite
        SpriteType mSprite;
};
