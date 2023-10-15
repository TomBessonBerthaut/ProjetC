#include<stdio.h>
#include<stdlib.h>
#include<SDL2/SDL.h>
#include"vue_controller.h"
#include<SDL2/SDL2_gfxPrimitives.h>
#include<stdbool.h>
#include<math.h>

//declaration de variables globales

char varName[20];

int heigth = 0;//hauteur de la fenetre
int width = 0;//largeur de la fenetre

start s;
end e;
star S;
planet p;
starShip V;
solarSystem solSys[50];

int nbreStar,nbrePlanet;


void displayWin(char *config_name){

    //ouverture du fichier de configuration
    FILE* file = fopen(config_name, "r");

    if(file == NULL){
        perror("Erreur lors de l'ouverture du fichier");
    }

    fseek(file, 0, SEEK_END); //se deplacer à la fin du fichier
    long taille = ftell(file); //obtenir la taille du fichier
    fseek(file, 0, SEEK_SET); //revenir au debut du fichier


    char *buffer = (char *)malloc(taille + 1); //allocation de la memoire
    if(buffer == NULL){
        perror("Erreur lors de l'allocation memoire");
    }
 
    
    //initialisation de la fenetre
    SDL_Init(SDL_INIT_EVERYTHING); 

    //lecture dans le fichier de configuration
    //size_t fichierr = fread (&config_name, sizeof(char), 1, fichiero);
    fscanf(file, "WIN_SIZE %d %d\n", &heigth, &width);

    //creation de la fenetre
    SDL_Window * win = SDL_CreateWindow("ProjetC_oleil",200,50,heigth,width,SDL_WINDOW_SHOWN);
    SDL_Surface * screen = SDL_GetWindowSurface(win);

    //creation du rendu
    SDL_Renderer* renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //attendre que l'utilisateur ferme la fenetre
    bool run = true;
    bool spacePressed = false;
    bool vPressed = false;
    bool rightPressed = false;
    bool leftPressed = false;
    SDL_Event ev;
    while(run){
        //SDL_Event ev;
        
        while(SDL_PollEvent(&ev)){
            switch (ev.type){
                case SDL_QUIT:
                    run = false;
                    break;
                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_ESCAPE) {
                        run = false; // Sortir de la boucle si la touche ÉCHAP est enfoncée
                    }
                    if (ev.key.keysym.scancode == SDL_SCANCODE_SPACE) {
                        spacePressed = true;
                        /*
                        for(int i = 0; i < nbreStar; i++){
                            for(int j = 0; j < nbrePlanet; j++){
                                
                            }
                        }
                        */
                    }   
                    if (ev.key.keysym.scancode == SDL_SCANCODE_V) {
                        vPressed = true;
                    }
                    if (ev.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        rightPressed = true;
                    }
                    if (ev.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        leftPressed = true;
                    }
                    break;
                case SDL_KEYUP:
                    if (ev.key.keysym.scancode == SDL_SCANCODE_V) {
                        vPressed = false;
                    }
                    if (ev.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
                        rightPressed = false;
                    }
                    if (ev.key.keysym.scancode == SDL_SCANCODE_LEFT) {
                        leftPressed = true;
                    }
                    break;
                default:
                    break;
            }
            

        }
        //SDL_RenderClear(renderer);

        //Start
        fscanf(file, "START %d %d\n", &s.x, &s.y);
        rectangleRGBA(renderer, s.x, s.y, s.x+10, s.y+10, 255, 255, 255, 255);

        //End
        fscanf(file, "END %d %d\n", &e.x, &e.y);
        rectangleRGBA(renderer, e.x, e.y, e.x+10, e.y+10, 255, 255, 255, 255);

        //vaisseau
        V.x = s.x; //initialisation des coordonnees du vaisseau
        V.y = s.y;
        boxRGBA(renderer, V.x, V.y, V.x+10, V.y+10, 255, 0, 0, 255);

        //affichage du systeme solaire
        
        fscanf(file, "NB_SOLAR_SYSTEM %d\n", &nbreStar);
        for(int i = 0; i < nbreStar; i++){
            fscanf(file, "STAR_POS %d %d\n", &solSys[i].S.x, &solSys[i].S.y);
            fscanf(file, "STAR_RADIUS %d\n", &solSys[i].S.r);
            filledCircleRGBA(renderer,solSys[i].S.x,solSys[i].S.y,solSys[i].S.r,255,255,0,255);

            //fscanf nbplanet
            fscanf(file, "NB_PLANET %d\n", &nbrePlanet);
            //for j nbplanet
            for(int j = 0; j < nbrePlanet; j++){
                //fscanf pos planet  system_solar[i].planet[j].pos.x
                fscanf(file, "PLANET_RADIUS %d\n", &solSys[i].p[j].r);
                fscanf(file, "PLANET_ORBIT %d\n", &solSys[i].p[j].o);
                solSys[i].p[j].x = solSys[i].S.x; //position initiale de la planete en abscisse
                solSys[i].p[j].y = solSys[i].S.y - abs(solSys[i].p[j].o); //position initiale de la planete en ordonnee
                //if(j > 0){
                    solSys[i].p[j].a = 0;
                //}
                

                filledCircleRGBA(renderer,solSys[i].p[j].x,solSys[i].p[j].y,solSys[i].p[j].r,0,0,255,255);

                
            }        

        
        }

        if (spacePressed) {
            for(int i = 0; i < nbreStar; i++){
                for(int j = 0; j < nbrePlanet; j++){
                    // action a effectuer
                    int x = solSys[i].p[j].x + (int)(solSys[i].p[j].r * cos(solSys[i].p[j].a));
                    int y = solSys[i].p[j].y + (int)(solSys[i].p[j].r * sin(solSys[i].p[j].a));
                    filledCircleRGBA(renderer,x,y,solSys[i].p[j].r,0,0,255,255);
                    solSys[i].p[j].a += solSys[i].p[j].r;
                    if (solSys[i].p[j].a >= 2 * M_PI) {
                        solSys[i].p[j].a = 0;
                    }
                    //printf("%d %d %d %f",solSys[i].p[j].x,solSys[i].p[j].y,solSys[i].p[j].r,solSys[i].p[j].a);
                }
            }      
        }
        
        //mise a jour de l'ecran
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

        //fermeture du fichier et nettoyage de la memoire
        fclose(file);
        free(buffer);

        //liberation des ressources
        SDL_DestroyWindow(win);
        SDL_Quit();

        for(int i = 0; i < nbreStar; i++){
            printf("je suis i %d\n",i);
                for(int j = 0; j < nbrePlanet; j++){
                    printf("je suis j %d\n",j);
                    printf("%d %d %d %f\n",solSys[i].p[j].x,solSys[i].p[j].y,solSys[i].p[j].r,solSys[i].p[j].a);
                }
        }
    
}


