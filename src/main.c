///////////////////////////////////////////////////////////////////////////
// Workfile: tvout.c (Implementation)
// Author: Daniel Giritzer
// Date: 2017-06-02
// Description: Simple Program to move the picture of the composite video
//              output.
// Remarks: -
// Revision: 1
// Copyright (C) 2017, Daniel Giritzer (giri@nwrk.biz)
///////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "devmem2.h"
#include "tvout.h"

void PrintUsageMessage(FILE* output)
{
    fprintf(output, "++++++++++++++++++++++++++++++\n");
    fprintf(output, "Usage: tvout [-m [-x val] [-y val]] \n\n");
    fprintf(output, "-m \t move \n");
    fprintf(output, "-x \t vertical offset in px \n");
    fprintf(output, "-x \t horizontal offset in px \n");
    fprintf(output, "\nThis program was created for the Armbian Project.\n");
    fprintf(output, "(c) 2017, Daniel G.\n");
    fprintf(output, "++++++++++++++++++++++++++++++\n");
}

int main(int argc, char **argv)
{
    bool mFlag = false;
    bool xFlag = false;
    char* xVal = 0;
    bool yFlag = false;
    char* yVal = 0;
    char c;

    if(argc < 2)
    {
        PrintUsageMessage(stdout);
    }

    // Use getopt to parse the cmd parameters
    while ((c = getopt (argc, argv, "mx:y:?")) != -1)
        switch (c)
        {
        case 'm':
            mFlag = true;
            break;
        case 'x':
            xFlag = true;
            xVal = optarg;
            break;
        case 'y':
            yFlag = true;
            yVal = optarg;
            break;
        case '?':
            //Print usage message
            PrintUsageMessage(stdout);
            return EXIT_FAILURE;
        default:
            abort ();
        }


    //check if m flag was set
    if(mFlag)
    {
        unsigned long to_write = 0;

        // read current position
        readmem(TV_ENCODER_RESYNC, 'w', &to_write);
        if(xFlag)
        {
            //Set new X value
            to_write += strtoul(xVal, 0, 0) << X_REG_OFFSET;
        }

        if(yFlag)
        {
            //Set new Y value
            to_write += strtoul(yVal, 0, 0) << Y_REG_OFFSET;
        }
        //write new position to register
        writemem(TV_ENCODER_RESYNC, to_write, 'w');
    }

    for (unsigned int index = optind; index < argc; index++)
    {
        printf ("Non-option argument %s\n", argv[index]);
    }
    return EXIT_SUCCESS;
}
