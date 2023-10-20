#ifndef MODEL_H
#define MODEL_H
#include <SDL2/SDL.h>

//**********************STRUCTURS**********************

typedef struct vector {
    float x;                // x coordinate of the vector
    float y;                // y coordinate of the vector
} vector;

typedef struct sun {
    int x;                  // x coordinate of the sun
    int y;                  // y coordinate of the sun
    int r;                  // Radius of the sun
    vector* v;              // Attractive force exerted by the sun on the ship
} sun;

typedef struct planet {
    float alpha;            // Position in radians on the orbit
    int r;                  // Radius of the planet
    int orbit;              // Planet radius orbit
    vector* v;              // Attractive force exerted by the planet on the ship
    sun* s;                 // Ptr towards the sun around which the planet orbits
} planet;

typedef struct startArea {
    int x;                  // x coordinate of the area
    int y;                  // y coordinate of the area
} startArea;

typedef struct endArea {
    int x;                  // x coordinate of the area
    int y;                  // y coordinate of the area
} endArea;

typedef struct ship {
    float x;                // x coordinate of the ship
    float y;                // y coordinate of the ship
    vector* v;              // Speed vector of the ship
    vector* tot;            // Sum of the forces applied on the ship
} ship;

typedef struct windowAttributs{
    int heigth;
    int width;
    SDL_Window* window;
    SDL_Renderer* renderer;
}windowAttributs;

typedef struct game {
    int nbSun;
    int nbPlanet;
    planet** listPlanet;    // List of all the planet simulated
    sun** listSun;          // List of all the sun simulated
    ship* s;                // Ship
    startArea* start;       // Coordinate where the ship spaws
    endArea* end;           // Coordiante you should aim for
    windowAttributs* w;
} game;

//**********************BUILDERS/DESTROYERS**********************

vector* buildVector (int x, int y);
void destructVector (vector* v);
sun* buildSun (int x, int y, int r);
void destructSun (sun* s);
planet* buildPlanet (sun* s, int orbit, int r);
void destructPlanet (planet* p);
startArea* buildStartArea (int x, int y);
void destructStartArea (startArea* sa);
endArea* buildEndtArea (int x, int y);
void destructEndArea (endArea* ea);
ship* buildShip ();
void destructShip (ship* s);
void destructGame (game* g);

//**********************FUNCTIONS**********************

void updateAllPlanets (game* g);
void updateAllVectors (game* g);
void getPlanetCoords (planet* p, float* coords);
void moveShip (ship* s);
void printVector (vector* v);
void vectorXYToAngle (vector* v, float* angularCoords);
void vectorAngleToXY (vector* v, float* angularCoords);
planet* readPlanet(FILE* file, sun* s);
void* readSunAndPlanets(FILE* file, game* g, planet** tempList);
game* readFile(const char* filename);


#endif