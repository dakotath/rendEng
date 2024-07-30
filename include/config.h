// configuration for this code
#ifndef CONFIG_H
#define CONFIG_H

#define BUILD_LINUX // build for LINUX
//#define BUILD_MINGW // build for Windows
//#define BUILD_WII

// config for different functions
#define USE_THREADING
#define USE_VIDEO
#define VIDEO_SDL2
//#define VIDEO_TERMINAL
//#define VIDEO_DUMMY
//#define VIDEO_WII

// arch
#ifdef __i386__
#define TARGET "x86 (32-bit)"
#elif defined(__x86_64__)
#define TARGET "x86_64 (64-bit)"
#elif defined(__powerpc__)
#define TARGET "PowerPC"
#elif defined(__mips__)
#define TARGET "MIPS"
#elif defined(BUILD_WII) // Special case systems.
#define TARGET "Revolution OS"
#else
#define TARGET "Unknown or unsupported architecture"
#endif

// Version
#define VERSION "CoreRend Version 1.0.0"

#endif