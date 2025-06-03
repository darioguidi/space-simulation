#include "function.h"

GLuint VAO;
GLuint VBO;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aPos;\n"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0);\n"
"}\n\0";



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

    // Generazione punti spazio 
    Point *space_points = generateSpaceGrid();
    
    // Creazione dell Array_Data
    Point array_data[4];
    for(int i=0;i<4;i++){
        array_data[i] = *(space_points+i);
    } 

    // Impostazione della Viewport
    glViewport(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);

    // Definizione della Shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Passiamo il codice definito sopra come stringa - GSLS
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compilazione del codice in linguaggio assembly 
    glCompileShader(vertexShader);

    // Definizione della FragmentShader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Passiamo il codice definito sopra come stringa - GSLS
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compilazione del codice in linguaggio assembly 
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Generazione Buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(array_data), array_data, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    
    
    // Imposta il colore di sfondo (nero opaco)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

        // Pulisce il buffer colore usando il colore impostato
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, 3);

        drawSpaceGrid();

        SDL_Delay(16);              // 60 FPS
        SDL_GL_SwapWindow(window);  // Scambia i buffer per visualizzare il frame appena renderizzato
    }

    free(space_points);
    
    // Pulizia delle risorse e uscita
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
