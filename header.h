#pragma once
#include "texture.h"
#include "player.h"
#include "ground.h"
#include "lever.h"
#include "door.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern LTexture gDotTexture;
extern std::vector<LTexture> gPlayerSprites;

//Constants
const double GRAVITATIONAL_CONSTANT = 1;
const int BOARDER_WIDTH = 20;

//Collision checking with separating axis test
extern bool checkCollision(SDL_Rect a, SDL_Rect b);

//Checking if one object is above another
extern bool isAbove(SDL_Rect a, SDL_Rect b);

//Checking for which side the collision is on
extern bool isLeftCollided(SDL_Rect a, SDL_Rect b);
extern bool isRightCollided(SDL_Rect a, SDL_Rect b);
