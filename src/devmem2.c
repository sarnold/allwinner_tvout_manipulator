///////////////////////////////////////////////////////////////////////////
// Workfile: devmem2.c (Implementation)
// Author: Jan-Derk Bakker, Daniel Giritzer
// Date: 2017-06-02
// Description: Simple module to read/write from/to any location in memory.
// Remarks: -
// Revision: 1
// Copyright (C) 2000, Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
// Copyright (C) 2017, Daniel Giritzer (giri@nwrk.biz)
///////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

static void ERROR(char* custom)
{
    fprintf(stderr, "Error: %s \n", custom);
    fprintf(stderr, "Error Nr: %d, %s\n",
            errno, strerror(errno));
}

int writemem(char* address, char* value, int access_type)
{
    int fd;
    void *map_base = 0;
    void *virt_addr = 0;
    unsigned long writeval = 0;

    off_t target = strtoul(address, 0, 0);


    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {
        ERROR("Opening /dev/mem/ failed!");
        return EXIT_FAILURE;
    };

    // Map one page
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);

    if(map_base == (void *) -1)
    {
        ERROR("Mapping Memory Page Failed!");
        return EXIT_FAILURE;
    }


    writeval = strtoul(value, 0, 0);
    switch(access_type)
    {
    case 'b':
        *((unsigned char *) virt_addr) = writeval;
        break;
    case 'h':
        *((unsigned short *) virt_addr) = writeval;
        break;
    case 'w':
        *((unsigned long *) virt_addr) = writeval;
        break;
    default:
        ERROR("Wrong access_type set!");
        break;
    }


    if(munmap(map_base, MAP_SIZE) == -1)
    {
        ERROR("Unmapping Memory Page Failed!");
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}

int readmem(char* address, int access_type, unsigned long read_result)
{
    int fd;
    void *map_base, *virt_addr;
    off_t target;

    target = strtoul(address, 0, 0);


    // Try to open /dev/mem
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {
        //Print error on failure
        ERROR("Opening /dev/mem/ failed!");
        return EXIT_FAILURE;
    };

    // Map one page
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);

    // Check if mapping was successful
    if(map_base == (void *) -1)
    {
        ERROR("Mapping Memory Page Failed!");
        return EXIT_FAILURE;
    }

    virt_addr = map_base + (target & MAP_MASK);
    switch(access_type)
    {
    case 'b':
        read_result = *((unsigned char *) virt_addr);
        break;
    case 'h':
        read_result = *((unsigned short *) virt_addr);
        break;
    case 'w':
        read_result = *((unsigned long *) virt_addr);
        break;
    default:
        ERROR("Wrong access_type set!");
        break;
    }

    if(munmap(map_base, MAP_SIZE) == -1)
    {
        ERROR("Unmapping Memory Page Failed!");
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}

