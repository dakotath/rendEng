/**
 * @file utils.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "config.h"

/**
 * @brief Print the details of the corelib build
 */
void printCoreInfo() {
    // info
    printf("%s %s.\nGCC version: %d.%d.%d\nCompiled on %s at %s\n\n", VERSION, TARGET, __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__, __DATE__, __TIME__);

    // print capabilities
    printf("Core Capabilities:\n");
    #ifdef USE_THREADING
    printf("\tThreading.c - 2023 Dakota Thorpe.\n");
    #endif
    #ifdef USE_VIDEO
    printf("\tVideo.c - 2023 Dakota Thorpe.\n");
    #endif
    printf("\n");
}