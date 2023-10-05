#include <stdio.h>
#include <stdlib.h>
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