########################################################
# command	output
# -------   	-----------------------------------
# make			Makes executable without debug info
# make debug	Makes executable with debug info
# make clean	Cleans executable, object files and core
#######################################################

#------------------------------------------------------------------------------

SOURCEDIR=./src
SOURCE=hashtable.cpp ./src/use_hashtable.cpp 
MYPROGRAM=use_hashtable
MYINCLUDES=-I./hdr

MYLIBRARIES=

DEFINES = -DLINUX -D_GCC3
CFLAGS= -Wall $(DEFINES)
CDEBUGFLAGS= -g -DDEBUG

CC=g++

#------------------------------------------------------------------------------


all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCEDIR)/$(SOURCE)
	$(CC) $(CFLAGS) $(MYINCLUDES) $(SOURCEDIR)/$(SOURCE) -o$(MYPROGRAM) 

debug: $(SOURCEDIR)/$(SOURCE)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(MYINCLUDES) $(SOURCEDIR)/$(SOURCE) -o$(MYPROGRAM)

clean:
	rm -f $(MYPROGRAM) *.o core
