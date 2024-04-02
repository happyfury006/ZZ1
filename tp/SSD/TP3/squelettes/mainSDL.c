#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sierpinski.h"

SDL_Renderer * renderer=NULL;


void dessineLigne(int x1,int y1,int x2,int y2){
    SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
}

void dessineTriangle(triangle abc){
    // TO DO question 17

}
void dessineListe(list_triangles*l){
    // TO DO question 17
}
void dessineFractale(){
    // TO DO question 17
    
    // Exemple d'appel à la fonction dessineLigne
    dessineLigne(20,30,240,250);
}

void dessinerFenetre() 
{

/* on prépare/efface le renderer */
SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
SDL_RenderClear(renderer);

/* dessiner en blanc */
SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

dessineFractale();

/* afficher le renderer dans la fenetre */
SDL_RenderPresent(renderer);
}

int main(){
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        return EXIT_FAILURE; 
    }


    // Création d'une fenetre
    SDL_Window   * window;

    int width=1000 , height=800;

    window = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                width, height, 
                SDL_WINDOW_RESIZABLE); 
        
    if (window == 0) 
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        /* on peut aussi utiliser SLD_Log() */
    }

    // SDL_Renderer *renderer;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED ); /*  SDL_RENDERER_SOFTWARE */
    if (renderer == 0) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
        /* faire ce qu'il faut pour quitter proprement */
    }
    dessinerFenetre();
    SDL_Delay(5000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

