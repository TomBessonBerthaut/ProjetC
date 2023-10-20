#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "model.h"

#define PI 3.14159
#define FPS 60


vector* buildVector (int x, int y){
    vector* v = calloc(sizeof(vector), 1);
    v->x = x;
    v->y = y;
    return v;
};

void destructVector (vector* v){
    free(v);
};

sun* buildSun (int x, int y, int r){
    sun* s = calloc(sizeof(sun), 1);
    s->x = x;
    s->y = y;
    s->r = r;
    s->v = buildVector(0, 0);
    return s;
};

void destructSun (sun* s){
    destructVector(s->v);
    free(s);
};

planet* buildPlanet (sun* s, int orbit, int r){
    planet* p = calloc(sizeof(planet), 1);
    p->s = s;
    p->orbit = orbit;
    p->r = r;
    p->v = buildVector(0, 0);
    return p;
};

void destructPlanet (planet* p){
    destructVector(p->v);
    free(p);
};

startArea* buildStartArea (int x, int y){
    startArea* sa = calloc(sizeof(startArea), 1);
    sa->x = x;
    sa->y = y;
    return sa;
};

void destructStartArea (startArea* sa){
    free(sa);
};

endArea* buildEndtArea (int x, int y){
    endArea* ea = calloc(sizeof(endArea), 1);
    ea->x = x;
    ea->y = y;
    return ea;
};

void destructEndArea (endArea* ea){
    free(ea);
};

ship* buildShip()
{
    ship *s = calloc(sizeof(ship), 1);
    s->v = buildVector(0, 0);
    s->v->x = 0;
    s->v->y = 0;

    return s;
};

void destructShip(ship* s){
    destructVector(s->v);
    destructVector(s->tot);
    free(s);
};

void destructGame (game* g){
    for (int i = 0; i < (sizeof(g->listPlanet)*sizeof(g->listPlanet[0])); i++){
        destructPlanet(g->listPlanet[i]);
    }
    free(g->listPlanet);
    for (int i = 0; i < (sizeof(g->listSun)*sizeof(g->listSun[0])); i++){
        destructSun(g->listSun[i]);
    }
    free(g->listSun);
    destructShip(g->s);
    destructStartArea(g->start);
    destructEndArea(g->end);
};



//*************************************************

void updateAllPlanets (game* g){                                                                // Take the list of all planets
    for (int i = 0; i < g->nbPlanet; i++){                                 // Updating all planets angles
        int senseOfRotation = g->listPlanet[i]->orbit > 0 ? 1 : 0;                                             // Get the rotation sense of the planet orbit
        g->listPlanet[i]->alpha = g->listPlanet[i]->alpha + senseOfRotation * 2 * PI / (g->listPlanet[i]->r * FPS);  // Udpating the planet angle
    }
};

void updateAllVectors (game* g){                                                    // Take the whole game in order to get acces to all suns, planets and the ship
    vector tempVector;                                                              // Temporary vector use calculate the sum of all the vectors
    tempVector.x = 0;
    tempVector.y = 0;
    for (int i = 0; i < g->nbSun; i++){         // Updating all suns vectors

        g->listSun[i]->v->x = 1000 * g->listSun[i]->r * 20 * (g->listSun[i]->x - g->s->x) / powf(pow(g->listSun[i]->x - g->s->x, 2) + pow(g->listSun[i]->y - g->s->y, 2), 1.5);
        //                   | G | * |   Sun mass   | * || * |     delat x sun/ship     | / |    Distance between sun and ship squared time Distance between sun and ship    |
        //                                        |ship's mass|
        g->listSun[i]->v->y = 1000 * g->listSun[i]->r * 20 * (g->listSun[i]->y - g->s->y) / powf(pow(g->listSun[i]->x - g->s->x, 2) + pow(g->listSun[i]->y - g->s->y, 2), 1.5);
        //                   | G | * |   Sun mass   | * || * |     delat y sun/ship     | / |    Distance between sun and ship squared time Distance between sun and ship    |
        //                                        |ship's mass|
        tempVector.x = tempVector.x + g->listSun[i]->v->x;
        tempVector.y = tempVector.y + g->listSun[i]->v->y;
    }
    for (int i = 0; i < g->nbPlanet; i++){   // Updating all planets vectors
        float pc[2];                                                                // Planet coords
        getPlanetCoords(g->listPlanet[i], pc);

        g->listPlanet[i]->v->x = 1000 * g->listPlanet[i]->r * 20 * (pc[0] - g->s->x) / powf(pow(pc[0] - g->s->x, 2) + pow(pc[1] - g->s->y, 2), 1.5);
        //                      | G | * |   Sun mass      | * || * |delat x sun/ship|/ |Distance between sun and ship squared time Distance between sun and ship|
        //                                               |ship's mass|
        g->listPlanet[i]->v->y = 1000 * g->listPlanet[i]->r * 20 * (pc[1] - g->s->y) / powf(pow(pc[0] - g->s->x, 2) + pow(pc[1] - g->s->y, 2), 1.5);
        //                      | G | * |   Sun mass      | * || * |delat y sun/ship|/ |Distance between sun and ship squared time Distance between sun and ship|
        //                                               |ship's mass|
        tempVector.x = tempVector.x + g->listPlanet[i]->v->x;
        tempVector.y = tempVector.y + g->listPlanet[i]->v->y;
    }

    // JE SUIS PAS CERTAIN D'AVOIR COMPRIS COMMENT LE VECTEUR VITESSE/ACCELERATION FONCTIONNE. DONC CETTE PARTIE EST PEU ETRE FAUSSE.
    g->s->v = g->s->tot;
    g->s->tot->x = tempVector.x;
    g->s->tot->y = tempVector.y;
    float angularCoords[2];
    vectorXYToAngle(g->s->v, angularCoords);  //Converting an x, y vector into an n, alpha vector
    if (angularCoords[0] < 2){  //Keeping the speed over 2
        angularCoords[0] = 2;
    }
    if (angularCoords[0] > 8){  //Keeping the speed below 9
        angularCoords[0] = 8;
    }
    vectorAngleToXY(g->s->v, angularCoords);  //Converting the vector back to x, y
    
};

