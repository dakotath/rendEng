// configuration for this code
#ifndef CONFIG_H
#define CONFIG_H

// arch
#ifdef __i386__
#define TARGET "x86 (32-bit)"
#elif defined(__x86_64__)
#define TARGET "x86_64 (64-bit)"
#elif defined(__powerpc__)
#define TARGET "PowerPC"
#elif defined(__mips__)
#define TARGET "MIPS"
#else
#define TARGET "Unknown or unsupported target architecture"
#endif

// Version
#define VERSION "CoreRend Version 1.0.0"

#define BUILD_LINUX // build for LINUX

// config for different functions
#define USE_THREADING
#define USE_VIDEO
#define VIDEO_SDL2

#endif