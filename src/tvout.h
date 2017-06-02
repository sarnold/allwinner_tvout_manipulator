///////////////////////////////////////////////////////////////////////////
// Workfile: tvout.h (Header)
// Author: Daniel Giritzer
// Date: 2017-06-02
// Description: Provides Adresses to the TV Encoder Registers
// Remarks: -
// Revision: 1
// Copyright (C) 2017, Daniel Giritzer (giri@nwrk.biz)
///////////////////////////////////////////////////////////////////////////
#ifndef TVOUT_H_INCLUDED
#define TVOUT_H_INCLUDED

#define TV_ENCODER_BASE 0x01E00000
#define TV_ENCODER_RESYNC TV_ENCODER_BASE + 0x130
#define Y_REG_OFFSET 15
#define X_REG_OFFSET 0

#endif // TVOUT_H_INCLUDED
