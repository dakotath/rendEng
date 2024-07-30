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
#include <stdint.h>
#include "video.h"
#include "threading.h"

// Declare global variables for the window and renderer
Display InitVideo(int width, int height) {
    Display disp;
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
    return disp;
}
void ProbeEvents(Display disp)
{
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
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
void FillScreen(Display disp, int r, int g, int b, int a)
{
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}

// Font shit.
TrueTypeFont LoadTTF(void* data, uint64_t size, int fontSize)
{
    TrueTypeFont returndata;
    
    // Load in Data.
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);

    return returndata;
}
void PrintfTTF(int x, int y, TrueTypeFont font, char* text, int r, int g, int b, int a)
{
    // Print with ttf.
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}

#endif

#ifdef VIDEO_WII

#include <stdio.h>
#include <stdbool.h>
#include <grrlib.h>
#include "video.h"
#include "threading.h"

#include "font_ttf.h"
#include "splash_bg_jpg.h"

TrueTypeFont __videoc_font__;

uint32_t RGBToUint32(int r, int g, int b) {
    // Ensure that the RGB values are within the valid range (0-255)
    r = (r < 0) ? 0 : (r > 255) ? 255 : r;
    g = (g < 0) ? 0 : (g > 255) ? 255 : g;
    b = (b < 0) ? 0 : (b > 255) ? 255 : b;

    // Combine the RGB values into a single uint32
    return ((uint32_t)r << 32) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | 0xff;
}
u32 rgbaToU32(int r, int g, int b, int a)
{
    return (r<<24) | (g<<16) | (b<<8) | (a&0xff);
}

// Declare global variables for the window and renderer
void ProbeEvents(Display disp)
{
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}
Display InitVideo(int width, int height) {
    Display disp;
    // Set parameters for the terminal display.
    disp.width = width;
    disp.height = height;
    disp.window = NULL; // Not used in the terminal implementation
    disp.renderer = NULL; // Not used in the terminal implementation
    //printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
    GRRLIB_Init();

    __videoc_font__ = LoadTTF(font_ttf, font_ttf_size, 20);

    // Splash Screen.
    GRRLIB_texImg* splashBg = GRRLIB_LoadTextureJPG(splash_bg_jpg);

    char* fromMakersTxt = malloc(256);
    char* text2 = "CoreLib is created by Dakotath.";
    sprintf(fromMakersTxt, "%s for %s", VERSION, TARGET);

    int textWidth = GRRLIB_WidthTTF(__videoc_font__.font, fromMakersTxt, __videoc_font__.fontSize);
    int textWidth2 = GRRLIB_WidthTTF(__videoc_font__.font, text2, __videoc_font__.fontSize);

    int txtX = (width - textWidth) / 2;
    int txtX2 = (width - textWidth2) / 2;

    //int logoX = (width - 128) / 2;

    u32 bgColor;

    // fade in
    for(int i = 0; i <= 255; i+=2)
    {
        FillScreen(disp, 0xff,0xA8,0xA8,i); // Set alpha channel to i and RGB to white

        GRRLIB_DrawImg(0, 0, splashBg, 0, 1,1, rgbaToU32(255,255,255,i));

        PrintfTTF(txtX, 20, __videoc_font__, fromMakersTxt, 0,0,0, i);
        PrintfTTF(txtX2, height-28, __videoc_font__, text2, 0,0,0, i);
        
        GRRLIB_Render();
    }
    usleep(1000*1000);
    // fade out
    for(int i = 255; i >= 0; i-=2)
    {
        FillScreen(disp, 0xff,0xA8,0xA8,i); // Set alpha channel to i and RGB to white

        GRRLIB_DrawImg(0, 0, splashBg, 0, 1,1, rgbaToU32(255,255,255,i));

        PrintfTTF(txtX, 20, __videoc_font__, fromMakersTxt, 0,0,0, i);
        PrintfTTF(txtX2, height-28, __videoc_font__, text2, 0,0,0, i);
        
        GRRLIB_Render();
    }
    return disp;
}
void QuitVideo(Display disp) {
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}
void DrawRect(Display disp, int x, int y, int width, int height, int r, int g, int b, bool fill) {
    //printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
    GRRLIB_Rectangle(x,y, width,height, RGBToUint32(r,g,b), fill);
}
void RenderScreen(Display disp) {
    //("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
    GRRLIB_Render();
}
void DrawCircle(Display disp, int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, bool fill) {
    //printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
    GRRLIB_Circle(x,y, rad, RGBToUint32(r,g,b), fill);
}
void ClearScreen(Display disp)
{
    //printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
    GRRLIB_FillScreen(0x8a8a8aff);
}
void FillScreen(Display disp, int r, int g, int b, int a)
{
    GRRLIB_FillScreen(rgbaToU32(r,g,b,a));
}

