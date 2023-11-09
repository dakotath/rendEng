#ifndef VIDEO_H
#define VIDEO_H

#include "config.h"

// Only compile if USE_VIDEO defined.
#ifdef USE_VIDEO

// SDL2.
#ifdef VIDEO_SDL2

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
} Display;

Display InitVideo(int width, int height);
void QuitVideo(Display disp);
void DrawRect(Display disp, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, bool fill);
void RenderScreen(Display disp);
void DrawCircle(Display disp, int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, bool fill);
void ClearScreen(Display disp);

#endif

#ifdef VIDEO_DUMMY // dummy

#include <stdio.h>
#include <stdbool.h>

typedef unsigned char Uint8;

typedef struct {
    void* window;
    void* renderer;
    int width;
    int height;
} Display;

Display InitVideo(int width, int height);
void QuitVideo(Display disp);
void DrawRect(Display disp, int x, int y, int width, int height, int r, int g, int b, bool fill);
void RenderScreen(Display disp);
void DrawCircle(Display disp, int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, bool fill);
void ClearScreen(Display disp);

#endif

#endif

#endif