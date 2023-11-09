#ifndef VIDEO_H
#define VIDEO_H

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

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} Display;

Display InitVideo(int width, int height);
void QuitVideo(Display disp);
void DrawRect(Display disp, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, bool fill);
void RenderScreen(Display disp);

#else // dummy

#include <stdio.h>
#include <stdbool.h>

typedef struct {
    void* window;
    void* renderer;
} Display;

Display InitVideo(int width, int height);
void QuitVideo(Display disp);
void DrawRect(Display disp, int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, bool fill);
void RenderScreen(Display disp);

#endif

#endif

#endif

#endif