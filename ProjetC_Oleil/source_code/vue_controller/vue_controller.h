#include "../model/model.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

//window
typedef struct Window{
    int x;
    int y;
}window;

//zone de depart
typedef struct Start{
    int x;
    int y;
}start;

//zone d'arriver
typedef struct End{
    int x;
    int y;
}end;

//Soleil
typedef struct Star{
    int x;
    int y;
    int r;
}star;


typedef struct StarShip{
    int x,y;
    int speed;
    int direction;
    int mass;
}starShip;

typedef struct SolarSystem{
    /* data */
    star S;
    planet p[50];
}solarSystem;

typedef struct Galaxy{
    solarSystem sysSol;
    starShip v;
    start s;
    end e;
}galaxy;

typedef struct Keyboard{
    int spacePressed;
    int vPressed;
    int rightPressed;
    int leftPressed;
    //Uint32 startTime = SDL_GetTicks();
}keyboard;


void initSDL(FILE * file);

void closeSDL();

void handleEvents(SDL_Event ev,int run);

//void updateGame();

void render(FILE * file);

void drawGalaxy(FILE * file);

//void displayWin(char *config_name);

//void createSolarSystem();