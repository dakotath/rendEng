/**
 * @file threading.c
 *
 * This file contains the implementation of the threading module.
 */

#include "config.h"

#ifdef USE_THREADING

#include "threading.h"

#ifdef BUILD_MINGW
#include <windows.h> // Windows
#elif defined BUILD_LINUX // Linux
#include <stdlib.h>
#include <pthread.h>
#elif defined BUILD_WII // Wii

#include <gccore.h>
#include <ogcsys.h>

#endif

/**
 * @brief Thread Information.
 * @paragraph p1es this is used to initialize threads into a controllable struct (Ex: stop, start, and wait functions).
 * 
 * @param func The function of the thread you are initializing
 * @param params Any parameters you need to pass to the thread function (Leave NULL if unused).
 */
ThreadInfo *InitThread(ThreadFunction func, ThreadParams params) {
    ThreadInfo *thread = malloc(sizeof(ThreadInfo));
    if (thread == NULL) {
        printf("Failed to allocate memory for ThreadInfo.\n");
        return NULL;
    }

    thread->func = func;
    thread->params = params;

#ifdef BUILD_MINGW
    thread->threadHandle = CreateThread(NULL, 0, thread->func, thread->params, 0, NULL);
#elif defined BUILD_LINUX // Linux
    if (pthread_create(&thread->threadHandle, NULL, thread->func, thread->params) != 0) {
        printf("Failed to create a new thread.\n");
        free(thread);
        return NULL;
    }
#elif defined BUILD_WII
    LWP_CreateThread(&thread->threadHandle, func, NULL, NULL, 0, 80);
#endif

    return thread;
}

/**
 * @brief Starting Threads.
 * @paragraph p1esd To start threads, use StartThread to startup your thread.
 * 
 * @param *thread A ThreadInfo that can be created with InitThread().
 */
void StartThread(ThreadInfo* thread) {
#ifdef BUILD_MINGW
    if (thread->threadHandle != NULL) {
        ResumeThread(thread->threadHandle);
    }
#elif defined BUILD_LINUX // Linux
    // Add Linux-specific thread starting code here
#elif defined BUILD_WII
    LWP_ResumeThread(thread->threadHandle);
#endif
}

/**
 * @brief Waiting For Threads to Finish.
 * @paragraph p1ad If you want to wait for a thread to finish up, use this.
 * 
 * @param *thread A ThreadInfo that can be created with InitThread().
 */
void WaitForThread(ThreadInfo* thread) {
#ifdef BUILD_MINGW
    if (thread->threadHandle != NULL) {
        WaitForSingleObject(thread->threadHandle, INFINITE);
    }
#elif defined BUILD_LINUX // Linux
    if (pthread_join(thread->threadHandle, NULL) != 0) {
        printf("Failed to join the thread.\n");
    }
#elif defined BUILD_WII // Wii
    if(LWP_JoinThread(thread->threadHandle, NULL) != 0)
    {
        printf("Failed to join the thread.\n");
    }
#endif
}

/**
 * @brief Destroying Threads.
 * @paragraph p1aw To clear threads, use this function to wipe the thread to NULL.
 * 
 * @param *thread The thread you want to clear.
 */
void DestroyThread(ThreadInfo* thread) {
#ifdef BUILD_MINGW
    if (thread->threadHandle != NULL) {
        CloseHandle(thread->threadHandle);
    }
#elif defined BUILD_LINUX // Linux
    // Add Linux-specific thread destruction code here
#endif
    free(thread);
}

#endif
