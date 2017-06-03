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

/////////////////////////////////////////////////
/// \brief This function gets called by the program
///        to print the usage message.
///
/// \param FILE* output file descriptor
/////////////////////////////////////////////////
void PrintUsageMessage(FILE* output)
{
    fprintf(output, "++++++++++++++++++++++++++++++++++++++++\n");
    fprintf(output, "Usage: tvout [-m [-r][-x val] [-y val]] \n\n");
    fprintf(output, "-m \t move the picture\n");
    fprintf(output, "  -x \t vertical offset in px \n");
    fprintf(output, "  -y \t horizontal offset in px \n");
    fprintf(output, "  -r \t reset position \n");
    fprintf(output, "\nThis program was created for the \nArmbian Project.\n");
    fprintf(output, "(c) 2017, Daniel G. (giri@nwrk.biz)\n");
    fprintf(output, "++++++++++++++++++++++++++++++++++++++++\n");
}

/////////////////////////////////////////////////
/// \brief Main Program. Parses Commandline
///        Parameters and writes user Input
///        to the matching TV-Encoder registers.
/////////////////////////////////////////////////
int main(int argc, char **argv)
{
    bool mFlag = false; //move
    bool xFlag = false; //y Offset
    char* xVal = 0;
    bool yFlag = false; //x Offset
    char* yVal = 0;
    bool rFlag = false; //reset Offset
    int c;

    //let us do the errorhandling
    opterr = 0;

    //check if there are any arguments
    if(argc < 2)
    {
        PrintUsageMessage(stdout);
    }

    // Use getopt to parse the cmd parameters
    while ((c = getopt (argc, argv, "mx:y:r")) != -1)
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
        case 'r':
            rFlag = true;
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

        if(rFlag)
        {
            //reset position
            writemem(TV_ENCODER_RESYNC, to_write, 'w');
        }
        else
        {
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
    }

    unsigned int index = 0;
    for (index = optind; index < argc; index++)
    {
        printf ("Invalid argument %s\n", argv[index]);
    }
    return EXIT_SUCCESS;
}
