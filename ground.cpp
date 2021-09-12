#include "header.h"
#include "ground.h"

Ground::Ground(int x, int y, int w, int h, GroundType colour, int onTargetX, int onTargetY, Uint8 r, Uint8 g, Uint8 b) {
    //Initializes the rectangle dimensions
    mRect.x = x;
    mRect.y = y;
    mRect.w = w;
    mRect.h = h;

    //Initializes the ground type
    mColour = colour;

    //Initializes the target position
    mTargetX = x;
    mTargetY = y;

    //Initializes the velocity
    mVelX = 0;
    mVelY = 0;

    //Initiailizes the on/off targets
    mOnTargetX = onTargetX;
    mOnTargetY = onTargetY;
    mOffTargetX = x;
    mOffTargetY = y;

    //Initializes the RGB colour
    mR = r;
    mG = g;
    mB = b;

    //Initializes the on variable
    mIsOn = false;
}

void Ground::resetOnOff() {
    //Reset the target and variable to off
    mTargetX = mOffTargetX;
    mTargetY = mOffTargetY;
    mIsOn = false;
}

void Ground::setTarget(bool on) {
    //If the lever/pusher is on
    if (on) {
        //Set the target and on variable
        mTargetX = mOnTargetX;
        mTargetY = mOnTargetY;
        mIsOn = true;
    }
}

void Ground::move(Player* player1, Player* player2/*SDL_Rect playerRect1, SDL_Rect playerRect2*/) {
    //The player rectangles
    SDL_Rect playerRect1 = player1->getRect();
    SDL_Rect playerRect2 = player2->getRect();

    //Temp variables for block velocity
    mVelX = 0;
    mVelY = 0;

    //Set the velocity if the target is not the current x-position
    if (mTargetX < mRect.x) {
        mVelX -= 1;
    } else if (mTargetX > mRect.x) {
        mVelX += 1;
    }

    //Move the block
    mRect.x += mVelX;

    //If the block collided
    if (checkCollision(playerRect1, mRect) || checkCollision(playerRect2, mRect)) {
        mRect.x -= mVelX;
    }

    //Set the velocity if the target is not the current y-position
    if (mTargetY < mRect.y) {
        mVelY -= 1;
    } else if (mTargetY > mRect.y) {
        mVelY += 1;
    }

    //Move the block
    mRect.y += mVelY;

    //If the block collided with the first player
    if (checkCollision(playerRect1, mRect)) {
        //If the block is above the player
        if (mVelY > 0) {
            //Stop the block
            mRect.y -= mVelY;
        }
        //If the player is above the block
        else if (mVelY <= 0) {
            //Adjust the player velocity to move up
            player1->adjustVel(mVelY);
        }
    }

    //If the block collided with the second player
    if (checkCollision(playerRect2, mRect)) {
        //If the block is above the player
        if (isAbove(mRect, playerRect2)) {
            //Stop the block
            mRect.y -= mVelY;
        } else {
            if (mVelY > 0) {
                player2->adjustVel(mVelY);
            }
            //If the player is above the block
            else if (mVelY <= 0) {
                //Adjust the player velocity to move up
                player2->adjustVel(mVelY);
            }
        }
    }
}

void Ground::render() {
    //The colour variables
    Uint8 r = 0x00, b = 0x00, g = 0x00, a = 0xFF;

    //Sets the colour variables based on the colour of the object
    switch (mColour) {
        case GROUND_TYPE_BASIC:
            r = 0x88;
            b = 0x88;
            g = 0x88;
        case GROUND_TYPE_RED:
            r = 0x88;
            break;
        case GROUND_TYPE_BLUE:
            b = 0x88;
            break;
        case GROUND_TYPE_GREEN:
            g = 0x88;
            break;
        default:
            break;
    }

    //Render the rectangle
    SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
    SDL_RenderFillRect(gRenderer, &mRect);

    //If it is moveable (has a positve target)
    if (mOnTargetX != -1) {
        //Set variables for the inner coloured rectangle
        SDL_Rect innerRect = mRect;
        innerRect.x += 2;
        innerRect.y += 2;
        innerRect.w -= 4;
        innerRect.h -= 4;

        //Set colour and render inner coloured rectangle
        SDL_SetRenderDrawColor(gRenderer, mR, mG, mB, a);
        SDL_RenderFillRect(gRenderer, &innerRect);

        //Set variables for the status rectangle
        SDL_Rect statusRect = innerRect;
        statusRect.x += 2;
        statusRect.y += 2;
        statusRect.w -= 4;
        statusRect.h -= 4;

        //Set colour and render status rectangle
        if (mIsOn) {
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0x88, 0x00, 0xFF);
        } else {
            SDL_SetRenderDrawColor(gRenderer, 0x88, 0x00, 0x00, 0xFF);
        }
        SDL_RenderFillRect(gRenderer, &statusRect);
    }
}

SDL_Rect Ground::getRect() {
    return mRect;
}

GroundType Ground::getColour() {
    return mColour;
}

int Ground::getXVel() {
    return mVelX;
}

int Ground::getYVel() {
    return mVelY;
}
