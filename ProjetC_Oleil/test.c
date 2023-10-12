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
    ship->v = buildVector(0, 0);
    ship->tot = buildVector(0, 0);

    g->s = ship;

    sun *sun = buildSun(10, 5, 2);
    
    g->listSun = calloc(2, sizeof(g->listSun));
    g->listSun[0] = sun;

    updateAllVectors(g);

    return 0;
} 