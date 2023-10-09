#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "model.h"


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
    for (int i = 0; i < (sizeof(g->listSun) / sizeof(g->listSun[0])); i++){

        g->listSun[i]->v->x = 1000 * g->listSun[i]->r * 20 * (g->listSun[i]->x - g->s->x) / powf(pow(g->listSun[i]->x - g->s->x, 2) + pow(g->listSun[i]->y - g->s->y, 2), 1.5);
        //                   | G | * |   Sun mass   | * || * |     delat x sun/ship     | / |    Distance between sun and ship squared time Distance between sun and ship    |
        //                                             |ship's mass|
        g->listSun[i]->v->y = 1000 * g->listSun[i]->r * 20 * (g->listSun[i]->y - g->s->y) / powf(pow(g->listSun[i]->x - g->s->x, 2) + pow(g->listSun[i]->y - g->s->y, 2), 1.5);
        //                   | G | * |   Sun mass   | * || * |     delat y sun/ship     | / |    Distance between sun and ship squared time Distance between sun and ship    |
        //                                             |ship's mass|
    }
};