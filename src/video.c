/**
 * @file video.c
 * 
 * All 2D rendering handlers.
 */

#include "config.h"

// Only compile if USE_VIDEO defined.
#ifdef USE_VIDEO

// Linux Video.
#ifdef BUILD_LINUX

// SDL2.
#ifdef VIDEO_SDL2

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "video.h"
#include "threading.h"

// Declare global variables for the window and renderer
void ProbeEvents(Display disp)
{
    SDL_Event event;

    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            //quit = 1;
            QuitVideo(disp);
        }
    }
}

/**
 * @brief Init Video.
 * @image html doc_img/sdl_test1.png "SDL2 Working"
 * 
 * @paragraph p1 Function to initialize SDL2 and create a window and renderer.
 * 
 * @param width Screen Width.
 * @param height Screen Height.
*/
Display InitVideo(int width, int height) {
    Display disp;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        //return -1;
    }

    disp.window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (disp.window == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        //return -1;
    }

    disp.renderer = SDL_CreateRenderer(disp.window, -1, SDL_RENDERER_ACCELERATED);
    if (disp.renderer == NULL) {
        printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(disp.window);
        SDL_Quit();
        //return -1;
    }
    
    // render a box in the center
    DrawRect(disp, (width/2)-(32/2), (height/2)-(32/2), 32,32, 255,255,255, true);
    RenderScreen(disp);

    return disp;
}

/**
 * @brief Quit Video.
 * 
 * @paragraph p1 Function to clean up and quit SDL2.
*/
void QuitVideo(Display disp) {
    if (disp.renderer != NULL) {
        SDL_DestroyRenderer(disp.renderer);
        disp.renderer = NULL;
    }

    if (disp.window != NULL) {
        SDL_DestroyWindow(disp.window);
        disp.window = NULL;
    }

    SDL_Quit();
}

/**
 * @brief Draw Rectangles.
 * 
 * @paragraph p1 Function to draw a cool rectangle with SDL2.
 * 
 * @param x X Position of your Rectangle.
 * @param y Y Position of your Rectangle.
 * @param width Width of the Rectangle.
 * @param height Height of the Rectangle.
 * 
 * @param r Red Amount (0-255).
 * @param g Green Amount (0-255).
 * @param b Blue Amount (0-255).
 * 
 * @param fill Option to fill your Rectangle.
*/
void DrawRect(Display disp, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, bool fill) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(disp.renderer, r, g, b, 255);

    // draw it
    if(fill==true)
    {
        SDL_RenderFillRect(disp.renderer, &rect);
    }
    else {
        SDL_RenderDrawRect(disp.renderer, &rect);
    }
}

/**
 * @brief Render Drawn Items.
 * 
 * @paragraph p1 Use this once your done drawing your stuff to display the changes.
*/
void RenderScreen(Display disp) {
    ProbeEvents(disp);
    SDL_RenderPresent(disp.renderer);
}

// Add more drawing functions as needed

#endif

#endif

#endif