// Font stuff
TrueTypeFont LoadTTF(void* data, uint64_t size, int fontSize)
{
    TrueTypeFont returndata;
    
    // Load in Data.
    returndata.font = GRRLIB_LoadTTF(data, size);
    returndata.fontSize = fontSize;

    // Return font.
    return returndata;
}
void PrintfTTF(int x, int y, TrueTypeFont font, char* text, int r, int g, int b, int a)
{
    // Print with ttf.
    GRRLIB_PrintfTTF(x, y, font.font, text, font.fontSize, rgbaToU32(r,g,b,a));
}

#endif

// terminal
#ifdef VIDEO_TERMINAL

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// linux specific includes
#ifdef BUILD_LINUX
#include <malloc.h>
#include <memory.h>
#endif
// end of linux specific includes

#include "video.h"
#include "threading.h"

void ProbeEvents(Display disp) {
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}

Display InitVideo(int width, int height) {
    Display disp;

    // Set parameters for the terminal display.
    disp.width = width;
    disp.height = height;
    disp.window = NULL; // Not used in the terminal implementation
    disp.renderer = NULL; // Not used in the terminal implementation

    // Initialize the terminal display.
    char* framebuffer = (char*)malloc(width * height * sizeof(char));
    if(framebuffer == NULL) {
        printf("Failed to allocate memory for framebuffer.\n");
        exit(0);
    }
    memset(framebuffer, ' ', width * height);

    // Return the framebuffer as a void pointer
    disp.renderer = (void*)framebuffer;

    return disp;
}

void QuitVideo(Display disp) {
    // Free the framebuffer memory
    free(disp.renderer);
}

void DrawRect(Display disp, int x, int y, int width, int height, int r, int g, int b, bool fill) {
    // Implement text-based rendering of rectangles in the terminal.
    char* framebuffer = (char*)disp.renderer;
    char fillChar = fill ? '#' : ' ';

    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            if (i >= 0 && i < disp.width && j >= 0 && j < disp.height) {
                framebuffer[i + j * disp.width] = fillChar;
            }
        }
    }
}

void RenderScreen(Display disp) {
    // Clear the terminal and render the framebuffer.
    system("clear");
    char* framebuffer = (char*)disp.renderer;

    for (int i = 0; i < disp.height; i++) {
        for (int j = 0; j < disp.width; j++) {
            putchar(framebuffer[j + i * disp.width]);
        }
        putchar('\n');
    }
}

void DrawCircle(Display disp, int x, int y, int rad, Uint8 r, Uint8 g, Uint8 b, bool fill) {
    // Implement text-based rendering of circles in the terminal.
    char* framebuffer = (char*)disp.renderer;
    char fillChar = fill ? '#' : ' ';

    for (int i = x - rad; i <= x + rad; i++) {
        for (int j = y - rad; j <= y + rad; j++) {
            if (i >= 0 && i < disp.width && j >= 0 && j < disp.height) {
                int dx = i - x;
                int dy = j - y;
                if (dx * dx + dy * dy <= rad * rad) {
                    framebuffer[i + j * disp.width] = fillChar;
                }
            }
        }
    }
}

void ClearScreen(Display disp) {
    // Clear the framebuffer and display.
    char* framebuffer = (char*)disp.renderer;
    memset(framebuffer, ' ', disp.width * disp.height);
}

void PrintfTTF(int x, int y, TrueTypeFont font, char* text, int r, int g, int b, int a)
{
    // Print with ttf.
    printf("Oh no, %s is not implemented for %s. %s line %d.\n", __FUNCTION__, TARGET, __FILE__, __LINE__);
}

// SDL2.
#ifdef VIDEO_SDL2

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "video.h"
#include "threading.h"

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

/**
 * @brief Fill Screen with color.
*/
void FillScreen(Display disp, int r, int g, int b, int a)
{
    
}

#endif

#endif

#endif