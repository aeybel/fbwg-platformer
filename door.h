#pragma once
#include "spritetypes.h"
#include <SDL.h>

//Class for level-ending doors
class Door {
    public:
        //The dimensions of the door
        static const int DOOR_WIDTH = 25;
        static const int DOOR_HEIGHT = 35;

        //Initializes the variables
        Door(SpriteType sprite);

        //Loads the door position
        void loadDoorPos(int level);

        //Renders the door
        void render();

        //Gets the base rectangle
        SDL_Rect getRect();

    private:
        //The base rectangle
        SDL_Rect mRect;

        //The player sprite it is for
        SpriteType mPlayerSprite;
};
