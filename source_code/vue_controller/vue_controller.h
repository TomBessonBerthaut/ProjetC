#define PI 3.14159265359

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

typedef struct Planet{
    int r;
    int o;
    int x;
    int y;
    double a;
    //int r;
}planet;

typedef struct StarShip{
    int x,y;
    int speed;
    int direction;
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


//Valeurs de chaque parametre du fichier
typedef struct Ligne{
    //char varname[10];
    int value;
}Ligne;


void displayWin(char *config_name);

//void createSolarSystem();