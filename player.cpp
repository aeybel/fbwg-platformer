#include "player.h"
#include "header.h"

Player::Player(SpriteType sprite) {
    //Initializes the offsets
    mPosX = 0;
    mPosY = 0;

    //Initializes the velocity
    mVelX = 0;
    mVelY = 0;

    //Initializes the rectangle dimensions
    mRect.x = mPosX;
    mRect.y = mPosY;
    mRect.w = PLAYER_WIDTH;
    mRect.h = PLAYER_HEIGHT;

    //Initialize the colliders
    mColliders.resize(2);

    mColliders[0].x = mPosX+PLAYER_COLLIDER_BOARDER;
    mColliders[0].y = mPosY;
    mColliders[0].w = PLAYER_WIDTH-(2*PLAYER_COLLIDER_BOARDER);
    mColliders[0].h = PLAYER_HEIGHT;

    mColliders[1].x = mPosX;
    mColliders[1].y = mPosY+PLAYER_COLLIDER_BOARDER;
    mColliders[1].w = PLAYER_WIDTH;
    mColliders[1].h = PLAYER_HEIGHT-(2*PLAYER_COLLIDER_BOARDER);

    //Intializes sprite type
    mSprite = sprite;
}

void Player::handleEvent(SDL_Event& e, std::vector<Ground>& walls) {
    if (mSprite == RED_PLAYER_SPRITE) {
        //If a key was pressed
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    for (int i = 0; i < walls.size(); i++) {
                        if (walls[i].getRect().y == mRect.y+PLAYER_HEIGHT+1) {
                            //Checks to see if it is on a surface before jumping
                            mVelY -= PLAYER_JUMPVEL;
                            break;
                        }
                    }
                    break;
                case SDLK_LEFT:
                    mVelX -= PLAYER_VEL;
                    break;
                case SDLK_RIGHT:
                    mVelX += PLAYER_VEL;
                    break;
            }
        }
        //If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    mVelX += PLAYER_VEL;
                    break;
                case SDLK_RIGHT:
                    mVelX -= PLAYER_VEL;
                    break;
            }
        }
    } else if (mSprite == BLUE_PLAYER_SPRITE) {
        //If a key was pressed
        if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym) {
                case SDLK_w:
                    for (int i = 0; i < walls.size(); i++) {
                        if (walls[i].getRect().y == mRect.y+PLAYER_HEIGHT+1) {
                            //Checks to see if it is on a surface before jumping
                            mVelY -= PLAYER_JUMPVEL;
                            break;
                        }
                    }
                    break;
                case SDLK_a:
                    mVelX -= PLAYER_VEL;
                    break;
                case SDLK_d:
                    mVelX += PLAYER_VEL;
                    break;
            }
        }
        //If a key was released
        else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
            //Adjust the velocity
            switch (e.key.keysym.sym) {
                case SDLK_a:
                    mVelX += PLAYER_VEL;
                    break;
                case SDLK_d:
                    mVelX -= PLAYER_VEL;
                    break;
            }
        }
    }
}

