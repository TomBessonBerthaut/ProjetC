#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include"vue_controller.h"
#include"../model/model.h"
#include<SDL2/SDL2_gfxPrimitives.h>
#include<stdbool.h>
#include<math.h>



/*
typedef struct WinParameter{
    SDL_Window * win;
    SDL_Renderer * renderer;
}WinParameter;
//this variable will allow us to access our sdl window and render anywhere in our file vue_controller.c
static WinParameter windowParameter;

//this variable will allow us to retrieve keyboard inputs anywhere in our file vue_controller.c
keyboard keys;

void initSDL(FILE * file){
    window wd;
    //SDL initialization
    SDL_Init(SDL_INIT_EVERYTHING); 

    //reading in configuration file
    fscanf(file, "WIN_SIZE %d %d\n", &wd.x, &wd.y);

    //creating the window and renderer
    windowParameter.win = SDL_CreateWindow("ProjetC_oleil",200,50,wd.x,wd.y,SDL_WINDOW_SHOWN);
    windowParameter.renderer = SDL_CreateRenderer(windowParameter.win, -1, SDL_RENDERER_ACCELERATED);

}

//release of sdl resources
void closeSDL(){
    SDL_DestroyRenderer(windowParameter.renderer);
    SDL_DestroyWindow(windowParameter.win);
    SDL_Quit();
}

void handleEvents(SDL_Event ev,int run){
    printf("run pendant la boucle et à l'interieure de la fonction: %d\n",run);
    while(SDL_PollEvent(&ev)){
        switch (ev.type){
            case SDL_QUIT:
                run = 0;
                printf("run apres le clic : %d\n",run);
                break;
            case SDL_KEYDOWN:
                if (ev.key.keysym.sym == SDLK_ESCAPE) {
                    run = 0; //Exit from loop if ESC key is pressed 
                    printf("run apres avoir appuye sur echap : %d\n",run);
                }
                if (ev.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    keys.spacePressed = 1;
                    printf("espace %d",keys.spacePressed);
                    //keys.startTime;
                }   
                if (ev.key.keysym.scancode == SDL_SCANCODE_V) {
                    keys.vPressed = 1;
                }
                if (ev.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    keys.rightPressed = 1;
                }
                if (ev.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    keys.leftPressed = 1;
                }
                break;
            case SDL_KEYUP:
                if (ev.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                    //spacePressed = false;
                }   
                if (ev.key.keysym.scancode == SDL_SCANCODE_V) {
                    //keys.vPressed = false;
                }
                if (ev.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                    keys.rightPressed = 0;
                }
                if (ev.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                    keys.leftPressed = 0;
                }
                break;
            default:
                break;
        }
        

    }
}


void render(FILE * file){
    SDL_SetRenderDrawColor(windowParameter.renderer,0,0,0,255); //make interface black
    SDL_RenderClear(windowParameter.renderer); //prepare the screen to receive new elements

    drawGalaxy(file);

    SDL_RenderPresent(windowParameter.renderer); //display updated content on screen
}

void drawGalaxy(FILE * file){
    int nbreStar,nbrePlanet;
    start s;
    end e;
    star S;
    planet p;
    starShip V;
    solarSystem solSys[50];
    //Start
    fscanf(file, "START %d %d\n", &s.x, &s.y);
    rectangleRGBA(windowParameter.renderer, s.x, s.y, s.x+10, s.y+10, 255, 255, 255, 255);

    //End
    fscanf(file, "END %d %d\n", &e.x, &e.y);
    rectangleRGBA(windowParameter.renderer, e.x, e.y, e.x+10, e.y+10, 255, 255, 255, 255);

    //vaisseau
    V.x = s.x; //initialisation des coordonnees du vaisseau
    V.y = s.y;
    boxRGBA(windowParameter.renderer, V.x, V.y, V.x+10, V.y+10, 255, 0, 0, 255);

    //Uint32 currentTime = SDL_GetTicks();
    //double Time = (currentTime - keys.startTime) / 1000.0;//to have time in second

    //affichage du systeme solaire
    
    fscanf(file, "NB_SOLAR_SYSTEM %d\n", &nbreStar);
    for(int i = 0; i < nbreStar; i++){
        fscanf(file, "STAR_POS %d %d\n", &solSys[i].S.x, &solSys[i].S.y);
        fscanf(file, "STAR_RADIUS %d\n", &solSys[i].S.r);
        filledCircleRGBA(windowParameter.renderer,solSys[i].S.x,solSys[i].S.y,solSys[i].S.r,255,255,0,255);

        //fscanf nbplanet
        fscanf(file, "NB_PLANET %d\n", &nbrePlanet);
        //for j nbplanet
        for(int j = 0; j < nbrePlanet; j++){
            //fscanf pos planet  system_solar[i].planet[j].pos.x
            fscanf(file, "PLANET_RADIUS %d\n", &solSys[i].p[j].r);
            fscanf(file, "PLANET_ORBIT %d\n", &solSys[i].p[j].o);
            solSys[i].p[j].x = solSys[i].S.x; //position initiale de la planete en abscisse
            solSys[i].p[j].y = solSys[i].S.y - abs(solSys[i].p[j].o); //position initiale de la planete en ordonnee
            //printf("space = %d\n", spacePressed);
            if (keys.spacePressed == 1) {
                // action a effectuer
                solSys[i].p[j].a = 2 * M_PI / solSys[i].p[j].r;
                solSys[i].p[j].x = solSys[i].S.x + (int)(solSys[i].p[j].o * cos(solSys[i].p[j].a));
                solSys[i].p[j].y = solSys[i].S.y + (int)(solSys[i].p[j].o * sin(solSys[i].p[j].a));
            }
            filledCircleRGBA(windowParameter.renderer,solSys[i].p[j].x,solSys[i].p[j].y,solSys[i].p[j].r,0,0,255,255);  
        }        
    }
}


//* Time 















//declaration de variables globales

//char varName[20];

//int heigth = 0;//hauteur de la fenetre
//int width = 0;//largeur de la fenetre



//double solSys[i].p[j].a = 0;





//void displayWin(char *config_name){
    //solSys->p->a
    //ouverture du fichier de configuration

    //FILE* file = fopen(config_name, "r");

    
 
    
    //initialisation de la fenetre
    //SDL_Init(SDL_INIT_EVERYTHING); 

    //lecture dans le fichier de configuration
    //size_t fichierr = fread (&config_name, sizeof(char), 1, fichiero);
    
    //attendre que l'utilisateur ferme la fenetre
    
    //while(run){
        //SDL_Event ev;
        
        
        //SDL_RenderClear(renderer);

        

/*
        for(int i = 0; i < nbreStar; i++){
            for(int j = 0; j < nbrePlanet; j++){
                
                if (spacePressed) {
                    // action a effectuer
                    int x = solSys[i].p[j].x + (int)(solSys[i].p[j].r * cos(solSys[i].p[j].a));
                    int y = solSys[i].p[j].y + (int)(solSys[i].p[j].r * sin(solSys[i].p[j].a));
                    filledCircleRGBA(renderer,x,y,solSys[i].p[j].r,0,0,255,255);
                    solSys[i].p[j].a += solSys[i].p[j].r;
                    if (solSys[i].p[j].a >= 2 * M_PI) {
                        solSys[i].p[j].a = 0;
                    }
                    //printf("%d %d %d %f",solSys[i].p[j].x,solSys[i].p[j].y,solSys[i].p[j].r,solSys[i].p[j].a);
                }else{
                    filledCircleRGBA(renderer,solSys[i].p[j].x,solSys[i].p[j].y,solSys[i].p[j].r,0,0,255,255);
                }
            }
        }  
        */
        
        //mise a jour de l'ecran
        //SDL_RenderPresent(renderer);
        //SDL_Delay(10);
    //}
    
    

    

    
    
//}

/*
//printf("space = %d\n", spacePressed);
            if (keys.spacePressed == 1) {
                // action a effectuer
                solSys[i].p[j].a = 2 * M_PI / solSys[i].p[j].r;
                solSys[i].p[j].x = solSys[i].S.x + (int)(solSys[i].p[j].o * cos(solSys[i].p[j].a));
                solSys[i].p[j].y = solSys[i].S.y + (int)(solSys[i].p[j].o * sin(solSys[i].p[j].a));
            }
            filledCircleRGBA(windowParameter.renderer,solSys[i].p[j].x,solSys[i].p[j].y,solSys[i].p[j].r,0,0,255,255);  */