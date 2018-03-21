#
# Makefile for TinyBasic
# TJP: modified to be a bit more generic
#
ANTLR_JAVA_SPAWN_1	=	TinyBasicLexer.java		\
				TinyBasicParser.java

ANTLR_JAVA_SPAWN_2	=	TinyBasicTreeWalker.java 




default:	$(ANTLR_JAVA_SPAWN_1) $(ANTLR_JAVA_SPAWN_2)

$(ANTLR_JAVA_SPAWN_1):	TinyBasic.g
	java antlr.Tool	TinyBasic.g
#	java antlr.Tool TinyBasicTreeWalker.g


$(ANTLR_JAVA_SPAWN_2):	TinyBasicTreeWalker.g
	java antlr.Tool TinyBasicTreeWalker.g

clean:
	-rm -f	TinyBasicTokenTypes.txt			TinyBasicTokenTypes.java
	-rm -f	TinyBasicLexerTokenTypes.txt		TinyBasicLexerTokenTypes.java
	-rm -f	TinyBasicTreeWalkerTokenTypes.txt	TinyBasicTreeWalkerTokenTypes.java
	-rm -f	TinyBasicLexer.java TinyBasicParser.java TinyBasicTreeWalker.java
	-rm -f	TinyBasicTokenTypes.java TinyBasicTreeWalkerTokenTypes.java


TinyBasicParser.java:		TinyBasicLexer.java


.KEEP_STATE:

##.SUFFIXES: .java .g

##.g.java:
##	java	antlr.Tool $<

	
