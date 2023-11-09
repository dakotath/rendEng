/**
 * @file video.c
 * 
 * All 2D rendering handlers.
 * 
 * @todo Add support to draw standard image types (png,jpg,bmp, and so on).
 */

#include "config.h"

// Only compile if USE_VIDEO defined.
#ifdef USE_VIDEO

#ifdef VIDEO_DUMMY // blank handlers, when porting to other systems, all of these must be present for the other systems.

#include <stdio.h>
#include <stdbool.h>
#include "video.h"
#include "threading.h"

// Declare global variables for the window and renderer
void ProbeEvents(Display disp)
{
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}
Display InitVideo(int width, int height) {
    Display disp;
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
    return disp;
}
void QuitVideo(Display disp) {
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}
void DrawRect(Display disp, int x, int y, int width, int height, int r, int g, int b, bool fill) {
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}
void RenderScreen(Display disp) {
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}
void DrawCircle(Display disp, int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, bool fill) {
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}
void ClearScreen(Display disp)
{
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}

#endif

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
 * 
 * @paragraph p1ff Function to initialize SDL2 and create a window and renderer.
 * 
 * @param width Screen Width.
 * @param height Screen Height.
*/
Display InitVideo(int width, int height) {
    Display disp;

    disp.width=width;
    disp.height=height;

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
 * @paragraph p1awd Function to clean up and quit SDL2.
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
 * @image html doc_img/sdl_test1.png "A simple white square."
 * 
 * @paragraph p1ert Function to draw a cool rectangle with SDL2.
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
 * @brief Draw A Circle.
 * 
 * @image html doc_img/circ_test1.png "A simple blue filled circle."
 * 
 * @paragraph drawCircp1 if you like the cool round shape called a Circle, use this to draw some!
 * 
 * @param x X position of your circle.
 * @param y Y position of your circle.
 * @param rad Radius for your circle.
 * 
 * @param r Red Amount (0-255).
 * @param g Green Amount (0-255).
 * @param b Blue Amount (0-255).
 * 
 * @param fill fill your circle.
*/
void DrawCircle(Display disp, int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, bool fill) {
    SDL_SetRenderDrawColor(disp.renderer, r, g, b, 255);
    if (fill) {
        for (int i = 0; i <= rad; i++) {
            int h = sqrt(rad * rad - i * i);
            SDL_RenderDrawLine(disp.renderer, x - h, y + i, x + h, y + i);
            SDL_RenderDrawLine(disp.renderer, x - h, y - i, x + h, y - i);
        }
    } else {
        int cx = rad;
        int cy = 0;
        int error = 1 - rad;

        while (cx >= cy) {
            SDL_RenderDrawPoint(disp.renderer, x + cx, y + cy);
            SDL_RenderDrawPoint(disp.renderer, x - cx, y + cy);
            SDL_RenderDrawPoint(disp.renderer, x + cx, y - cy);
            SDL_RenderDrawPoint(disp.renderer, x - cx, y - cy);
            SDL_RenderDrawPoint(disp.renderer, x + cy, y + cx);
            SDL_RenderDrawPoint(disp.renderer, x - cy, y + cx);
            SDL_RenderDrawPoint(disp.renderer, x + cy, y - cx);
            SDL_RenderDrawPoint(disp.renderer, x - cy, y - cx);

            if (error <= 0) {
                cy++;
                error += 2 * cy + 1;
            } else {
                cx--;
                cy++;
                error += 2 * (cy - cx) + 1;
            }
        }
    }

}

/**
 * @brief Render Drawn Items.
 * 
 * @paragraph p1zxc Use this once your done drawing your stuff to display the changes.
*/
void RenderScreen(Display disp) {
    ProbeEvents(disp);
    SDL_RenderPresent(disp.renderer);
}

/**
 * @brief Clearing the screen.
 * 
 * @paragraph clscrnp1 Use this when you want to clear your display.
*/
void ClearScreen(Display disp) {
    SDL_SetRenderDrawColor(disp.renderer, 0, 0, 0, 255);
    SDL_RenderClear(disp.renderer);
}

#endif

#endif