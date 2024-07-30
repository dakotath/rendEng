#ifndef THREADING_H
#define THREADING_H

#include <stdio.h>
#include "config.h"

// threading.h 2023 Dakota Thorpe

#ifdef USE_THREADING

// Windows MINGW
#ifdef BUILD_MINGW

#include <windows.h>

#define ThreadFunction DWORD WINAPI
#define ThreadParams LPVOID
#define udelay(ms) Sleep(ms)

/**
 * @brief ThreadInfo structure.
 * @paragraph p1 The ThreadInfo structure.
 * 
 * @param func The thread function.
 * @param params Parameters for threads
 * @param threadHandle A controlable thread handle.
*/
typedef struct {
    ThreadFunction func; /* Thread Function */
    ThreadParams params; /* Thread parameters */
    HANDLE threadHandle; /* The handle for the thread. */
} ThreadInfo;

#elif defined BUILD_LINUX // Linux

#include <pthread.h>

typedef void* ThreadFunction;
typedef void* ThreadParams;

#define udelay(ms) usleep(ms * 1000)

/**
 * @brief ThreadInfo structure.
 * @paragraph p1 The ThreadInfo structure.
 * 
 * @param func The thread function.
 * @param params Parameters for threads
 * @param threadHandle A controllable thread handle.
 */
typedef struct {
    ThreadFunction func; /* Thread Function */
    ThreadParams params; /* Thread parameters */
    pthread_t threadHandle; /* The handle for the thread. */
} ThreadInfo;

#elif defined BUILD_WII // Nintendo Wii

#include <gccore.h>

typedef void* ThreadFunction;
typedef void* ThreadParams;

#define udelay(ms) usleep(ms * 1000)

typedef struct {
    ThreadFunction func;
    ThreadParams params;
    lwp_t threadHandle;
} ThreadInfo;

#else // Dummy

typedef void* ThreadFunction;
typedef void* ThreadParams;

#define udelay(ms) usleep(ms * 1000)

typedef struct {
    ThreadFunction func;
    ThreadParams params;
    int threadHandle;
} ThreadInfo;

#endif

ThreadInfo *InitThread(ThreadFunction func, ThreadParams params);
void StartThread(ThreadInfo* thread);
void WaitForThread(ThreadInfo* thread);
void DestroyThread(ThreadInfo* thread);

#endif

#endif