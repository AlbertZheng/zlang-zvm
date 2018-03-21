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
#LDFLAGS  = -Wl,--gc-sections $(ANTLR_LIB) -Wl,-rpath -Wl,/Gnu/gcc/cvs-20000527/lib
#LDFLAGS  = -Wl,--gc-sections $(ANTLR_LIB) -Wl,-rpath -Wl,/Tios/Language/gcc-2.95.2/lib
LDFLAGS = $(ANTLR_LIB)

cppfiles := CalcParser.cpp CalcLexer.cpp Main.cpp
objects := $(sort $(cppfiles:.cpp=.o))

%.o : %.cpp ;$(CPP) -c $< $(CXXFLAGS) -o $@

calc: $(objects) calc.g;
	$(CPP) -o $@ $(objects) $(LDFLAGS)

CalcLexer.cpp CalcLexer.hpp CalcParser.cpp CalcParser.hpp: calc.g
	$(ANTLR) $<

clean: ;
	rm -f calc *.o .depend *.rej *.orig *~ core CalcLexer.cpp CalcLexer.hpp \
			CalcParser.cpp CalcParser.hpp Calc CalcParserTokenTypes.* \
			CalcTreeWalker.cpp CalcTreeWalker.hpp

