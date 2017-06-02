///////////////////////////////////////////////////////////////////////////
// Workfile: devmem2.c (Implementation)
// Author: Jan-Derk Bakker, Daniel Giritzer
// Date: 2017-06-02
// Description: Simple module to read/write from/to any location in memory.
// Remarks: assumes a 4k page size and that sizeof(unsigned long) == 4
// Revision: 1.2
// Copyright (C) 2000, Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
// Copyright (C) 2017, Daniel Giritzer (giri@nwrk.biz)
///////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "devmem2.h"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)


/////////////////////////////////////////////////
/// \brief This function is called by the module
///        if an error occurs.
///
/// \param char* Custom error Message.
/////////////////////////////////////////////////
static void ERROR(char* custom)
{
    //print custom error message
    fprintf(stderr, "Error: %s \n", custom);

    //print further information
    fprintf(stderr, "Info: %d, %s\n",
            errno, strerror(errno));
}

/////////////////////////////////////////////////
/// \brief This function allows writing to memory
///        on the specified address.
///
/// \param unsigned long Address to write to
/// \param unsigned long Value to write
/// \param int Access type, should be 'w' (word),
///        'h' (halfword), 'b'(byte)
/////////////////////////////////////////////////
int writemem(unsigned long address, unsigned long writeval, int access_type)
{
    int fd;
    void *map_base = 0;
    void *virt_addr = 0;

    off_t target = address;

    // Try to open /dev/mem
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1)
    {
        ERROR("Opening /dev/mem/ failed!");
        return EXIT_FAILURE;
    };

    // Map one page
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);

    // Check if mapping was successful
    if(map_base == (void *) -1)
    {
        //Print error on failure
        ERROR("Mapping Memory Page Failed!");
        return EXIT_FAILURE;
    }

    //calculate virtual address
    virt_addr = map_base + (target & MAP_MASK);

    //write value to memory
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

    //unmap memory
    if(munmap(map_base, MAP_SIZE) == -1)
    {
        ERROR("Unmapping Memory Page Failed!");
        return EXIT_FAILURE;
    }

    close(fd);
    return EXIT_SUCCESS;
}

/////////////////////////////////////////////////
/// \brief This function allows reading the memory
///        on the specified address.
///
/// \param unsigned long Address to read from
/// \param int Access type, should be 'w' (word),
///        'h' (halfword), 'b'(byte)
/// \param unsigned long* pointer result variable
/////////////////////////////////////////////////
int readmem(unsigned long address, int access_type, unsigned long *result)
{
    int fd;
    void *map_base, *virt_addr;
    unsigned long read_result = 0;

    off_t target = address;

    //check if result variable is a nullpointer
    if(result == NULL)
    {
        //Print error on failure
        ERROR("Result Parameter is a nullpointer!");
        return EXIT_FAILURE;
    }


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

    //calculate virtual address
    virt_addr = map_base + (target & MAP_MASK);

    //read value
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

    // unmap memory
    if(munmap(map_base, MAP_SIZE) == -1)
    {
        ERROR("Unmapping Memory Page Failed!");
        return EXIT_FAILURE;
    }

    // return result
    *result = read_result;

    close(fd);
    return EXIT_SUCCESS;
}

