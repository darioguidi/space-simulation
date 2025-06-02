#include "function.h"

int main(int argc, char* argv[])
{
    // Inizializza SDL con il supporto video
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Errore inizializzazione SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Imposta la versione di OpenGL (3.3) e il profilo core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Crea una finestra SDL con supporto OpenGL e possibilità di ridimensionamento
    SDL_Window *window = SDL_CreateWindow(
        "Space Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );

    // Controlla che la finestra sia stata creata correttamente
    if (window == NULL){
        printf("Errore nella creazione della finestra: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crea il contesto OpenGL associato alla finestra
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (glContext == NULL){
        printf("Errore nella creazione del contesto OpenGL: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Inizializza GLEW per gestire le estensioni OpenGL
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        printf("Errore nell'inizializzazione di GLEW: %s\n", glewGetErrorString(err));
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Loop principale del programma
    int running = 1;
    SDL_Event event;

    while (running){
        // Gestione degli eventi SDL
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                printf("Chiusura del programma\n");
                running = 0;
            }
        }

        // Imposta il colore di sfondo (nero opaco)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        // Pulisce il buffer colore usando il colore impostato
        glClear(GL_COLOR_BUFFER_BIT);

        // Rendering della scena (da implementare)

        SDL_Delay(16);              // Pausa per mantenere circa 60 FPS
        SDL_GL_SwapWindow(window);  // Scambia i buffer per visualizzare il frame appena renderizzato
    }

    // Pulizia delle risorse e uscita
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
