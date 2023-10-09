#include <stdio.h>
#include <stdlib.h>
#include "source_code/model/model.h"

int main(){
    game *g = calloc(1, sizeof(game));
    g->listPlanet = NULL;
    g->start = NULL;
    g->end = NULL;

    ship *ship = calloc(1, sizeof(ship));
    ship->x = 0;
    ship->y = 0;
    ship->v = NULL;
    ship->tot = NULL;

    g->s = ship;

    sun *sun = buildSun(10, 10, 2);
    
    g->listSun = calloc(1, sizeof(g->listSun));
    g->listSun[0] = sun;

    updateAllVectors(g);

    
} 