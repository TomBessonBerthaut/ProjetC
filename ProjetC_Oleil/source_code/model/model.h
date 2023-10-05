typedef struct vector {
    int x;                  // x coordinate of the vector
    int y;                  // y coordinate of the vector
} vector;

typedef struct sun {
    int x;                  // x coordinate of the sun
    int y;                  // y coordinate of the sun
    int r;                  // Radius of the sun
    vector v;               // Attractive force exerted by the sun on the ship
} sun;

typedef struct planet {
    int x;                  // x coordinate of the planet
    int y;                  // y coordinate of the planet
    int r;                  // Radius of the planet
    int orbit;              // Planet radius orbit
    vector v;               // Attractive force exerted by the planet on the ship
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
    int x;                  // x coordinate of the ship
    int y;                  // y coordinate of the ship
    vector v;               // Speed vector of the ship
    vector tot;             // Sum of the forces applied on the ship
} ship;

typedef struct game {
    planet* listPlanet;    // List of all the planet simulated
    sun* listSun;          // List of all the sun simulated
    ship s;                 // Ship
    startArea start;        // Coordinate where the ship spaws
    endArea end;            // Coordiante you should aim for
} game;
