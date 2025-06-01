#include "function.h"

int main(int argc, char* argv[])
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Errore inizializzazione SDL\n");
        return 1;
    }
    
    // Set OpenGL version and profile attributes before creating window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Window creation and Settings
    SDL_Window *window = SDL_CreateWindow(
        "Space Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_RESIZABLE
    );

    if (window == NULL){
        printf("Errore nella creazione della window \n");
        return 1;
    }

    /* Enable multisampling for a nice antialiased effect */
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == NULL){
        printf("Errore nella creazione del renderer \n");
        return 1;
    }

    int running = 1;
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                printf("Chiusura del programma\n");
                running = 0;
            }

        }

        SDL_Delay(16);
    }


    return 0;
}