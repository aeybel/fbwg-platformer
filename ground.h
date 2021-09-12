#pragma once
#include "player.h"
#include <SDL.h>

class Player;

//Enumeration for ground types
enum GroundType {
    GROUND_TYPE_BASIC,
    GROUND_TYPE_RED,
    GROUND_TYPE_BLUE,
    GROUND_TYPE_GREEN,
    GROUND_TYPE_TOTAL
};

//Class for floor types
class Ground {
    public:
        //Initializes the variables
        Ground(int x, int y, int w, int h, GroundType colour, int onTargetX = -1, int onTargetY = -1, Uint8 r = 0, Uint8 g = 0, Uint8 b = 0);

        //Resets the on variable to off
        void resetOnOff();

        //Sets the on/off and target position
        void setTarget(bool on);

        //Move towards the target position
        void move(Player* player1, Player* player2);

        //Render the image on the screen
        void render();

        //Gets the base rectangle
        SDL_Rect getRect();

        //Gets the ground type
        GroundType getColour();

        //Gets the velocities
        int getXVel();
        int getYVel();

    private:
        //The rectangle
        SDL_Rect mRect;

        //The colour of the rectangle
        GroundType mColour;

        //The target position to move to
        int mTargetX, mTargetY;

        //The current block velocity
        int mVelX, mVelY;

        //The on and off target positions
        int mOnTargetX, mOnTargetY;
        int mOffTargetX, mOffTargetY;

        //The on/off position
        bool mIsOn;

        //The colour corresponding to a lever
        Uint8 mR, mG, mB;
};