bool Player::move(std::vector<Ground> walls, int wallVelY, std::vector<Lever> levers) {
    //Player action success flag
    bool alive = true;

    //Move the player left or right
    mPosX += mVelX;
    mRect.x = mPosX;
    mColliders[0].x += mVelX;
    mColliders[1].x += mVelX;

    //The player went too far left or right
    if ((mPosX < BOARDER_WIDTH) || (mPosX + PLAYER_WIDTH > SCREEN_WIDTH - BOARDER_WIDTH)) {
        mPosX -= mVelX;
        mRect.x = mPosX;
        mColliders[0].x -= mVelX;
        mColliders[1].x -= mVelX;
    } else {
        //Checks collisions
        for (int i = 0; i < walls.size(); i++) {
            for (int j = 0; j < 2; j++) {
                if (checkCollision(mColliders[j], walls[i].getRect())) {
                    //Death cases for different types of ground
                    switch (walls[i].getColour()) {
                        case GROUND_TYPE_BASIC:
                            break;
                        case GROUND_TYPE_GREEN:
                            alive = false;
                            break;
                        case GROUND_TYPE_RED:
                            if (mSprite == BLUE_PLAYER_SPRITE) {
                                alive = false;
                            }
                            break;
                        case GROUND_TYPE_BLUE:
                            if (mSprite == RED_PLAYER_SPRITE) {
                                alive = false;
                            }
                            break;
                    }
                    if (walls[i].getRect().y >= mPosY+PLAYER_HEIGHT) {
                        //If the player is directly above a block, make the player move with the block
                        mVelY -= 1;
                    } else {
                        //Moves the player back
                        mPosX -= mVelX;
                        mRect.x = mPosX;
                        mColliders[0].x -= mVelX;
                        mColliders[1].x -= mVelX;
                    }
                    break;
                }
            }
        }
    }

    //Move the player up or down
    mPosY += mVelY;
    mRect.y = mPosY;
    mColliders[0].y += mVelY;
    mColliders[1].y += mVelY;

    //If the player went to far up or down
    if (mPosY < BOARDER_WIDTH) {
        mPosY = BOARDER_WIDTH;
        mRect.y = mPosY;
        mColliders[0].y = BOARDER_WIDTH;
        mColliders[1].y = BOARDER_WIDTH + PLAYER_COLLIDER_BOARDER;
    } else if (mPosY + PLAYER_HEIGHT > SCREEN_HEIGHT) {
        mPosY = SCREEN_HEIGHT - PLAYER_HEIGHT;
        mRect.y = mPosY;
        mColliders[0].y = SCREEN_HEIGHT - PLAYER_HEIGHT;
        mColliders[1].y = SCREEN_HEIGHT - PLAYER_HEIGHT - PLAYER_COLLIDER_BOARDER;
    }
    bool collisions = false;
    //Checks collisions
    for (int i = 0; i < walls.size(); i++) {
        if (checkCollision(mColliders[0], walls[i].getRect())) {
            //Death cases for different types of ground
            switch (walls[i].getColour()) {
                case GROUND_TYPE_BASIC:
                    break;
                case GROUND_TYPE_GREEN:
                    alive = false;
                    break;
                case GROUND_TYPE_RED:
                    if (mSprite == BLUE_PLAYER_SPRITE) {
                        alive = false;
                    }
                    break;
                case GROUND_TYPE_BLUE:
                    if (mSprite == RED_PLAYER_SPRITE) {
                        alive = false;
                    }
                    break;
            }
            //Moves the player back
            if (walls[i].getYVel() != 0) {
                mPosY += walls[i].getYVel();
                mRect.y = mPosY;
                mColliders[0].y += walls[i].getYVel();
                mColliders[1].y += walls[i].getYVel();
            }
            mPosY -= mVelY;
            mRect.y = mPosY;
            mColliders[0].y -= mVelY;
            mColliders[1].y -= mVelY;
            if (isAbove(mColliders[0], walls[i].getRect())) {
                mVelY = 0;
            } else {
                mVelY = 1;
            }
            collisions = true;
        }
        if (checkCollision(mColliders[1], walls[i].getRect())) {
            //Death cases for different types of ground
            switch (walls[i].getColour()) {
                case GROUND_TYPE_BASIC:
                    break;
                case GROUND_TYPE_GREEN:
                    alive = false;
                    break;
                case GROUND_TYPE_RED:
                    if (mSprite == BLUE_PLAYER_SPRITE) {
                        alive = false;
                    }
                    break;
                case GROUND_TYPE_BLUE:
                    if (mSprite == RED_PLAYER_SPRITE) {
                        alive = false;
                    }
                    break;
            }
            //Moves the player back on the x-axis
            mPosX -= mVelX;
            mRect.x = mPosX;
            mColliders[0].x -= mVelX;
            mColliders[1].x -= mVelX;
        }
    }
    //Applies gravity if there are no collisions
    if (!collisions) {
        mVelY += GRAVITATIONAL_CONSTANT;
    }

    return alive;
}

void Player::render() {
    //Show the player
    gPlayerSprites[mSprite].render(mPosX, mPosY);
}

void Player::loadPlayerPos(int level) {
    //If it is the red sprite
    if (mSprite == RED_PLAYER_SPRITE) {
        //Set the position
        switch (level) {
            case -1:
                mPosX = 40;
                mPosY = 225;
                break;
            case 0:
                mPosX = 320;
                mPosY = 225;
                break;
            case 1:
                mPosX = 30;
                mPosY = 420;
                break;
            case 2:
                mPosX = 30;
                mPosY = 420;
                break;
            case -3:
                mPosX = 560;
                mPosY = 50;
                break;
            case 3:
                mPosX = 40;
                mPosY = 40;
                break;
            case 4:
                mPosX = 270;
                mPosY = 60;
                break;
        }
        //Adjust the member variables/rectangles
        mRect.x = mPosX;
        mRect.y = mPosY;
        mColliders[0].x = mPosX+PLAYER_COLLIDER_BOARDER;
        mColliders[0].y = mPosY;
        mColliders[1].x = mPosX;
        mColliders[1].y = mPosY+PLAYER_COLLIDER_BOARDER;
    }
    //If it is the blue sprite
    if (mSprite == BLUE_PLAYER_SPRITE) {
        //Set the position
        switch (level) {
            case -1:
                mPosX = 50;
                mPosY = 225;
                break;
            case 0:
                mPosX = 330;
                mPosY = 225;
                break;
            case 1:
                mPosX = 30;
                mPosY = 360;
                break;
            case 2:
                mPosX = 70;
                mPosY = 420;
                break;
            case -3:
                mPosX = 50;
                mPosY = 250;
                break;
            case 3:
                mPosX = 520;
                mPosY = 40;
                break;
            case 4:
                mPosX = 290;
                mPosY = 60;
                break;
        }
        //Adjust the member variables/rectangles
        mRect.x = mPosX;
        mRect.y = mPosY;
        mColliders[0].x = mPosX+PLAYER_COLLIDER_BOARDER;
        mColliders[0].y = mPosY;
        mColliders[1].x = mPosX;
        mColliders[1].y = mPosY+PLAYER_COLLIDER_BOARDER;
    }
}

SDL_Rect Player::getRect() {
    return mRect;
}

void Player::adjustVel(int wallVelY) {
    mVelY = wallVelY;
}
