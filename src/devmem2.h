///////////////////////////////////////////////////////////////////////////
// Workfile: devmem2.h (Implementation)
// Author: Jan-Derk Bakker, Daniel Giritzer
// Date: 2017-06-02
// Description: Simple module to read/write from/to any location in memory.
// Remarks: -
// Revision: 1
// Copyright (C) 2000, Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
// Copyright (C) 2017, Daniel Giritzer (giri@nwrk.biz)
///////////////////////////////////////////////////////////////////////////
#ifndef DEVMEM2_H_INCLUDED
#define DEVMEM2_H_INCLUDED


int writemem(char* address, char* value, int access_type);

int readmem(char* address, int access_type, unsigned long *result);


#endif // DEVMEM2_H_INCLUDED
