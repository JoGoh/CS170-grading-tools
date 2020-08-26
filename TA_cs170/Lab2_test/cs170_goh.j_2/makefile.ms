# Macros ========================================
CC = cl
NOLGFLAG = /nologo
CFLAGS = /W4 /WX /Za /c /EHsc
OBJFLAG = /Fo
EXEFLAG = /Fe
OUTDIR = ms\\

SRC1 = main.cpp
SRC2 = list.cpp
HDR2 = list.h

OBJ1 = $(OUTDIR)main.obj
OBJ2 = $(OUTDIR)list.obj 
OBJS= $(OBJ2) $(OBJ1)

EXE = $(OUTDIR)out.exe
ERASE = rm
MAKEFILE = makefile.ms


# Targets ========================================
$(EXE) : $(OBJS)
	$(CC) $(EXEFLAG)$(EXE) $(NOLGFLAG) $(OBJS)

$(OBJ1) : $(SRC1)
	$(CC) $(OBJFLAG)$(OBJ1) $(CFLAGS) $(NOLGFLAG) $(SRC1)

$(OBJ2) : $(SRC2) $(HDR2)
	$(CC) $(OBJFLAG)$(OBJ2) $(CFLAGS) $(NOLGFLAG) $(SRC2)

clean :
	-$(ERASE) $(OBJS) $(EXE)
	
rebuild :
	-$(ERASE) $(OBJS) $(EXE)
	-$(MAKE) -f $(MAKEFILE) -i