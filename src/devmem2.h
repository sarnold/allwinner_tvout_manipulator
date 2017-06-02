///////////////////////////////////////////////////////////////////////////
// Workfile: devmem2.h (Header)
// Author: Jan-Derk Bakker, Daniel Giritzer
// Date: 2017-06-02
// Description: Simple module to read/write from/to any location in memory.
// Remarks: assumes a 4k page size and that sizeof(unsigned long) == 4
// Revision: 1.2
// Copyright (C) 2000, Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
// Copyright (C) 2017, Daniel Giritzer (giri@nwrk.biz)
///////////////////////////////////////////////////////////////////////////
#ifndef DEVMEM2_H_INCLUDED
#define DEVMEM2_H_INCLUDED

/////////////////////////////////////////////////
/// \brief This function allows writing to memory
///        on the specified address.
///
/// \param unsigned long Address to write to
/// \param unsigned long  Value to write
/// \param int Access type, should be 'w' (word),
///        'h' (halfword), 'b'(byte)
/////////////////////////////////////////////////
int writemem(unsigned long address, unsigned long  writeval, int access_type);

/////////////////////////////////////////////////
/// \brief This function allows reading the memory
///        on the specified address.
///
/// \param unsigned long Address to read from
/// \param int Access type, should be 'w' (word),
///        'h' (halfword), 'b'(byte)
/// \param unsigned long* pointer result variable
/////////////////////////////////////////////////
int readmem(unsigned long address, int access_type, unsigned long *result);

#endif // DEVMEM2_H_INCLUDED
