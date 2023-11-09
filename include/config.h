// configuration for this code
#ifndef CONFIG_H
#define CONFIG_H

#ifdef __i386__
const char* TARGET = "x86 (32-bit)";
#elif defined(__x86_64__)
const char* TARGET = "x86_64 (64-bit)";
#elif defined(__powerpc__)
const char* TARGET = "PowerPC";
#elif defined(__mips__)
const char* TARGET = "MIPS";
#else
const char* TARGET = "Unknown or unsupported target architecture";
#endif

// Version
#define VERSION "CoreRend Version 1.0.0"

#define BUILD_LINUX // build for LINUX

// config for different functions
#define USE_THREADING
#define USE_VIDEO
#define VIDEO_SDL2

#endif