############################################################################
# Workfile: Makefile
# Author: Daniel Giritzer, S1510306010
#	  giri@nwrk.biz
# Date: 06.04.2016
# Description:	Universal Makefile for Unix based Operating Systems
#
# Remarks:	Compatible with CodeBlocks (C::B)
#			PROJNAME variable should match your project name!
# Revision: 5.4
# Usage: make debug		- builds debug version
#		 make release	- builds release version
#		 make all	- builds debug and release version
#		 make clean	- cleans project
#		 make rebuild	- builds everything from scratch
############################################################################

####################
#GENERAL | EDIT 1/3
####################
WORKDIR = $(shell pwd)
SOURCES := $(shell ls *.c)
PROJNAME = tvout

CC = gcc
CXX = g++
AR = ar
LD = gcc
WINDRES = windres

INC =
CFLAGS = -Wall -fexceptions
RESINC =
LIBDIR =
LIB =
LDFLAGS =

############################
#DEBUG SETTINGS | EDIT: 2/3
############################
INC_DEBUG = $(INC)
CFLAGS_DEBUG = $(CFLAGS) -g
RESINC_DEBUG = $(RESINC)
RCFLAGS_DEBUG = $(RCFLAGS)
LIBDIR_DEBUG = $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG = $(LDFLAGS)
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG =
OUT_DEBUG = bin/Debug/$(PROJNAME)


##############################
#RELEASE SETTINGS | EDIT: 3/3
##############################
INC_RELEASE = $(INC)
CFLAGS_RELEASE = $(CFLAGS) -O2
RESINC_RELEASE = $(RESINC)
RCFLAGS_RELEASE = $(RCFLAGS)
LIBDIR_RELEASE = $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE = $(LDFLAGS) -s
OBJDIR_RELEASE = obj/Release
DEP_RELEASE =
OUT_RELEASE = bin/Release/$(PROJNAME)

############################
#OBJECT LISTS | DO NOT EDIT!
############################
OBJ_DEBUG = $(addprefix $(OBJDIR_DEBUG)/,$(SOURCES:%.c=%.o))
OBJ_RELEASE = $(addprefix $(OBJDIR_RELEASE)/,$(SOURCES:%.c=%.o))


##########################
#FUNCTIONS | DO NOT EDIT!
##########################

######## General
all All: debug release
clean Clean: cleanDebug cleanRelease
rebuild Rebuild: clean debug release

######## DEBUG
before_debug:
	test -d bin/Debug || mkdir -p bin/Debug
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug:

debug Debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LDFLAGS_DEBUG) $(LIBDIR_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG) -o $(OUT_DEBUG)

$(OBJDIR_DEBUG)/%.o: %.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c $< -D_DEBUG -o $@

clean_debug cleanDebug:
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/Debug
	rm -rf $(OBJDIR_DEBUG)


######## RELEASE
before_release:
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release:

release Release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LDFLAGS_RELEASE) $(LIBDIR_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE) -o $(OUT_RELEASE)

$(OBJDIR_RELEASE)/%.o: %.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c $< -o $@

clean_release cleanRelease:
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug cleanDebug before_release after_release clean_release cleanRelease

