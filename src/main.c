///////////////////////////////////////////////////////////////////////////
// Workfile: tvout.c (Implementation)
// Author: Daniel Giritzer
// Date: 2017-06-02
// Description: Simple Program to move the
// Remarks: -
// Revision: 1
// Copyright (C) 2017, Daniel Giritzer (giri@nwrk.biz)
///////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "devmem2.h"
#include "tvout.h"


int main(int argc, char **argv)
{
    unsigned long to_write = 0;


    //Print usage message
    if(argc != 3)
    {
        fprintf(stdout, "Usage: tvout <move x> <move y>\n");
        fprintf(stdout, "The parameter values should be in px.\n");
        fprintf(stdout, "This program was created for the Armbian Project.");
        fprintf(stdout, "(c) 2017, Daniel G.");
        return EXIT_SUCCESS;
    }

    //Set X value
    to_write = strtoul(argv[1], 0, 0) << X_REG_OFFSET;

    //Set Y value
    to_write = strtoul(argv[2], 0, 0) << Y_REG_OFFSET;

    //write to register
    writemem(TV_ENCODER_RESYNC, to_write, 'w');

    return EXIT_SUCCESS;
}
