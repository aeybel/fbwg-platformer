#include "header.h"
#include "lever.h"

Lever::Lever(int x, int y, LeverType type, unsigned int groundIndex, Uint8 r, Uint8 g, Uint8 b, bool onDir) {
    //Set the xy position
    mRect.x = x;
    mRect.y = y;

    //Set the lever height and width (constant)
    mRect.h = 15;
    mRect.w = 15;

    //Set the on position
    mIsOn = false;

    //Set the touched variable
    mTouchingA = false;
    mTouchingB = false;

    //Initialize the colours
    mR = r;
    mG = g;
    mB = b;

    //Set the lever's type
    mType = type;

    //Set the ground index of the lever
    mGroundIndex = groundIndex;

    //Set the on direction
    onDirStandard = onDir;
}

void Lever::getPusherInput(SDL_Rect playerRect1, SDL_Rect playerRect2) {
    //If one of them is collided
    if (checkCollision(mRect, playerRect1) || checkCollision(mRect, playerRect2)) {
        //Set true
        mIsOn = true;
    } else {
        //Set false
        mIsOn = false;
    }
}

void Lever::getLeverInput(SDL_Rect playerRect1, SDL_Rect playerRect2) {
    //Checking collision for the first player
    bool firstCollided = checkCollision(mRect, playerRect1);
    bool secondCollided = checkCollision(mRect, playerRect2);

    //If they have collided
    if (firstCollided) {
        //Checks if it is the first time collided
        if (!mTouchingA) {
            //If it collided on the right side
            if (playerRect1.x < mRect.x) {
                if (onDirStandard) {
                    mIsOn = true;
                } else {
                    mIsOn = false;
                }
            }
            //If it collided on the left side
            else if (playerRect1.x > mRect.x) {
                if (onDirStandard) {
                    mIsOn = false;
                } else {
                    mIsOn = true;
                }

            }
        }
        mTouchingA = true;
    } else {
        mTouchingA = false;
    }

    //If they have collided
    if (secondCollided) {
        //Checks if it is the first time collided
        if (!mTouchingB) {
            //If it collided on the right side
            if (playerRect2.x < mRect.x) {
                if (onDirStandard) {
                    mIsOn = true;
                } else {
                    mIsOn = false;
                }
            }
            //If it collided on the left side
            if (playerRect2.x > mRect.x) {
                if (onDirStandard) {
                    mIsOn = false;
                } else {
                    mIsOn = true;
                }
            }
        }
        mTouchingB = true;
    } else {
        mTouchingB = false;
    }
}

void Lever::render() {
    //If it is a lever type
    if (mType == LEVER_TYPE_LEVER) {
        //Set the variables for the left inset rectangle
        SDL_Rect leftSmallRect = mRect;
        leftSmallRect.x += 3;
        leftSmallRect.y += 3;
        leftSmallRect.w /= 2;
        leftSmallRect.w -= 3;
        leftSmallRect.h -= 6;

        //Set the variables for the right inset rectangle
        SDL_Rect rightSmallRect = mRect;
        rightSmallRect.x += rightSmallRect.w/2;
        rightSmallRect.y += 3;
        rightSmallRect.w /= 2;
        rightSmallRect.w -= 3;
        rightSmallRect.h -= 6;

        //Render the large rectangle
        SDL_SetRenderDrawColor(gRenderer, mR, mG, mB, 0xFF);
        SDL_RenderFillRect(gRenderer, &mRect);

        //Set and render the small rectangles based on on status
        if ((mIsOn && onDirStandard) || (!mIsOn && !onDirStandard)) {
            //Render a red rectangle on the left
            SDL_SetRenderDrawColor(gRenderer, 0xBB, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(gRenderer, &leftSmallRect);
            //Render a green rectangle on the right
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xBB, 0x00, 0xFF);
            SDL_RenderFillRect(gRenderer, &rightSmallRect);
        } else {
            //Render a green rectangle on the left
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xBB, 0x00, 0xFF);
            SDL_RenderFillRect(gRenderer, &leftSmallRect);
            //Render a red rectangle on the right
            SDL_SetRenderDrawColor(gRenderer, 0xBB, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(gRenderer, &rightSmallRect);
        }
    }
    //If it is a pusher type
    else if (mType == LEVER_TYPE_PUSHER) {
        //Set variables for the smaller inset rectangle
        SDL_Rect smallRect = mRect;
        smallRect.x += 3;
        smallRect.y += 3;
        smallRect.w -= 6;
        smallRect.h -= 6;

        //Render the big rectangle
        SDL_SetRenderDrawColor(gRenderer, mR, mG, mB, 0xFF);
        SDL_RenderFillRect(gRenderer, &mRect);

        //Render the small rectangle, based on on/off
        if (mIsOn) {
            //Set the colour to green
            SDL_SetRenderDrawColor(gRenderer, 0x00, 0xBB, 0x00, 0xFF);
        } else {
            //Set the colour to red
            SDL_SetRenderDrawColor(gRenderer, 0xBB, 0x00, 0x00, 0xFF);
        }
        SDL_RenderFillRect(gRenderer, &smallRect);
    }
}

SDL_Rect Lever::getRect() {
    return mRect;
}

bool Lever::getOnStatus() {
    return mIsOn;
}

unsigned int Lever::getGroundIndex()
{
    return mGroundIndex;
}
