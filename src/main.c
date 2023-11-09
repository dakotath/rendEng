#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "threading.h"
#include "video.h"

Display disp;

ThreadFunction testThread1(ThreadParams params) {
    while (1)
    {
        printf("Thread 1 test.\n");

        // wait for other code to run
        udelay(1000);
    }
    return NULL;
}

ThreadFunction mainThread(ThreadParams params) {
    while (1)
    {
        printf("Main Thread.\n");

        // wait
        udelay(400);
    }
    return NULL;
}

ThreadFunction rendererThread(ThreadParams params) {
    int ballX = 64;
    int ballY = 128;
    int ballRadius = 20;
    int ballSpeedX = 3;
    int ballSpeedY = 2;

    while (1) {
        // Clear the screen or draw a background
        //SDL_SetRenderDrawColor(disp.renderer, 0, 0, 0, 255);
        //SDL_RenderClear(disp.renderer);
        ClearScreen(disp);

        // Update ball position
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        // Check for collisions with the screen edges
        if (ballX - ballRadius < 0 || ballX + ballRadius > disp.width) {
            ballSpeedX = -ballSpeedX; // Reverse X direction
        }
        if (ballY - ballRadius < 0 || ballY + ballRadius > disp.height) {
            ballSpeedY = -ballSpeedY; // Reverse Y direction
        }

        // Render the ball
        DrawCircle(disp, ballX, ballY, ballRadius, 0, 0, 255, true);

        // Show the draws
        RenderScreen(disp);

        // Delay for animation
        udelay(10);
    }

    return NULL;
}


#undef main

int main(int argc, char** argv) {
    // print core info
    printCoreInfo();

    // init video
    int screenW = 320;
    int screenH = 240;
    disp = InitVideo(screenW, screenH);

    // setup thread infos
    ThreadParams testT1Params = NULL;
    ThreadInfo *testT1Info = InitThread(testThread1, testT1Params);
    ThreadInfo *mainThreadInfo = InitThread(mainThread, testT1Params);
    ThreadInfo *renderThreadInfo = InitThread(rendererThread, NULL);

    // start it
    StartThread(testT1Info);
    StartThread(mainThreadInfo);
    StartThread(renderThreadInfo);

    // Wait for our main thread to stop
    WaitForThread(mainThreadInfo);

    return 0;
}