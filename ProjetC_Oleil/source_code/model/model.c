#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "model.h"

#define PI 3.14159
#define FPS 60


vector* buildVector (int x, int y){
    vector* v = calloc(1, sizeof(vector));
    v->x = x;
    v->y = y;
    return v;
};

void destructVector (vector* v){
    free(v);
};

sun* buildSun (int x, int y, int r){
    sun* s = calloc(1, sizeof(sun));
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
    planet* p = calloc(1, sizeof(planet));
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
    startArea* sa = calloc(1, sizeof(startArea));
    sa->x = x;
    sa->y = y;
    return sa;
};

void destructStartArea (startArea* sa){
    free(sa);
};

endArea* buildEndtArea (int x, int y){
    endArea* ea = calloc(1, sizeof(endArea));
    ea->x = x;
    ea->y = y;
    return ea;
};

void destructEndArea (endArea* ea){
    free(ea);
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


void updateAllVectors (game* g){
    vector tempVector;                                                              // Temporary vector use calculate the sum of all the vectors
    tempVector.x = 0;
    tempVector.y = 0;
    for (int i = 0; i < (sizeof(g->listSun) / sizeof(g->listSun[0])); i++){         // Updating all suns vectors

        g->listSun[i]->v->x = 1000 * g->listSun[i]->r * 20 * (g->listSun[i]->x - g->s->x) / powf(pow(g->listSun[i]->x - g->s->x, 2) + pow(g->listSun[i]->y - g->s->y, 2), 1.5);
        //                   | G | * |   Sun mass   | * || * |     delat x sun/ship     | / |    Distance between sun and ship squared time Distance between sun and ship    |
        //                                        |ship's mass|
        g->listSun[i]->v->y = 1000 * g->listSun[i]->r * 20 * (g->listSun[i]->y - g->s->y) / powf(pow(g->listSun[i]->x - g->s->x, 2) + pow(g->listSun[i]->y - g->s->y, 2), 1.5);
        //                   | G | * |   Sun mass   | * || * |     delat y sun/ship     | / |    Distance between sun and ship squared time Distance between sun and ship    |
        //                                        |ship's mass|
        tempVector.x = tempVector.x + g->listSun[i]->v->x;
        tempVector.y = tempVector.y + g->listSun[i]->v->y;
    }/*
    for (int i = 0; i < (sizeof(g->listPlanet) / sizeof(g->listPlanet[0])); i++){   // Updating all planets vectors
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
    }*/

    // JE SUIS PAS CERTAIN D'AVOIR COMPRIS COMMENT LE VECTEUR VITESSE/ACCELERATION FONCTIONNE. DONC CETTE PARTIE EST PEU ETRE FAUSSE.
    g->s->v = g->s->tot;
    g->s->tot->x = tempVector.x;
    g->s->tot->y = tempVector.y;
};

void getPlanetCoords (planet* p, float* coords){                                        // Array to return x and y coords at the same time
    coords[0] = p->orbit * cos(p->alpha * 180 / PI) + p->s->x;  // X coord
    coords[1] = p->orbit * sin(p->alpha * 180 / PI) + p->s->y;  // Y coord
}

void moveShip (ship* s){
    s->x = s->x + (s->v->x / FPS);
    s->y = s->y + (s->v->y / FPS);
}

void printVector (vector* v){
    printf("Vecteur :\nX = %f\nY = %f\n", v->x, v->y);
}
