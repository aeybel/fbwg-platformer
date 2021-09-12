///UNUSED DOCUMENT DUE TO MANY, MANY, MANY BUGS
#include "header.h"
#include "blocks.h"

Block::Block(int x, int y) {
    //Initialize the rectangle
    mRect.x = x;
    mRect.y = y;
    mRect.w = BLOCK_WIDTH;
    mRect.h = BLOCK_HEIGHT;

    //Initialize the velocity
    mVelY = 0;
}

void Block::move(int playerVelX, std::vector<Ground> walls) {
    //std::cout << playerVelX << 'd';
    //std::cout << playerVelX;
    mRect.x += playerVelX;
    std::cout << mRect.x;
    /*if (playerVelX < 0) {
        mRect.x -= 3;
    } else if (playerVelX > 0) {
        mRect.x += 3;
    }
    std::cout << "AGHf";*/
    /*for (int i = 0; i < walls.size(); i++) {
        if (isRightCollided(mRect, walls[i].getRect()) || isLeftCollided(mRect, walls[i].getRect())) {
            mRect.x -= playerVelX;
            return false;
        }
    }*/
    //return true;
}

/*
void Block::move(SDL_Rect playerRect, std::vector<Ground> walls) {
    if (checkCollision(playerRect, mRect)) {
        int tempVel = 0;
        if (isLeftCollided(playerRect, mRect)) {
            //tempVel += 5;
            //mRect.x = playerRect.x+playerRect.w;
            tempVel += 3;
        } else if (isRightCollided(playerRect, mRect)) {
            //tempVel -= 5;
            //mRect.x = playerRect.x-mRect.w;
            tempVel -= 3;
        }

        //mRect.x += tempVel;
        for (int i = 0; i < walls.size(); i++) {
            if (checkCollision(mRect, walls[i].getRect())) {
                if (isLeftCollided(mRect, walls[i].getRect()) || isRightCollided(mRect, walls[i].getRect())) {
                    mRect.x -= tempVel;
                }
                //mRect.x -= playerRect.w;
                break;
            }
        }
    }

    mRect.y += 1;
    for (int i = 0; i < walls.size(); i++) {
        if (checkCollision(mRect, walls[i].getRect())) {
            mRect.y -= 1;
            break;
        }
    }
}*/

void Block::fall(std::vector<Ground> walls) {
    mRect.y += mVelY;

    bool above = false;
    for (int i = 0; i < walls.size(); i++) {
        if (checkCollision(mRect, walls[i].getRect())) {
            mRect.y -= mVelY;
            above = true;
            break;
        }
    }

    if (!above) {
        std::cout << "nope";
        mVelY += GRAVITATIONAL_CONSTANT;
    } else {
        std::cout << "yep";
        mVelY = 0;
    }
}

void Block::render() {
    SDL_SetRenderDrawColor(gRenderer, 0xD2, 0x69, 0x1E, 0xFF);
    SDL_RenderFillRect(gRenderer, &this->mRect);
}

SDL_Rect Block::getRect() {
    return mRect;
}
