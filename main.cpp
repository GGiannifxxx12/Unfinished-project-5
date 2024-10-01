#include <SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

SDL_Window* createWindow() {
    SDL_Window* window = SDL_CreateWindow("3D Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    return window;
}

SDL_GLContext createContext(SDL_Window* window) {
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        std::cerr << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    return glContext;
}

void initOpenGL() {
    glewExperimental = GL_TRUE; // Allow modern OpenGL
    if (glewInit() != GLEW_OK) {
        std::cerr << "Could not initialize GLEW!" << std::endl;
        exit(1);
    }
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

void render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Render your 3D objects here
}

int main(int argc, char* argv[]) {
    initSDL();
    SDL_Window* window = createWindow();
    SDL_GLContext glContext = createContext(window);
    initOpenGL();

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        render();
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
