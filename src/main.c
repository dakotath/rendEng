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
    while (1)
    {
        // rendering
        DrawRect(disp, 0,0, 32,32, 255,255,0, true);

        // show draws
        RenderScreen(disp);

        udelay(1);
    }
    return NULL;
}

int main() {
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