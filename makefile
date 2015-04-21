#------------------------------------------------------------------------------
# Makefile for Lex 
#
#      make             makes Lex
#      make clean       removes object files
#
#------------------------------------------------------------------------------

FLAGS      = -std=c99 -Wall
SOURCES1    = List.c Lex.c
SOURCES2    = List.c ListClient.c
OBJECTS1    = List.o Lex.o
OBJECTS2    = List.o ListClient.o
HEADERS    = List.h
EXEBIN1     = Lex
EXEBIN2     = ListClient
LISTSTUFF  = Lex.c ListClient.c List.h  makefile README

all: $(EXEBIN1) $(EXEBIN2)

$(EXEBIN1) : $(OBJECTS1) $(HEADERS)
	gcc -o $(EXEBIN1) $(OBJECTS1)

$(OBJECTS1) : $(SOURCES1) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES1) 

$(EXEBIN2) : $(OBJECTS2) $(HEADERS)
	gcc -o $(EXEBIN2) $(SOURCES2)

$(OBJECTS2) : $(SOURCES2) $(HEADERS)
	gcc -c $(FLAGS) $(SOURCES2)


clean :
	rm -f $(EXEBIN1) $(OBJECTS1) $(EXEBIN2)  $(OBJECTS2)

submit :
	submit cmps101-pt.f14 pa2 $(SOURCES1) $(HEADERS) $(LISTSTUFF)

check:
	valgrind --leak-check=full $(EXEBIN) 
