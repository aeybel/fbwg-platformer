/**
ICS 3UI
Final Project - Alanna Eybel
Fireboy and Watergirl replica
**/

#include "header.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Start up and create window
bool init();

//Load media
bool loadMedia();

//Free media and shut down SDL
void close();

//The window
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The dot textures
std::vector<LTexture> gPlayerSprites(TOTAL_PLAYER_SPRTITES);

//Returns a vector of class objects to use for each level
std::vector<Ground> loadWalls(int level);
std::vector<Lever> loadLevers(int level);
std::vector<Lever> loadPushers(int level);

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    } else {
        //Create window
        gWindow = SDL_CreateWindow("Fireboy and Watergirl replica", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL) {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                //Initialize render color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) &imgFlags)) {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia() {
    //Loading success flag
    bool success = true;

    if (!gPlayerSprites[RED_PLAYER_SPRITE].loadFromFile("sprites/redDot.bmp")) {
        std::cout << "Failed to load red dot texture!" << std::endl;
        success = false;
    }
    if (!gPlayerSprites[BLUE_PLAYER_SPRITE].loadFromFile("sprites/blueDot.bmp")) {
        std::cout << "Failed to load blue dot texture!" << std::endl;
        success = false;
    }

    return success;
}

void close() {
    //Free loaded images
    for (int i = 0; i < 2; i++) {
        gPlayerSprites[i].free();
    }

    //Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x+a.w;
    topA = a.y;
    bottomA = a.y+a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x+b.w;
    topB = b.y;
    bottomB = b.y+b.h;

    //if any of the sides from A are outside B
    if (bottomA >= topB && topA <= bottomB && rightA >= leftB && leftA <= rightB) {
        return true;
    }

    //If no sides from A are outside B
    return false;
}

bool isAbove(SDL_Rect a, SDL_Rect b) {
    if ((a.y+a.h) - b.y <= 1 && (a.y+a.h) - b.y >= 0) {
        return true;
    }
    else {
        return false;
    }
}

bool isLeftCollided(SDL_Rect a, SDL_Rect b) {
    double centreB = b.x+(b.w/2);

    if (a.x < centreB && (a.x+a.h > b.x)) {
        return true;
    }

    return false;
}

bool isRightCollided(SDL_Rect a, SDL_Rect b) {
    double centreB = b.x+(b.w/2);

    if (a.x > centreB && (a.x < b.x+b.w)) {
        return true;
    }

    return false;
}

std::vector<Ground> loadWalls(int level) {
    std::vector<Ground> levelRects;
    switch (level) {
        case -1: //Testing level
            levelRects.push_back(Ground(40, (SCREEN_HEIGHT/2)+40, 250, 40, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(225, (SCREEN_HEIGHT/2)-10, 200, 40, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(300, (SCREEN_HEIGHT/2)-90, 160, 20, GROUND_TYPE_BASIC, 30, 50, 0x88, 0x00, 0x88));
            levelRects.push_back(Ground(20, 40, 50, 20, GROUND_TYPE_BASIC, 20, 100, 0x88, 0x00, 0x88));
            break;
        case 0: //Another testing level
            levelRects.push_back(Ground(300, 280, 120, 40, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(200, 320, 100, 40, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(260, 280, 30, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(210, 280, 35, 20, GROUND_TYPE_RED));
            break;
        case 1:
            levelRects.push_back(Ground(0, SCREEN_HEIGHT-20, 300, 20, GROUND_TYPE_BASIC)); //the lowest platform
            levelRects.push_back(Ground(350, SCREEN_HEIGHT-20, 80, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(480, SCREEN_HEIGHT-20, SCREEN_WIDTH-480, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(20, 390, 200, 20, GROUND_TYPE_BASIC)); //blue's platform
            levelRects.push_back(Ground(300, SCREEN_HEIGHT-19, 50, 10, GROUND_TYPE_RED)); //the lava
            levelRects.push_back(Ground(430, SCREEN_HEIGHT-19, 50, 10, GROUND_TYPE_BLUE)); //the water
            levelRects.push_back(Ground(570, 410, 50, 50, GROUND_TYPE_BASIC)); //the tall platform
            levelRects.push_back(Ground(280, 360, 110, 20, GROUND_TYPE_BASIC)); //the middle lower platform
            levelRects.push_back(Ground(390, 370, 50, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(440, 360, 90, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(390, 361, 50, 10, GROUND_TYPE_GREEN)); //the poison
            levelRects.push_back(Ground(20, 320, 280, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(20, 240, 50, 10, GROUND_TYPE_BASIC, 20, 300, 0x88, 0x44, 0x00)); //the lever platform
            levelRects.push_back(Ground(70, 240, SCREEN_WIDTH-90, 20, GROUND_TYPE_BASIC)); //the middle platform
            levelRects.push_back(Ground(SCREEN_WIDTH-70, 170, 50, 10, GROUND_TYPE_BASIC, SCREEN_WIDTH-70, 220, 0x88, 0x00, 0x88)); //the pusher platform
            levelRects.push_back(Ground(100, 160, 470, 20, GROUND_TYPE_BASIC)); //the middle upper platform
            levelRects.push_back(Ground(20, 120, 80, 60, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(150, 70, 60, 20, GROUND_TYPE_BASIC)); //the top platform
            levelRects.push_back(Ground(200, 90, 420, 20, GROUND_TYPE_BASIC));
            break;
        case 2:
            levelRects.push_back(Ground(20, SCREEN_HEIGHT-20, 90, 20, GROUND_TYPE_BASIC)); //the bottom platform
            levelRects.push_back(Ground(230, SCREEN_HEIGHT-20, 130, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(480, SCREEN_HEIGHT-20, 140, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(570, 410, 50, 50, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(110, SCREEN_HEIGHT-19, 120, 10, GROUND_TYPE_RED)); //the lava/water
            levelRects.push_back(Ground(360, SCREEN_HEIGHT-19, 120, 10, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(110, 420, 120, 10, GROUND_TYPE_BASIC)); //the middle lower bits
            levelRects.push_back(Ground(360, 420, 120, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(110, 410, 120, 10, GROUND_TYPE_BLUE)); //the water/lava on the middle lower bits
            levelRects.push_back(Ground(360, 410, 120, 10, GROUND_TYPE_RED));
            levelRects.push_back(Ground(20, 350, SCREEN_WIDTH-90, 20, GROUND_TYPE_BASIC)); //the (low) middle platform
            levelRects.push_back(Ground(20, 290, 50, 60, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(310, 280, 10, 70, GROUND_TYPE_BASIC, 310, 210, 0x88, 0x00, 0x88)); //the lower middle pusher platform
            levelRects.push_back(Ground(100, 260, 40, 20, GROUND_TYPE_BASIC)); //the middle platform
            levelRects.push_back(Ground(260, 250, 100, 30, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(480, 260, 140, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(140, 270, 120, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(360, 270, 120, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(530, 210, 40, 60, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(570, 170, 50, 90, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(140, 261, 120, 10, GROUND_TYPE_GREEN)); //the poison
            levelRects.push_back(Ground(360, 261, 120, 10, GROUND_TYPE_GREEN));
            levelRects.push_back(Ground(170, 220, 60, 10, GROUND_TYPE_BASIC)); //the middle upper bits (above the poison)
            levelRects.push_back(Ground(390, 220, 60, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(340, 85, 60, 10, GROUND_TYPE_BASIC, 280, 85, 0x88, 0x44, 0x00)); //the upper pusher platform
            levelRects.push_back(Ground(470, 110, 80, 20, GROUND_TYPE_BASIC)); //the upper platform
            levelRects.push_back(Ground(20, 80, 260, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(340, 80, 150, 20, GROUND_TYPE_BASIC));
            break;
        case -3: //Temporary level
            levelRects.push_back(Ground(530, 90, 100, 20, GROUND_TYPE_BASIC)); //the upper most platform
            levelRects.push_back(Ground(70, 120, 460, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(140, 70, 60, 50, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(240, 115, 40, 15, GROUND_TYPE_BLUE)); //the upper water
            levelRects.push_back(Ground(340, 115, 40, 15, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(440, 115, 40, 15, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(20, 190, 480, 20, GROUND_TYPE_BASIC)); //the middle upper ground
            levelRects.push_back(Ground(150, 160, 40, 30, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(250, 185, 40, 15, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(330, 170, 40, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(450, 170, 130, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(500, 240, 120, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(500, 200, 10, 40, GROUND_TYPE_BASIC));
            break;
        case 3:
            levelRects.push_back(Ground(280, 260, 50, 10, GROUND_TYPE_BASIC, 400, 260, 0x00, 0x44, 0x88)); //the "blue" lever platform
            levelRects.push_back(Ground(330, 200, 40, 10, GROUND_TYPE_BASIC, 290, 200, 0x88, 0x44, 0x00)); //the "orange" lever platform
            levelRects.push_back(Ground(440, 390, 10, 60, GROUND_TYPE_BASIC, 440, 330, 0x88, 0x00, 0x88)); //the "white" pusher platform
            levelRects.push_back(Ground(20, 70, 60, 20, GROUND_TYPE_BASIC)); //red's platform
            levelRects.push_back(Ground(20, 150, 70, 20, GROUND_TYPE_BASIC)); //upper middle layer
            levelRects.push_back(Ground(90, 160, 60, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(150, 150, 90, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(90, 151, 60, 10, GROUND_TYPE_RED)); //the upper lava
            levelRects.push_back(Ground(120, 90, 50, 20, GROUND_TYPE_BASIC)); //the left curving bit
            levelRects.push_back(Ground(150, 70, 170, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(300, 90, 20, 110, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(270, 200, 60, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(240, 220, 40, 70, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(20, 260, 100, 30, GROUND_TYPE_BASIC)); //the base of the left curve
            levelRects.push_back(Ground(160, 260, 40, 30, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(120, 270, 40, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(200, 270, 40, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(120, 261, 40, 10, GROUND_TYPE_BLUE)); //the water in the left curve
            levelRects.push_back(Ground(200, 261, 40, 10, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(480, 20, 20, 70, GROUND_TYPE_BASIC)); //blue's platform
            levelRects.push_back(Ground(500, 70, 70, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(500, 200, 30, 30, GROUND_TYPE_BASIC)); //the right upper bits
            levelRects.push_back(Ground(530, 210, 40, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(570, 200, 50, 30, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(530, 201, 40, 10, GROUND_TYPE_BLUE)); //the upper water
            levelRects.push_back(Ground(410, 150, 120, 20, GROUND_TYPE_BASIC)); //the right curve
            levelRects.push_back(Ground(390, 150, 20, 70, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(370, 200, 20, 140, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(330, 260, 50, 40, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(390, 310, 30, 70, GROUND_TYPE_BASIC)); //the lower part of the right curve
            levelRects.push_back(Ground(420, 320, 30, 60, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(450, 310, 20, 70, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(420, 311, 30, 10, GROUND_TYPE_RED)); //the lava in the lower part of the right curve
            levelRects.push_back(Ground(470, 310, 50, 20, GROUND_TYPE_BASIC)); //the right alcove
            levelRects.push_back(Ground(60, 370, 60, 20, GROUND_TYPE_BASIC)); //the middle lower platform
            levelRects.push_back(Ground(170, 370, 50, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(270, 370, 350, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(120, 380, 50, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(220, 380, 50, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(120, 371, 50, 10, GROUND_TYPE_RED)); //the lava/water in the middle lower platform
            levelRects.push_back(Ground(220, 371, 50, 10, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(0, SCREEN_HEIGHT-30, SCREEN_WIDTH, 30, GROUND_TYPE_BASIC)); //the lowest platform
            break;
        case 4:
            levelRects.push_back(Ground(520, 150, 50, 10, GROUND_TYPE_BASIC, 470, 150, 0x00, 0x44, 0x88)); //the "blue" lever platform
            levelRects.push_back(Ground(200, 20, 10, 50, GROUND_TYPE_BASIC, 200, 70, 0x88, 0x88, 0x00)); //the "yellow" lever platform
            levelRects.push_back(Ground(50, 70, 170, 20, GROUND_TYPE_BASIC)); //the upper left G shape
            levelRects.push_back(Ground(50, 90, 20, 120, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(70, 190, 160, 20, GROUND_TYPE_BASIC));;
            levelRects.push_back(Ground(210, 150, 20, 40, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(120, 130, 230, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(260, 100, 60, 20, GROUND_TYPE_BASIC)); //the top lava platform bits
            levelRects.push_back(Ground(380, 130, 30, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(440, 130, 20, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(320, 140, 120, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(350, 131, 30, 10, GROUND_TYPE_RED)); //the lava bits
            levelRects.push_back(Ground(410, 131, 30, 10, GROUND_TYPE_RED));
            levelRects.push_back(Ground(440, 150, 80, 50, GROUND_TYPE_BASIC)); //The rest of the V shape
            levelRects.push_back(Ground(420, 200, 50, 30, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(280, 230, 160, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(20, 280, 80, 20, GROUND_TYPE_BASIC)); //the middle left platform
            levelRects.push_back(Ground(130, 280, 30, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(200, 280, 40, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(270, 280, 30, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(20, 290, 280, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(100, 281, 30, 10, GROUND_TYPE_BLUE)); //the water (middle)
            levelRects.push_back(Ground(160, 281, 40, 10, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(240, 281, 30, 10, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(540, 100, 80, 20, GROUND_TYPE_BASIC)); //the rightmost bits
            levelRects.push_back(Ground(560, 120, 20, 150, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(490, 250, 30, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(520, 260, 40, 10, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(520, 251, 40, 10, GROUND_TYPE_BLUE));
            levelRects.push_back(Ground(450, 280, 70, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(140, 360, 30, 20, GROUND_TYPE_BASIC)); //the bottom bits
            levelRects.push_back(Ground(200, 390, 50, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(300, 360, 100, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(470, 430, 30, 30, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(520, 370, 50, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(570, 320, 50, 20, GROUND_TYPE_BASIC));
            levelRects.push_back(Ground(0, SCREEN_HEIGHT-29, SCREEN_WIDTH, 30, GROUND_TYPE_BASIC)); //the very bottom bit
            levelRects.push_back(Ground(20, SCREEN_HEIGHT-30, SCREEN_WIDTH-40, 10, GROUND_TYPE_GREEN));
            levelRects.push_back(Ground(20, 410, 70, 50, GROUND_TYPE_BASIC)); //blue's platform
            break;
    }
    return levelRects;
}

std::vector<Lever> loadLevers(int level) {
    std::vector<Lever> levelLevers;
    switch (level) {
        case -1:
            levelLevers.push_back(Lever(280, 210, LEVER_TYPE_LEVER, 2));
            break;
        case 0:
            break;
        case 1:
            levelLevers.push_back(Lever(160, 300, LEVER_TYPE_LEVER, 12, 0x88, 0x44, 0x00, false));
            break;
        case 2:
            break;
        case -3:
            break;
        case 3:
            levelLevers.push_back(Lever(50, 240, LEVER_TYPE_LEVER, 0, 0x00, 0x44, 0x88, false));
            levelLevers.push_back(Lever(500, 350, LEVER_TYPE_LEVER, 1,  0x88, 0x44, 0x00, false));
            break;
        case 4:
            levelLevers.push_back(Lever(150, 170, LEVER_TYPE_LEVER, 0, 0x88, 0x88, 0x00, true));
            levelLevers.push_back(Lever(560, 80, LEVER_TYPE_LEVER, 1, 0x00, 0x44, 0x88, false));
            break;
    }
    return levelLevers;
}

std::vector<Lever> loadPushers(int level) {
    std::vector<Lever> levelPushers;
    switch (level) {
        case -1:
            levelPushers.push_back(Lever(230, 210, LEVER_TYPE_PUSHER, 3));
            break;
        case 0:
            break;
        case 1:
            levelPushers.push_back(Lever(480, 140, LEVER_TYPE_PUSHER, 14, 0x88, 0x00, 0x88));
            levelPushers.push_back(Lever(170, 220, LEVER_TYPE_PUSHER, 14, 0x88, 0x00, 0x88));
            break;
        case 2:
            levelPushers.push_back(Lever(490, 320, LEVER_TYPE_PUSHER, 12, 0x88, 0x00, 0x88));
            levelPushers.push_back(Lever(120, 320, LEVER_TYPE_PUSHER, 12, 0x88, 0x00, 0x88));
            levelPushers.push_back(Lever(460, 60, LEVER_TYPE_PUSHER, 24, 0x88, 0x44, 0x00));
            levelPushers.push_back(Lever(160, 60, LEVER_TYPE_PUSHER, 24, 0x88, 0x44, 0x00));
            break;
        case -3:
            break;
        case 3:
            levelPushers.push_back(Lever(310, 430, LEVER_TYPE_PUSHER, 2, 0x88, 0x00, 0x88));
            levelPushers.push_back(Lever(580, 430, LEVER_TYPE_PUSHER, 2, 0x88, 0x00, 0x88));
            break;
        case 4:
            break;
    }
    return levelPushers;
}

int main(int argc, char* args[]) {
    //Start up SDL and create window
    if (!init()) {
        std::cout << "Failed to initialize!" << std::endl;
    } else {
        //Load media
        if (!loadMedia()) {
            std::cout << "Failed to load media!" << std::endl;
        } else {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //The current level
            int level = 1;

            //Create the player
            Player redPlayer(RED_PLAYER_SPRITE);
            Player bluePlayer(BLUE_PLAYER_SPRITE);

            //Load the level positions
            redPlayer.loadPlayerPos(level);
            bluePlayer.loadPlayerPos(level);
            std::vector<Ground> walls = loadWalls(level);

            //Loads the lever and pusher positions
            std::vector<Lever> levers = loadLevers(level);
            std::vector<Lever> pushers = loadPushers(level);

            //Creates the doors
            Door redDoor(RED_PLAYER_SPRITE);
            Door blueDoor(BLUE_PLAYER_SPRITE);

            //Loads the doors
            redDoor.loadDoorPos(level);
            blueDoor.loadDoorPos(level);

            //While application is running
            while (!quit) {
                //Handle events on the queue
                while (SDL_PollEvent(&e) != 0) {
                    //User requests quit
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    //Handle player input
                    redPlayer.handleEvent(e, walls);
                    bluePlayer.handleEvent(e, walls);
                }

                //Move the player
                if (!(redPlayer.move(walls,0,levers) && bluePlayer.move(walls,0,levers))) {
                    //If the player died, reset the level
                    redPlayer.loadPlayerPos(level);
                    bluePlayer.loadPlayerPos(level);
                    walls = loadWalls(level);
                    levers = loadLevers(level);
                    pushers = loadPushers(level);
                }

                //Move the walls
                for (int i = 0; i < walls.size(); i++) {
                    walls[i].move(&redPlayer, &bluePlayer);
                }

                //Get input for the levers
                for (int i = 0; i < levers.size(); i++) {
                    levers[i].getLeverInput(redPlayer.getRect(), bluePlayer.getRect());
                }

                //Get input for the pushers
                for (int i = 0; i < pushers.size(); i++) {
                    pushers[i].getPusherInput(redPlayer.getRect(), bluePlayer.getRect());
                }

                //Reset the walls for the levers
                for (int i = 0; i < levers.size(); i++) {
                    walls[levers[i].getGroundIndex()].resetOnOff();
                }

                //Reset the walls for the pushers
                for (int i = 0; i < pushers.size(); i++) {
                    walls[pushers[i].getGroundIndex()].resetOnOff();
                }

                //Set the walls targets based on the levers
                for (int i = 0; i < levers.size(); i++) {
                    walls[levers[i].getGroundIndex()].setTarget(levers[i].getOnStatus());
                }

                //Set the walls based on pushers
                for (int i = 0; i < pushers.size(); i++) {
                    walls[pushers[i].getGroundIndex()].setTarget(pushers[i].getOnStatus());
                }

                //If the player got to the doors and completed the level
                if (checkCollision(redPlayer.getRect(), redDoor.getRect()) && checkCollision(bluePlayer.getRect(), blueDoor.getRect())) {
                    //Load the next level
                    level += 1;
                    if (level > 4) {
                        quit = true;
                        std::cout << "CONGRATULATIONS!!! YOU HAVE WON!!!";
                    } else {
                        redPlayer.loadPlayerPos(level);
                        bluePlayer.loadPlayerPos(level);
                        walls = loadWalls(level);
                        levers = loadLevers(level);
                        pushers = loadPushers(level);
                        redDoor.loadDoorPos(level);
                        blueDoor.loadDoorPos(level);
                    }
                }

                //Clears screen, renders the boarder
                SDL_SetRenderDrawColor(gRenderer, 0x88, 0x88, 0x88, 0xFF);
                SDL_RenderClear(gRenderer);

                {
                    //Renders the middle white (clears the middle)
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_Rect screenArea;
                    screenArea.x = BOARDER_WIDTH;
                    screenArea.y = BOARDER_WIDTH;
                    screenArea.w = SCREEN_WIDTH - 2 * BOARDER_WIDTH;
                    screenArea.h = SCREEN_HEIGHT - 1.5 * BOARDER_WIDTH;
                    SDL_RenderFillRect(gRenderer, &screenArea);
                }

                //Render the doors
                redDoor.render();
                blueDoor.render();

                //Render the levers
                for (int i = 0; i < levers.size(); i++) {
                    levers[i].render();
                }

                //Render the pushers
                for (int i = 0; i < pushers.size(); i++) {
                    pushers[i].render();
                }

                //Render the player
                redPlayer.render();
                bluePlayer.render();

                //Render the walls
                for (int i = 0; i < walls.size(); i++) {
                    walls[i].render();
                }

                //Update screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }

    //Free resources, shut down SDL
    close();

    return 0;
}
