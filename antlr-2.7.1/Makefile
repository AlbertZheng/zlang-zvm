#
# [only works with gnu make]
#

ifeq ($(JAVAC),) 
    JAVAC=javac
endif

ANTLR_SRC := antlr
EXAMPLE_SRC := examples

ANTLR_SOURCES   := $(shell find $(ANTLR_SRC) -name '*.java')
EXAMPLE_SOURCES := $(shell find $(EXAMPLE_SRC) -name '*.java')

RUNTIME_CLASSES :=  antlr/DefineGrammarSymbols.class \
        antlr/ANTLRGrammarParseBehavior.class \
        antlr/MakeGrammar.class \
        antlr/ANTLRParser.class \
        antlr/ANTLRTokenTypes.class \
        antlr/LLkGrammarAnalyzer.class \
        antlr/GrammarAnalyzer.class \
        antlr/ANTLRException.class \
        antlr/CharStreamException.class \
        antlr/CharStreamIOException.class \
        antlr/FileCopyException.class \
        antlr/FileLineFormatter.class \
        antlr/MismatchedCharException.class \
        antlr/MismatchedTokenException.class \
        antlr/NoViableAltException.class \
        antlr/NoViableAltForCharException.class \
        antlr/RecognitionException.class \
        antlr/SemanticException.class \
        antlr/TokenStreamException.class \
        antlr/TokenStreamIOException.class \
        antlr/TokenStreamRecognitionException.class \
        antlr/TokenStreamRetryException.class      \
        antlr/ANTLRHashString.class \
        antlr/ANTLRStringBuffer.class \
        antlr/ASTFactory.class \
        antlr/ASTNULLType.class \
        antlr/ASTPair.class \
        antlr/BaseAST.class \
        antlr/ByteBuffer.class \
        antlr/CharBuffer.class \
        antlr/InputBuffer.class \
        antlr/CharQueue.class \
        antlr/CharScanner.class \
        antlr/CommonAST.class \
        antlr/CommonASTWithHiddenTokens.class \
        antlr/CommonToken.class \
        antlr/CommonHiddenStreamToken.class \
        antlr/LLkParser.class \
        antlr/Parser.class \
        antlr/Token.class \
        antlr/TokenBuffer.class \
        antlr/TokenQueue.class \
        antlr/TokenStream.class \
        antlr/TokenStreamHiddenTokenFilter.class \
        antlr/TokenStreamBasicFilter.class \
        antlr/TokenStreamSelector.class \
        antlr/Tool.class \
        antlr/Tool\$1.class \
        antlr/ToolErrorHandler.class \
        antlr/TreeParser.class \
        antlr/collections/AST.class \
        antlr/collections/ASTEnumeration.class \
        antlr/collections/impl/ASTArray.class \
        antlr/collections/impl/BitSet.class \
        antlr/collections/List.class \
        antlr/collections/Stack.class \
        antlr/collections/impl/LList.class \
        antlr/collections/impl/LLCell.class \
        antlr/LexerSharedInputState.class \
        antlr/ParserSharedInputState.class \
        antlr/TreeParserSharedInputState.class \
        antlr/debug/misc/*.class

DEBUG_CLASSES := $(RUNTIME_CLASSES) \
        antlr/debug/*.class


.PHONY : antlr
.PHONY : examples

antlr : .antlr_compiled

all-jars : runtime-jar tool-jar debug-jar

examples : antlr  .examples_compiled

runtime-jar : antlr
	@ echo ""
	@ echo "Building runtime jar (antlr.jar)"
	@ echo ""
	@ jar cvf antlr.jar $(RUNTIME_CLASSES)

debug-jar : antlr
	@ echo ""
	@ echo "Building debug jar (antlr.debug.jar)"
	@ echo ""
	@ jar cvf antlr.debug.jar $(DEBUG_CLASSES)


tool-jar : antlr
	@ echo ""
	@ echo "Building tool jar (antlrall.jar)"
	@ echo ""
	@ jar cvf antlrall.jar ` find $(ANTLR_SRC) -name '*.class'`

clean :
	@ echo ""
	@ echo "Removing cruft"
	@ echo ""
	@ rm -f `find . -name '*.class'`
	@ rm -f .antlr_compiled
	@ rm -f .examples_compiled

.antlr_compiled : $(ANTLR_SOURCES)
	@ echo ""
	@ echo "Compiling antlr (antlr/.../*.class)"
	@ echo ""
	@ $(JAVAC) $(ANTLR_SOURCES)
	@ touch .antlr_compiled

.examples_compiled : antlr $(EXAMPLE_SOURCES)
	@ echo ""
	@ echo "Currently unimplemented"
	@ echo ""
