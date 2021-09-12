#pragma once
#include <SDL.h>

enum LeverType {
    LEVER_TYPE_LEVER,
    LEVER_TYPE_PUSHER
};

//Levers and switches class
class Lever {
    public:
        //Create and intiializes lever
        Lever(int x, int y, LeverType type, unsigned int groundIndex, Uint8 r = 0x88, Uint8 g = 0x00, Uint8 b = 0x88, bool onDir = true);

        //Get input for pushers
        void getPusherInput(SDL_Rect playerRect1, SDL_Rect playerRect2);

        //Get input for levers
        void getLeverInput(SDL_Rect playerRect1, SDL_Rect playerRect2);

        //Renders the lever
        void render();

        //Gets the base rectangle
        SDL_Rect getRect();

        //Gets the on/off status
        bool getOnStatus();

        //Gets the list index
        unsigned int getGroundIndex();

    private:
        //The base rectangle
        SDL_Rect mRect;

        //The current state of the rectangle
        bool mIsOn;

        //If the block is being touched by the player
        bool mTouchingA, mTouchingB;

        //The colour of the outline rectangle
        Uint8 mR, mG, mB;

        //The type of lever (pusher/lever)
        LeverType mType;

        //The ground index position
        unsigned int mGroundIndex;

        //The on/off direction
        bool onDirStandard;
};
