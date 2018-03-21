CC = gcc
CPP = g++
ANTLR = java -classpath ../../.. antlr.Tool
#CC  = /Gnu/gcc/cvs-20000527/bin/gcc
#CPP = /Gnu/gcc/cvs-20000527/bin/g++

CURDIR  = $(shell pwd)

ANTLR_LIB = -L$(CURDIR)/../../../lib/cpp/src/.libs -lantlr
ANTLR_INC = -I$(CURDIR)/../../../lib/cpp

DEBUGFLAGS   := -g
OPTFLAGS     := -felide-constructors
#OPTFLAGS     := -felide-constructors -ffunction-sections -fdata-sections
STDFLAGS     := -pipe -W -Wall $(ANTLR_INC)

CXXFLAGS = $(DEBUGFLAGS) $(STDFLAGS) $(OPTFLAGS)
#LDFLAGS  = -Wl,--gc-sections $(ANTLR_LIB) -Wl,-rpath -Wl,/Gnu/gcc/cvs-20000527/lib
LDFLAGS  = -Wl,--gc-sections $(ANTLR_LIB) -Wl,-rpath -Wl,/Tios/Language/gcc-2.95.2/lib

cppfiles := InstrTreeWalker.cpp InstrLexer.cpp InstrParser.cpp Main.cpp

objects := $(sort $(cppfiles:.cpp=.o))

%.o : %.cpp ;$(CPP) -c $< $(CXXFLAGS) -o $@

instr: $(objects) instr.g;
	$(CPP) -o $@ $(objects) $(LDFLAGS)

InstrTreeWalker.cpp InstrTreeWalker.hpp \
InstrLexer.cpp InstrLexer.hpp \
InstrParser.cpp InstrParser.hpp: instr.g ;
	$(ANTLR) $<

clean: ;
	rm -f *.o .depend *.rej *.orig *~ core \
	InstrTreeWalker.cpp InstrTreeWalker.hpp \
	InstrLexer.cpp InstrLexer.hpp \
	InstrParser.cpp InstrParser.hpp InstrParserTokenTypes.*
