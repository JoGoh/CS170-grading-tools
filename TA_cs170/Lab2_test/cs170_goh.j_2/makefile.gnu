# Macros ========================================
CC = g++
CFLAGS =  -Wall -Wextra -Werror -ansi -pedantic -c -std=c++11
OBJFLAG = -o
EXEFLAG = -o
OUTDIR = gnu\\

SRC1 = main.cpp
SRC2 = list.cpp
HDR2 = list.h

OBJ1 = $(OUTDIR)main.o
OBJ2 = $(OUTDIR)list.o
OBJS= $(OBJ2) $(OBJ1)

EXE = $(OUTDIR)out.exe
ERASE = rm
MAKEFILE = makefile.gnu


# Targets ========================================
$(EXE) : $(OBJS)
	$(CC) $(EXEFLAG) $(EXE) $(OBJS)

$(OBJ1) : $(SRC1)
	$(CC) $(OBJFLAG) $(OBJ1) $(CFLAGS) $(SRC1)

$(OBJ2) : $(SRC2) $(HDR2)
	$(CC) $(OBJFLAG) $(OBJ2) $(CFLAGS) $(SRC2)

clean :
	-$(ERASE) $(OBJS) $(EXE)
	
rebuild :
	-$(ERASE) $(OBJS) $(EXE)
	-$(MAKE) -f $(MAKEFILE) -i