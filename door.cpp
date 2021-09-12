#include "header.h"
#include "door.h"

Door::Door(SpriteType sprite) {
    //Set the variables for the base rectangle
    mRect.x = 0;
    mRect.y = 0;
    mRect.w = DOOR_WIDTH;
    mRect.h = DOOR_HEIGHT;

    //Set the door sprite based on the player sprite
    mPlayerSprite = sprite;
}

void Door::loadDoorPos(int level) {
    //If the corresponding sprite is the red sprite
    if (mPlayerSprite == RED_PLAYER_SPRITE) {
        //Set the door posiiton based on the level
        switch (level) {
            case -1:
                mRect.x = 300;
                mRect.y = 190;
                break;
            case 0:
                mRect.x = 190;
                mRect.y = 180;
                break;
            case 1:
                mRect.x = 510;
                mRect.y = 50;
                break;
            case 2:
                mRect.x = 30;
                mRect.y = 40;
                break;
            case -3:
                mRect.x = 510;
                mRect.y = 200;
                break;
            case 3:
                mRect.x = 480;
                mRect.y = 410;
                break;
            case 4:
                mRect.x = 580;
                mRect.y = 280;
                break;
        }
    }
    //If the corresponding sprite is the blue sprite
    else {
        //Set the door position based on the level
        switch (level) {
            case -1:
                mRect.x = 350;
                mRect.y = 190;
                break;
            case 0:
                mRect.x = 140;
                mRect.y = 180;
                break;
            case 1:
                mRect.x = 560;
                mRect.y = 50;
                break;
            case 2:
                mRect.x = 80;
                mRect.y = 40;
                break;
            case -3:
                mRect.x = 100;
                mRect.y = 400;
                break;
            case 3:
                mRect.x = 520;
                mRect.y = 410;
                break;
            case 4:
                mRect.x = 20;
                mRect.y = 370;
                break;
        }
    }
}

void Door::render() {
    //Adjusts the colour
    if (mPlayerSprite == RED_PLAYER_SPRITE) {
        SDL_SetRenderDrawColor(gRenderer, 0x44, 0x00, 0x00, 0xFF);
    } else {
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x44, 0xFF);
    }

    //Render the rectangle
    SDL_RenderFillRect(gRenderer, &mRect);
}

SDL_Rect Door::getRect() {
    return mRect;
}
