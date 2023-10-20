#include <stdio.h>
#include "vue_controller/vue_controller.h"
#include "model/model.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main(int argc, char *argv[]){
    const char *config_name = argv[1];
    game* g = readFile(config_name);



    /*SDL_Init(SDL_INIT_EVERYTHING);

 //checking the number of arguments passed on the command line
    if(argc != 2){
        printf("Please pass a configuration file as a parameter\n");
        return 1;
    }

    char *config_name = argv[1];

    SDL_Event ev;
    

    game* g;

    if (readFile(g, config_name) == 1){
        printf("Erreur lors de la lecture du fichier\n");
        return 1;
    }
    









    initSDL(file);  //Initialisation 

    int run = 1;
    //printf("run avant la boucle: %d\n",run);
    while(run != 0){
        //printf("run pendant la boucle mais hors de la fonction: %d\n",run);
        handleEvents(ev,run);
        printf("run apres la fonction : %d\n",run);
        render(file);
    }
    
    
    
    
    //closing the file and cleaning the memory
    
    

    closeSDL();


    //displayWin("../../config.txt");

    //createSolarSystem(SDL_Window * win, char *config_name);
    */
    return 0;
}