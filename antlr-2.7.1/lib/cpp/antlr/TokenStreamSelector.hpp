#ifndef INC_TokenStreamSelector_hpp__
#define INC_TokenStreamSelector_hpp__

#include "antlr/config.hpp"
#include "antlr/TokenStream.hpp"
#include <map>
#include <stack>

ANTLR_BEGIN_NAMESPACE(antlr)

/** A token stream MUX (multiplexor) knows about n token streams
 *  and can multiplex them onto the same channel for use by token
 *  stream consumer like a parser.  This is a way to have multiple
 *  lexers break up the same input stream for a single parser.
 * Or, you can have multiple instances of the same lexer handle
 *  multiple input streams; this works great for includes.
 */
class TokenStreamSelector : public TokenStream {
protected:
	/** The set of inputs to the MUX */
#ifdef OS_NO_ALLOCATOR
	typedef ANTLR_USE_NAMESPACE(std)less<ANTLR_USE_NAMESPACE(std)string> lessp;
	typedef ANTLR_USE_NAMESPACE(std)map<ANTLR_USE_NAMESPACE(std)string,TokenStream*,lessp> inputStreamNames_coll;
#else
	typedef ANTLR_USE_NAMESPACE(std)map<ANTLR_USE_NAMESPACE(std)string,TokenStream*> inputStreamNames_coll;
#endif
	inputStreamNames_coll inputStreamNames;

	/** The currently-selected token stream input */
	TokenStream* input;

	/** Used to track stack of input streams */
#ifdef OS_NO_ALLOCATOR
	typedef ANTLR_USE_NAMESPACE(std)stack<TokenStream*, ANTLR_USE_NAMESPACE(std)deque<TokenStream*> > streamStack_coll;
#else
	typedef ANTLR_USE_NAMESPACE(std)stack<TokenStream*> streamStack_coll;
#endif
	streamStack_coll streamStack;

public:
	TokenStreamSelector();
	~TokenStreamSelector();

	void addInputStream(TokenStream* stream, const ANTLR_USE_NAMESPACE(std)string& key);

	/** Return the stream from which tokens are being pulled at
	 *  the moment.
	 */
	TokenStream* getCurrentStream() const;

	TokenStream* getStream(const ANTLR_USE_NAMESPACE(std)string& sname) const;

	RefToken nextToken();

	TokenStream* pop();

	void push(TokenStream* stream);

	void push(const ANTLR_USE_NAMESPACE(std)string& sname);

	/** Abort recognition of current Token and try again.
	 *  A stream can push a new stream (for include files
	 *  for example, and then retry(), which will cause
	 *  the current stream to abort back to this.nextToken().
	 *  this.nextToken() then asks for a token from the
	 *  current stream, which is the new "substream."
	 */
	void retry();

/** Set the stream without pushing old stream */
	void select(TokenStream* stream);

	void select(const ANTLR_USE_NAMESPACE(std)string& sname);
};

ANTLR_END_NAMESPACE

#endif //INC_TokenStreamSelector_hpp__