void getPlanetCoords (planet* p, float* coords){                                        // Array to return x and y coords at the same time
    coords[0] = p->orbit * cos(p->alpha * 180 / PI) + p->s->x;  // X coord
    coords[1] = p->orbit * sin(p->alpha * 180 / PI) + p->s->y;  // Y coord
};

void moveShip (ship* s){
    s->x = s->x + (s->v->x / FPS);
    s->y = s->y + (s->v->y / FPS);
};

void printVector (vector* v){
    printf("Vecteur :\nX = %f\nY = %f\n", v->x, v->y);
};

void vectorXYToAngle (vector* v, float* angularCoords){
    angularCoords[0] = powf(powf(v->x, 2) + powf(v->y, 2), 0.5);
    if (v->x > 0){
        if (v->y > 0){
            angularCoords[1] = cosf(v->x / angularCoords[0]);
        }
        else{
            angularCoords[1] = 0 - cosf(v->x / angularCoords[0]);
        }
    }
    else{
        if (v->y > 0){
            angularCoords[1] = cosf(v->x / angularCoords[0]) + PI;
        }
        else{
            angularCoords[1] = 0 - cosf(v->x / angularCoords[0]) - PI;
        }
    }
};
void vectorAngleToXY (vector* v, float* angularCoords){
    float length = angularCoords[0];
    float angle = angularCoords[1];
    if (angle >= 0){
        if (angle <= PI / 2){
            v->x = cosf(angle) * length;
            v->y = sinf(angle) * length;
        }
        else{
            v->x = -sinf(angle - PI / 2) * length;
            v->y = cosf(angle) * length;            
        }
    }
    else{
        if (angle >= -PI / 2){
            v->x = cosf(-angle) * length;
            v->y = -sinf(-angle) * length;
        }
        else{
            v->x = -cosf(angle + PI) * length;
            v->y = -sinf(angle + PI) * length;
        }
    } 
};

//*************************************************************************************************************************************************
planet* readPlanet(FILE* file, sun* s)
{
    int r = 0;
    int orbit = 0;
    if (1 != fscanf(file, "PLANET_RADIUS %u\n", &r)) {
        fprintf(stderr, "Error reading radius planet\n");
        return NULL;
    }

    if (1 != fscanf(file, "PLANET_ORBIT %d\n", &orbit)) {
        fprintf(stderr, "Error reading orbit planet\n");
        return NULL;
    }

    planet *p = buildPlanet(s, orbit, r);
    return p;
}

void* readSunAndPlanets(FILE* file, game* g, planet** tempList)
{
    int sunX = 0;
    int sunY = 0;
    int sunR = 0;
    if (2 != fscanf(file, "STAR_POS %d %d\n", &sunX, &sunY)) {
        fprintf(stderr, "Error reading sun pos\n");
        return NULL;
    }

    if (1 != fscanf(file, "STAR_RADIUS %u\n", &sunR)) {
        fprintf(stderr, "Error reading sun radius\n");
        return NULL;
    }
    sun* s = buildSun(sunX, sunY, sunR);
    g->listSun[g->nbSun] = s;
    g->nbSun++;

    // read planet count
    int tempNbPlanet = 0;
    if (1 != fscanf(file, "NB_PLANET %u\n", &tempNbPlanet)) {
        fprintf(stderr, "Error reading nb Planet\n");
        return NULL;
    }

    for (size_t i = 0; i < tempNbPlanet; i++) {
        g->listPlanet[g->nbPlanet] = readPlanet(file, g->listSun[g->nbSun-1]);
        g->nbPlanet++;
    }
}

/*
    
*/
game* readFile(const char* filename)
{
    int tempNbSun = 0;
    game* g = calloc(sizeof(game), 1);

    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening the file\n");
        return NULL;
    }

    if (2 != fscanf(file, "WIN_SIZE %d %d\n", &g->w->heigth, &g->w->width)) {
        fprintf(stderr, "Error reading window size\n");
        return NULL;
    }

    if (2 != fscanf(file, "START %d %d\n", &g->start->x, &g->start->y)) {
        fprintf(stderr, "Error reading start area\n");
        return NULL;
    }

    if (2 != fscanf(file, "END %d %d\n", &g->end->x, &g->end->y)) {
        fprintf(stderr, "Error reading end area\n");
        return NULL;
    }

    if (1 != fscanf(file, "NB_SOLAR_SYSTEM %u\n", &tempNbSun)) {
        fprintf(stderr, "Error reading solar system\n");
        return NULL;
    }

    g->listSun = calloc(sizeof(sun*) * tempNbSun, 1);
    g->nbSun = 0;
    g->nbPlanet = 0;
    planet *tempList[100];
    for (int i = 0; i < 100; i++){
        tempList[i] = calloc(sizeof(planet*), 1);
    }

    for (int i = 0; i < tempNbSun; i++){
        readSunAndPlanets(file, g, tempList);
    }

    g->nbPlanet--;
    g->listPlanet = calloc(sizeof(planet*) * g->nbPlanet, 1);
    for (int i = 0; i < g->nbPlanet; i++){
        g->listPlanet[i] = tempList[i];
    }
    for (int i = 0; i < 100; i++){
        free(tempList[i]);
    }
    
    g->s = buildShip();
    fclose(file);

    return g;
}