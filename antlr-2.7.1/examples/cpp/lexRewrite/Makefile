CC = gcc
CPP = g++
ANTLR= java -classpath ../../.. antlr.Tool
#CC  = /Gnu/gcc/cvs-20000527/bin/gcc
#CPP = /Gnu/gcc/cvs-20000527/bin/g++

CURDIR  = $(shell pwd)

ANTLR_LIB = -L$(CURDIR)/../../../lib/cpp/src/.libs -lantlr
ANTLR_INC = -I$(CURDIR)/../../../lib/cpp

DEBUGFLAGS   := -g
#OPTFLAGS     := -felide-constructors -ffunction-sections -fdata-sections
OPTFLAGS     := -felide-constructors
STDFLAGS     := -pipe -W -Wall $(ANTLR_INC)

CXXFLAGS = $(DEBUGFLAGS) $(STDFLAGS) $(OPTFLAGS)
#LDFLAGS  = $(ANTLR_LIB) -Wl,-rpath -Wl,/Gnu/gcc/cvs-20000527/lib
#LDFLAGS  = -Wl,--gc-sections $(ANTLR_LIB) -Wl,-rpath -Wl,/Gnu/gcc/cvs-20000527/lib
LDFLAGS  = -Wl,--gc-sections $(ANTLR_LIB) -Wl,-rpath -Wl,/Tios/Language/gcc-2.95.2/lib

cppfiles := Rewrite.cpp Main.cpp
objects := $(sort $(cppfiles:.cpp=.o))

%.o : %.cpp ;$(CPP) -c $< $(CXXFLAGS) -o $@

rewrite: $(objects) rewrite.g;
	$(CPP) -o $@ $(objects) $(LDFLAGS)

Rewrite.cpp Rewrite.hpp RewriteTokenTypes.hpp RewriteTokenTypes.txt: rewrite.g
	$(ANTLR) $<

Main.o: Rewrite.o

clean: ;
	rm -f *.o .depend *.rej *.orig *~ core \
		rewrite Rewrite.cpp Rewrite.hpp RewriteTokenTypes.hpp RewriteTokenTypes.txt

