/* $ANTLR 2.7.1: "zlangpass1.g" -> "ZLangLexer.cpp"$ */
#include "ZLangLexer.hpp"
#include "antlr/CharBuffer.hpp"
#include "antlr/TokenStreamException.hpp"
#include "antlr/TokenStreamIOException.hpp"
#include "antlr/TokenStreamRecognitionException.hpp"
#include "antlr/CharStreamException.hpp"
#include "antlr/CharStreamIOException.hpp"
#include "antlr/NoViableAltForCharException.hpp"

ANTLR_BEGIN_NAMESPACE(zlang)
#line 1 "zlangpass1.g"

#line 14 "ZLangLexer.cpp"
ZLangLexer::ZLangLexer(std::istream& in)
  : antlr::CharScanner(new antlr::CharBuffer(in))
{
  setCaseSensitive(true);
  initLiterals();
}

ZLangLexer::ZLangLexer(antlr::InputBuffer& ib)
  : antlr::CharScanner(ib)
{
  setCaseSensitive(true);
  initLiterals();
}

ZLangLexer::ZLangLexer(const antlr::LexerSharedInputState& state)
  : antlr::CharScanner(state)
{
  setCaseSensitive(true);
  initLiterals();
}

void ZLangLexer::initLiterals()
{
  literals["return"] = 41;
  literals["true"] = 88;
  literals["for"] = 45;
  literals["void"] = 34;
  literals["string"] = 53;
  literals["break"] = 39;
  literals["double"] = 52;
  literals["else"] = 43;
  literals["rope"] = 56;
  literals["false"] = 89;
  literals["extern"] = 24;
  literals["static"] = 35;
  literals["sdword"] = 48;
  literals["byte"] = 46;
  literals["table"] = 25;
  literals["if"] = 42;
  literals["uqword"] = 51;
  literals["sqword"] = 50;
  literals["continue"] = 40;
  literals["bool"] = 47;
  literals["while"] = 44;
  literals["udword"] = 49;
  literals["ipaddress"] = 54;
  literals["pport"] = 55;
}
bool ZLangLexer::getCaseSensitiveLiterals() const
{
  return true;
}

antlr::RefToken ZLangLexer::nextToken()
{
  antlr::RefToken theRetToken;
  for (;;) {
    antlr::RefToken theRetToken;
    int _ttype = antlr::Token::INVALID_TYPE;
    resetText();
    try {   // for char stream error handling
      try {   // for lexical error handling
        switch ( LA(1)) {
        case static_cast<unsigned char>('\t'):
        case static_cast<unsigned char>('\n'):
        case static_cast<unsigned char>('\14'):
        case static_cast<unsigned char>('\r'):
        case static_cast<unsigned char>(' '):
        {
          mWS_(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>('?'):
        {
          mQUESTION(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>('('):
        {
          mLPAREN(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>(')'):
        {
          mRPAREN(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>(']'):
        {
          mRBRACK(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>('}'):
        {
          mRCURLY(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>(','):
        {
          mCOMMA(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>('~'):
        {
          mBNOT(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>(';'):
        {
          mSEMI(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>('\''):
        {
          mCHAR_LITERAL(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>('"'):
        {
          mSTRING_LITERAL(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>('{'):
        {
          mIPv4ADDR_LITERAL(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>('A'):
        case static_cast<unsigned char>('B'):
        case static_cast<unsigned char>('C'):
        case static_cast<unsigned char>('D'):
        case static_cast<unsigned char>('E'):
        case static_cast<unsigned char>('F'):
        case static_cast<unsigned char>('G'):
        case static_cast<unsigned char>('H'):
        case static_cast<unsigned char>('I'):
        case static_cast<unsigned char>('J'):
        case static_cast<unsigned char>('K'):
        case static_cast<unsigned char>('L'):
        case static_cast<unsigned char>('M'):
        case static_cast<unsigned char>('N'):
        case static_cast<unsigned char>('O'):
        case static_cast<unsigned char>('P'):
        case static_cast<unsigned char>('Q'):
        case static_cast<unsigned char>('R'):
        case static_cast<unsigned char>('S'):
        case static_cast<unsigned char>('T'):
        case static_cast<unsigned char>('U'):
        case static_cast<unsigned char>('V'):
        case static_cast<unsigned char>('W'):
        case static_cast<unsigned char>('X'):
        case static_cast<unsigned char>('Y'):
        case static_cast<unsigned char>('Z'):
        case static_cast<unsigned char>('_'):
        case static_cast<unsigned char>('a'):
        case static_cast<unsigned char>('b'):
        case static_cast<unsigned char>('c'):
        case static_cast<unsigned char>('d'):
        case static_cast<unsigned char>('e'):
        case static_cast<unsigned char>('f'):
        case static_cast<unsigned char>('g'):
        case static_cast<unsigned char>('h'):
        case static_cast<unsigned char>('i'):
        case static_cast<unsigned char>('j'):
        case static_cast<unsigned char>('k'):
        case static_cast<unsigned char>('l'):
        case static_cast<unsigned char>('m'):
        case static_cast<unsigned char>('n'):
        case static_cast<unsigned char>('o'):
        case static_cast<unsigned char>('p'):
        case static_cast<unsigned char>('q'):
        case static_cast<unsigned char>('r'):
        case static_cast<unsigned char>('s'):
        case static_cast<unsigned char>('t'):
        case static_cast<unsigned char>('u'):
        case static_cast<unsigned char>('v'):
        case static_cast<unsigned char>('w'):
        case static_cast<unsigned char>('x'):
        case static_cast<unsigned char>('y'):
        case static_cast<unsigned char>('z'):
        {
          mIDENTIFIER(true);
          theRetToken=_returnToken;
          break;
        }
        case static_cast<unsigned char>('#'):
        {
          mCPP_LINE_CONTROL(true);
          theRetToken=_returnToken;
          break;
        }
        default:
          if ((LA(1)==static_cast<unsigned char>('/')) && (LA(2)==static_cast<unsigned char>('/'))) {
            mSL_COMMENT(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('/')) && (LA(2)==static_cast<unsigned char>('*'))) {
            mML_COMMENT(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>(':')) && (LA(2)==static_cast<unsigned char>(':'))) {
            mSCOPE(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('=')) && (LA(2)==static_cast<unsigned char>('='))) {
            mEQUAL(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('!')) && (LA(2)==static_cast<unsigned char>('='))) {
            mNOT_EQUAL(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('/')) && (LA(2)==static_cast<unsigned char>('='))) {
            mDIV_ASSIGN(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('+')) && (LA(2)==static_cast<unsigned char>('='))) {
            mPLUS_ASSIGN(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('+')) && (LA(2)==static_cast<unsigned char>('+'))) {
            mINC(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('-')) && (LA(2)==static_cast<unsigned char>('='))) {
            mMINUS_ASSIGN(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('-')) && (LA(2)==static_cast<unsigned char>('-'))) {
            mDEC(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('*')) && (LA(2)==static_cast<unsigned char>('='))) {
            mSTAR_ASSIGN(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('%')) && (LA(2)==static_cast<unsigned char>('='))) {
            mMOD_ASSIGN(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('>')) && (LA(2)==static_cast<unsigned char>('>'))) {
            mSR(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('>')) && (LA(2)==static_cast<unsigned char>('='))) {
            mGE(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('<')) && (LA(2)==static_cast<unsigned char>('<'))) {
            mSL(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('<')) && (LA(2)==static_cast<unsigned char>('='))) {
            mLE(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('^')) && (LA(2)==static_cast<unsigned char>('='))) {
            mBXOR_ASSIGN(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('|')) && (LA(2)==static_cast<unsigned char>('='))) {
            mBOR_ASSIGN(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('|')) && (LA(2)==static_cast<unsigned char>('|'))) {
            mLOR(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('&')) && (LA(2)==static_cast<unsigned char>('='))) {
            mBAND_ASSIGN(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('&')) && (LA(2)==static_cast<unsigned char>('&'))) {
            mLAND(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('[')) && (LA(2)==static_cast<unsigned char>('['))) {
            mROPE_LITERAL(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('0')) && (LA(2)==static_cast<unsigned char>('X')||LA(2)==static_cast<unsigned char>('x'))) {
            mNUM_HEX_INT(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('.')) && ((LA(2) >= static_cast<unsigned char>('0') && LA(2) <= static_cast<unsigned char>('9')))) {
            mNUM_FLOAT(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('[')) && (true)) {
            mLBRACK(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>(':')) && (true)) {
            mCOLON(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('.')) && (true)) {
            mDOT(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('=')) && (true)) {
            mASSIGN(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('!')) && (true)) {
            mLNOT(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('/')) && (true)) {
            mDIV(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('+')) && (true)) {
            mPLUS(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('-')) && (true)) {
            mMINUS(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('*')) && (true)) {
            mSTAR(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('%')) && (true)) {
            mMOD(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('>')) && (true)) {
            mGT(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('<')) && (true)) {
            mLT_(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('^')) && (true)) {
            mBXOR(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('|')) && (true)) {
            mBOR(true);
            theRetToken=_returnToken;
          }
          else if ((LA(1)==static_cast<unsigned char>('&')) && (true)) {
            mBAND(true);
            theRetToken=_returnToken;
          }
          else if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9'))) && (true)) {
            mNUM_INT(true);
            theRetToken=_returnToken;
          }
        else {
          if (LA(1)==EOF_CHAR) {uponEOF(); _returnToken = makeToken(antlr::Token::EOF_TYPE);}
				else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
        }
        }
        if ( !_returnToken ) goto tryAgain; // found SKIP token
        _ttype = _returnToken->getType();
        _returnToken->setType(_ttype);
        return _returnToken;
      }
      catch (antlr::RecognitionException& e) {
        throw antlr::TokenStreamRecognitionException(e);
      }
    }
    catch (antlr::CharStreamIOException& csie) {
       throw antlr::TokenStreamIOException(csie.io);
    }
    catch (antlr::CharStreamException& cse) {
       throw antlr::TokenStreamException(cse.getMessage());
    }
tryAgain:;
  }
}

/** whitespace -- ignored. */
void ZLangLexer::mWS_(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = WS_;
  int _saveIndex;
  
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>(' '):
  {
    match(static_cast<unsigned char>(' '));
    break;
  }
  case static_cast<unsigned char>('\t'):
  {
    match(static_cast<unsigned char>('\t'));
    break;
  }
  case static_cast<unsigned char>('\14'):
  {
    match(static_cast<unsigned char>('\14'));
    break;
  }
  case static_cast<unsigned char>('\n'):
  case static_cast<unsigned char>('\r'):
  {
    {
    if ((LA(1)==static_cast<unsigned char>('\r')) && (LA(2)==static_cast<unsigned char>('\n'))) {
      match("\r\n");
    }
    else if ((LA(1)==static_cast<unsigned char>('\r')) && (true)) {
      match(static_cast<unsigned char>('\r'));
    }
    else if ((LA(1)==static_cast<unsigned char>('\n'))) {
      match(static_cast<unsigned char>('\n'));
    }
    else {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    
    }
    if ( inputState->guessing==0 ) {
#line 788 "zlangpass1.g"
      newline();
#line 447 "ZLangLexer.cpp"
    }
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  if ( inputState->guessing==0 ) {
#line 790 "zlangpass1.g"
    _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP;
#line 460 "ZLangLexer.cpp"
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/** single-line comments. */
void ZLangLexer::mSL_COMMENT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = SL_COMMENT;
  int _saveIndex;
  
  match("//");
  {
  for (;;) {
    if ((_tokenSet_0.member(LA(1)))) {
      {
      match(_tokenSet_0);
      }
    }
    else {
      goto _loop127;
    }
    
  }
  _loop127:;
  }
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>('\n'):
  {
    match(static_cast<unsigned char>('\n'));
    break;
  }
  case static_cast<unsigned char>('\r'):
  {
    match(static_cast<unsigned char>('\r'));
    {
    if ((LA(1)==static_cast<unsigned char>('\n'))) {
      match(static_cast<unsigned char>('\n'));
    }
    else {
    }
    
    }
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  if ( inputState->guessing==0 ) {
#line 801 "zlangpass1.g"
    _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP; newline();
#line 520 "ZLangLexer.cpp"
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/** multiple-line comments. */
void ZLangLexer::mML_COMMENT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = ML_COMMENT;
  int _saveIndex;
  
  match("/*");
  {
  for (;;) {
    if (((LA(1)==static_cast<unsigned char>('*')) && ((LA(2) >= static_cast<unsigned char>('\3') && LA(2) <= static_cast<unsigned char>('\377'))))&&( LA(2) != '/' )) {
      match(static_cast<unsigned char>('*'));
    }
    else if ((LA(1)==static_cast<unsigned char>('\r')) && (LA(2)==static_cast<unsigned char>('\n'))) {
      match(static_cast<unsigned char>('\r'));
      match(static_cast<unsigned char>('\n'));
      if ( inputState->guessing==0 ) {
#line 822 "zlangpass1.g"
        newline();
#line 548 "ZLangLexer.cpp"
      }
    }
    else if ((LA(1)==static_cast<unsigned char>('\r')) && ((LA(2) >= static_cast<unsigned char>('\3') && LA(2) <= static_cast<unsigned char>('\377')))) {
      match(static_cast<unsigned char>('\r'));
      if ( inputState->guessing==0 ) {
#line 823 "zlangpass1.g"
        newline();
#line 556 "ZLangLexer.cpp"
      }
    }
    else if ((LA(1)==static_cast<unsigned char>('\n'))) {
      match(static_cast<unsigned char>('\n'));
      if ( inputState->guessing==0 ) {
#line 824 "zlangpass1.g"
        newline();
#line 564 "ZLangLexer.cpp"
      }
    }
    else if ((_tokenSet_1.member(LA(1)))) {
      {
      match(_tokenSet_1);
      }
    }
    else {
      goto _loop133;
    }
    
  }
  _loop133:;
  }
  match("*/");
  if ( inputState->guessing==0 ) {
#line 828 "zlangpass1.g"
    _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP;
#line 583 "ZLangLexer.cpp"
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/** operators. */
void ZLangLexer::mQUESTION(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = QUESTION;
  int _saveIndex;
  
  match(static_cast<unsigned char>('?'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mLPAREN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = LPAREN;
  int _saveIndex;
  
  match(static_cast<unsigned char>('('));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mRPAREN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = RPAREN;
  int _saveIndex;
  
  match(static_cast<unsigned char>(')'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mLBRACK(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = LBRACK;
  int _saveIndex;
  
  match(static_cast<unsigned char>('['));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mRBRACK(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = RBRACK;
  int _saveIndex;
  
  match(static_cast<unsigned char>(']'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mRCURLY(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = RCURLY;
  int _saveIndex;
  
  match(static_cast<unsigned char>('}'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mCOLON(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = COLON;
  int _saveIndex;
  
  match(static_cast<unsigned char>(':'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mSCOPE(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = SCOPE;
  int _saveIndex;
  
  match("::");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mCOMMA(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = COMMA;
  int _saveIndex;
  
  match(static_cast<unsigned char>(','));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mDOT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = DOT;
  int _saveIndex;
  
  match(static_cast<unsigned char>('.'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mASSIGN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = ASSIGN;
  int _saveIndex;
  
  match(static_cast<unsigned char>('='));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mEQUAL(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = EQUAL;
  int _saveIndex;
  
  match("==");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mLNOT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = LNOT;
  int _saveIndex;
  
  match(static_cast<unsigned char>('!'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mBNOT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = BNOT;
  int _saveIndex;
  
  match(static_cast<unsigned char>('~'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mNOT_EQUAL(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = NOT_EQUAL;
  int _saveIndex;
  
  match("!=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mDIV(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = DIV;
  int _saveIndex;
  
  match(static_cast<unsigned char>('/'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mDIV_ASSIGN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = DIV_ASSIGN;
  int _saveIndex;
  
  match("/=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mPLUS(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = PLUS;
  int _saveIndex;
  
  match(static_cast<unsigned char>('+'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mPLUS_ASSIGN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = PLUS_ASSIGN;
  int _saveIndex;
  
  match("+=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mINC(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = INC;
  int _saveIndex;
  
  match("++");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mMINUS(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = MINUS;
  int _saveIndex;
  
  match(static_cast<unsigned char>('-'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mMINUS_ASSIGN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = MINUS_ASSIGN;
  int _saveIndex;
  
  match("-=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mDEC(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = DEC;
  int _saveIndex;
  
  match("--");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mSTAR(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = STAR;
  int _saveIndex;
  
  match(static_cast<unsigned char>('*'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mSTAR_ASSIGN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = STAR_ASSIGN;
  int _saveIndex;
  
  match("*=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mMOD(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = MOD;
  int _saveIndex;
  
  match(static_cast<unsigned char>('%'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mMOD_ASSIGN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = MOD_ASSIGN;
  int _saveIndex;
  
  match("%=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mSR(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = SR;
  int _saveIndex;
  
  match(">>");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mGE(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = GE;
  int _saveIndex;
  
  match(">=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mGT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = GT;
  int _saveIndex;
  
  match(">");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mSL(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = SL;
  int _saveIndex;
  
  match("<<");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mLE(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = LE;
  int _saveIndex;
  
  match("<=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mLT_(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = LT_;
  int _saveIndex;
  
  match(static_cast<unsigned char>('<'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mBXOR(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = BXOR;
  int _saveIndex;
  
  match(static_cast<unsigned char>('^'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mBXOR_ASSIGN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = BXOR_ASSIGN;
  int _saveIndex;
  
  match("^=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mBOR(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = BOR;
  int _saveIndex;
  
  match(static_cast<unsigned char>('|'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mBOR_ASSIGN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = BOR_ASSIGN;
  int _saveIndex;
  
  match("|=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mLOR(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = LOR;
  int _saveIndex;
  
  match("||");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mBAND(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = BAND;
  int _saveIndex;
  
  match(static_cast<unsigned char>('&'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mBAND_ASSIGN(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = BAND_ASSIGN;
  int _saveIndex;
  
  match("&=");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mLAND(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = LAND;
  int _saveIndex;
  
  match("&&");
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mSEMI(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = SEMI;
  int _saveIndex;
  
  match(static_cast<unsigned char>(';'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mCHAR_LITERAL(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = CHAR_LITERAL;
  int _saveIndex;
  
  _saveIndex=text.length();
  match(static_cast<unsigned char>('\''));
  text.erase(_saveIndex);
  {
  if ((LA(1)==static_cast<unsigned char>('\\'))) {
    mESCAPE(false);
  }
  else if ((_tokenSet_2.member(LA(1)))) {
    matchNot(static_cast<unsigned char>('\''));
  }
  else {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  
  }
  _saveIndex=text.length();
  match(static_cast<unsigned char>('\''));
  text.erase(_saveIndex);
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mESCAPE(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = ESCAPE;
  int _saveIndex;
  
  match(static_cast<unsigned char>('\\'));
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>('n'):
  {
    match(static_cast<unsigned char>('n'));
    if ( inputState->guessing==0 ) {
#line 952 "zlangpass1.g"
      text.erase(_begin); text += '\n';
#line 1227 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('r'):
  {
    match(static_cast<unsigned char>('r'));
    if ( inputState->guessing==0 ) {
#line 953 "zlangpass1.g"
      text.erase(_begin); text += '\r';
#line 1237 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('t'):
  {
    match(static_cast<unsigned char>('t'));
    if ( inputState->guessing==0 ) {
#line 954 "zlangpass1.g"
      text.erase(_begin); text += '\t';
#line 1247 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('b'):
  {
    match(static_cast<unsigned char>('b'));
    if ( inputState->guessing==0 ) {
#line 955 "zlangpass1.g"
      text.erase(_begin); text += '\b';
#line 1257 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('f'):
  {
    match(static_cast<unsigned char>('f'));
    if ( inputState->guessing==0 ) {
#line 956 "zlangpass1.g"
      text.erase(_begin); text += '\f';
#line 1267 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('"'):
  {
    match(static_cast<unsigned char>('"'));
    if ( inputState->guessing==0 ) {
#line 957 "zlangpass1.g"
      text.erase(_begin); text += '"';
#line 1277 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('\''):
  {
    match(static_cast<unsigned char>('\''));
    if ( inputState->guessing==0 ) {
#line 958 "zlangpass1.g"
      text.erase(_begin); text += '\'';
#line 1287 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('\\'):
  {
    match(static_cast<unsigned char>('\\'));
    if ( inputState->guessing==0 ) {
#line 959 "zlangpass1.g"
      text.erase(_begin); text += '\\';
#line 1297 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('0'):
  {
    match(static_cast<unsigned char>('0'));
    if ( inputState->guessing==0 ) {
#line 960 "zlangpass1.g"
      text.erase(_begin); text += '\0';
#line 1307 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('['):
  {
    match(static_cast<unsigned char>('['));
    if ( inputState->guessing==0 ) {
#line 961 "zlangpass1.g"
      text.erase(_begin); text += '[';
#line 1317 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>(']'):
  {
    match(static_cast<unsigned char>(']'));
    if ( inputState->guessing==0 ) {
#line 962 "zlangpass1.g"
      text.erase(_begin); text += ']';
#line 1327 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('x'):
  {
    match(static_cast<unsigned char>('x'));
    mHEX_DIGIT(false);
    {
    if ((_tokenSet_3.member(LA(1))) && ((LA(2) >= static_cast<unsigned char>('\3') && LA(2) <= static_cast<unsigned char>('\377')))) {
      mHEX_DIGIT(false);
      if ( inputState->guessing==0 ) {
#line 977 "zlangpass1.g"
        
        //std::string stringText = $getText();
        // ANTLR have a bug when translating '$getText()'
        // -> std::string stringText = text.substr(_begin,text.length()-_begin)();
        std::string stringText = text.substr(_begin,text.length()-_begin);
        // skipping '\x'
        stringText = stringText.substr(2);
        u_char uch = (u_char)strtol(stringText.c_str(), (char **)0, 16);
        text.erase(_begin); text += std::string(1, uch);
        
#line 1350 "ZLangLexer.cpp"
      }
    }
    else if (((LA(1) >= static_cast<unsigned char>('\3') && LA(1) <= static_cast<unsigned char>('\377'))) && (true)) {
    }
    else {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    
    }
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/** string literals. */
void ZLangLexer::mSTRING_LITERAL(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = STRING_LITERAL;
  int _saveIndex;
  
  _saveIndex=text.length();
  match(static_cast<unsigned char>('"'));
  text.erase(_saveIndex);
  {
  for (;;) {
    if ((LA(1)==static_cast<unsigned char>('\\'))) {
      mESCAPE(false);
    }
    else if ((_tokenSet_4.member(LA(1)))) {
      {
      match(_tokenSet_4);
      }
    }
    else {
      goto _loop181;
    }
    
  }
  _loop181:;
  }
  _saveIndex=text.length();
  match(static_cast<unsigned char>('"'));
  text.erase(_saveIndex);
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/** rope-string literals. */
void ZLangLexer::mROPE_LITERAL(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = ROPE_LITERAL;
  int _saveIndex;
  
  _saveIndex=text.length();
  match("[[");
  text.erase(_saveIndex);
  {
  for (;;) {
    if ((LA(1)==static_cast<unsigned char>('\\'))) {
      mESCAPE(false);
    }
    else if ((_tokenSet_5.member(LA(1)))) {
      {
      match(_tokenSet_5);
      }
    }
    else {
      goto _loop185;
    }
    
  }
  _loop185:;
  }
  _saveIndex=text.length();
  match("]]");
  text.erase(_saveIndex);
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mIPv4ADDR_LITERAL(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = IPv4ADDR_LITERAL;
  int _saveIndex;
  
  bool synPredMatched192 = false;
  if (((LA(1)==static_cast<unsigned char>('{')) && (_tokenSet_6.member(LA(2))))) {
    int _m192 = mark();
    synPredMatched192 = true;
    inputState->guessing++;
    try {
      {
      match(static_cast<unsigned char>('{'));
      {
      switch ( LA(1)) {
      case static_cast<unsigned char>('0'):
      case static_cast<unsigned char>('1'):
      case static_cast<unsigned char>('2'):
      case static_cast<unsigned char>('3'):
      case static_cast<unsigned char>('4'):
      case static_cast<unsigned char>('5'):
      case static_cast<unsigned char>('6'):
      case static_cast<unsigned char>('7'):
      case static_cast<unsigned char>('8'):
      case static_cast<unsigned char>('9'):
      {
        {
        mPURE_INT(false);
        {
        switch ( LA(1)) {
        case static_cast<unsigned char>('.'):
        {
          match(static_cast<unsigned char>('.'));
          mPURE_INT(false);
          match(static_cast<unsigned char>('.'));
          break;
        }
        case static_cast<unsigned char>('/'):
        {
          mDIV(false);
          mIP_PROTOCOL(false);
          break;
        }
        default:
        {
          throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
        }
        }
        }
        }
        break;
      }
      case static_cast<unsigned char>('A'):
      case static_cast<unsigned char>('B'):
      case static_cast<unsigned char>('C'):
      case static_cast<unsigned char>('D'):
      case static_cast<unsigned char>('E'):
      case static_cast<unsigned char>('F'):
      case static_cast<unsigned char>('G'):
      case static_cast<unsigned char>('H'):
      case static_cast<unsigned char>('I'):
      case static_cast<unsigned char>('J'):
      case static_cast<unsigned char>('K'):
      case static_cast<unsigned char>('L'):
      case static_cast<unsigned char>('M'):
      case static_cast<unsigned char>('N'):
      case static_cast<unsigned char>('O'):
      case static_cast<unsigned char>('P'):
      case static_cast<unsigned char>('Q'):
      case static_cast<unsigned char>('R'):
      case static_cast<unsigned char>('S'):
      case static_cast<unsigned char>('T'):
      case static_cast<unsigned char>('U'):
      case static_cast<unsigned char>('V'):
      case static_cast<unsigned char>('W'):
      case static_cast<unsigned char>('X'):
      case static_cast<unsigned char>('Y'):
      case static_cast<unsigned char>('Z'):
      case static_cast<unsigned char>('_'):
      case static_cast<unsigned char>('a'):
      case static_cast<unsigned char>('b'):
      case static_cast<unsigned char>('c'):
      case static_cast<unsigned char>('d'):
      case static_cast<unsigned char>('e'):
      case static_cast<unsigned char>('f'):
      case static_cast<unsigned char>('g'):
      case static_cast<unsigned char>('h'):
      case static_cast<unsigned char>('i'):
      case static_cast<unsigned char>('j'):
      case static_cast<unsigned char>('k'):
      case static_cast<unsigned char>('l'):
      case static_cast<unsigned char>('m'):
      case static_cast<unsigned char>('n'):
      case static_cast<unsigned char>('o'):
      case static_cast<unsigned char>('p'):
      case static_cast<unsigned char>('q'):
      case static_cast<unsigned char>('r'):
      case static_cast<unsigned char>('s'):
      case static_cast<unsigned char>('t'):
      case static_cast<unsigned char>('u'):
      case static_cast<unsigned char>('v'):
      case static_cast<unsigned char>('w'):
      case static_cast<unsigned char>('x'):
      case static_cast<unsigned char>('y'):
      case static_cast<unsigned char>('z'):
      {
        mIDENTIFIER(false);
        {
        if ((LA(1)==static_cast<unsigned char>('.'))) {
          match(static_cast<unsigned char>('.'));
          mIDENTIFIER(false);
        }
        else {
        }
        
        }
        break;
      }
      default:
      {
        throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
      }
      }
      }
      }
    }
    catch (antlr::RecognitionException& pe) {
      synPredMatched192 = false;
    }
    rewind(_m192);
    inputState->guessing--;
  }
  if ( synPredMatched192 ) {
    {
    _saveIndex=text.length();
    match(static_cast<unsigned char>('{'));
    text.erase(_saveIndex);
    {
    switch ( LA(1)) {
    case static_cast<unsigned char>('0'):
    case static_cast<unsigned char>('1'):
    case static_cast<unsigned char>('2'):
    case static_cast<unsigned char>('3'):
    case static_cast<unsigned char>('4'):
    case static_cast<unsigned char>('5'):
    case static_cast<unsigned char>('6'):
    case static_cast<unsigned char>('7'):
    case static_cast<unsigned char>('8'):
    case static_cast<unsigned char>('9'):
    {
      mPURE_INT(false);
      {
      switch ( LA(1)) {
      case static_cast<unsigned char>('.'):
      {
        match(static_cast<unsigned char>('.'));
        mPURE_INT(false);
        match(static_cast<unsigned char>('.'));
        mPURE_INT(false);
        match(static_cast<unsigned char>('.'));
        mPURE_INT(false);
        {
        switch ( LA(1)) {
        case static_cast<unsigned char>('/'):
        {
          mDIV(false);
          mPURE_INT(false);
          break;
        }
        case static_cast<unsigned char>('}'):
        {
          break;
        }
        default:
        {
          throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
        }
        }
        }
        break;
      }
      case static_cast<unsigned char>('/'):
      {
        mDIV(false);
        mIP_PROTOCOL(false);
        if ( inputState->guessing==0 ) {
#line 929 "zlangpass1.g"
          _ttype = PPORT_LITERAL;
#line 1638 "ZLangLexer.cpp"
        }
        break;
      }
      default:
      {
        throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
      }
      }
      }
      break;
    }
    case static_cast<unsigned char>('A'):
    case static_cast<unsigned char>('B'):
    case static_cast<unsigned char>('C'):
    case static_cast<unsigned char>('D'):
    case static_cast<unsigned char>('E'):
    case static_cast<unsigned char>('F'):
    case static_cast<unsigned char>('G'):
    case static_cast<unsigned char>('H'):
    case static_cast<unsigned char>('I'):
    case static_cast<unsigned char>('J'):
    case static_cast<unsigned char>('K'):
    case static_cast<unsigned char>('L'):
    case static_cast<unsigned char>('M'):
    case static_cast<unsigned char>('N'):
    case static_cast<unsigned char>('O'):
    case static_cast<unsigned char>('P'):
    case static_cast<unsigned char>('Q'):
    case static_cast<unsigned char>('R'):
    case static_cast<unsigned char>('S'):
    case static_cast<unsigned char>('T'):
    case static_cast<unsigned char>('U'):
    case static_cast<unsigned char>('V'):
    case static_cast<unsigned char>('W'):
    case static_cast<unsigned char>('X'):
    case static_cast<unsigned char>('Y'):
    case static_cast<unsigned char>('Z'):
    case static_cast<unsigned char>('_'):
    case static_cast<unsigned char>('a'):
    case static_cast<unsigned char>('b'):
    case static_cast<unsigned char>('c'):
    case static_cast<unsigned char>('d'):
    case static_cast<unsigned char>('e'):
    case static_cast<unsigned char>('f'):
    case static_cast<unsigned char>('g'):
    case static_cast<unsigned char>('h'):
    case static_cast<unsigned char>('i'):
    case static_cast<unsigned char>('j'):
    case static_cast<unsigned char>('k'):
    case static_cast<unsigned char>('l'):
    case static_cast<unsigned char>('m'):
    case static_cast<unsigned char>('n'):
    case static_cast<unsigned char>('o'):
    case static_cast<unsigned char>('p'):
    case static_cast<unsigned char>('q'):
    case static_cast<unsigned char>('r'):
    case static_cast<unsigned char>('s'):
    case static_cast<unsigned char>('t'):
    case static_cast<unsigned char>('u'):
    case static_cast<unsigned char>('v'):
    case static_cast<unsigned char>('w'):
    case static_cast<unsigned char>('x'):
    case static_cast<unsigned char>('y'):
    case static_cast<unsigned char>('z'):
    {
      mIDENTIFIER(false);
      {
      for (;;) {
        if ((LA(1)==static_cast<unsigned char>('.'))) {
          match(static_cast<unsigned char>('.'));
          mIDENTIFIER(false);
        }
        else {
          goto _loop198;
        }
        
      }
      _loop198:;
      }
      {
      switch ( LA(1)) {
      case static_cast<unsigned char>('/'):
      {
        mDIV(false);
        mPURE_INT(false);
        break;
      }
      case static_cast<unsigned char>('}'):
      {
        break;
      }
      default:
      {
        throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
      }
      }
      }
      break;
    }
    default:
    {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    }
    }
    _saveIndex = text.length();
    mRCURLY(false);
    text.erase(_saveIndex);
    }
  }
  else if ((LA(1)==static_cast<unsigned char>('{')) && (true)) {
    match(static_cast<unsigned char>('{'));
    if ( inputState->guessing==0 ) {
#line 935 "zlangpass1.g"
      _ttype = LCURLY;
#line 1754 "ZLangLexer.cpp"
    }
  }
  else {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mPURE_INT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = PURE_INT;
  int _saveIndex;
  
  {
  int _cnt219=0;
  for (;;) {
    if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
      mDIGIT(false);
    }
    else {
      if ( _cnt219>=1 ) { goto _loop219; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
    }
    
    _cnt219++;
  }
  _loop219:;
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mIP_PROTOCOL(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = IP_PROTOCOL;
  int _saveIndex;
  
  switch ( LA(1)) {
  case static_cast<unsigned char>('T'):
  case static_cast<unsigned char>('t'):
  {
    {
    {
    switch ( LA(1)) {
    case static_cast<unsigned char>('T'):
    {
      match(static_cast<unsigned char>('T'));
      break;
    }
    case static_cast<unsigned char>('t'):
    {
      match(static_cast<unsigned char>('t'));
      break;
    }
    default:
    {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    }
    }
    {
    switch ( LA(1)) {
    case static_cast<unsigned char>('C'):
    {
      match(static_cast<unsigned char>('C'));
      break;
    }
    case static_cast<unsigned char>('c'):
    {
      match(static_cast<unsigned char>('c'));
      break;
    }
    default:
    {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    }
    }
    {
    switch ( LA(1)) {
    case static_cast<unsigned char>('P'):
    {
      match(static_cast<unsigned char>('P'));
      break;
    }
    case static_cast<unsigned char>('p'):
    {
      match(static_cast<unsigned char>('p'));
      break;
    }
    default:
    {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    }
    }
    }
    break;
  }
  case static_cast<unsigned char>('U'):
  case static_cast<unsigned char>('u'):
  {
    {
    {
    switch ( LA(1)) {
    case static_cast<unsigned char>('U'):
    {
      match(static_cast<unsigned char>('U'));
      break;
    }
    case static_cast<unsigned char>('u'):
    {
      match(static_cast<unsigned char>('u'));
      break;
    }
    default:
    {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    }
    }
    {
    switch ( LA(1)) {
    case static_cast<unsigned char>('D'):
    {
      match(static_cast<unsigned char>('D'));
      break;
    }
    case static_cast<unsigned char>('d'):
    {
      match(static_cast<unsigned char>('d'));
      break;
    }
    default:
    {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    }
    }
    {
    switch ( LA(1)) {
    case static_cast<unsigned char>('P'):
    {
      match(static_cast<unsigned char>('P'));
      break;
    }
    case static_cast<unsigned char>('p'):
    {
      match(static_cast<unsigned char>('p'));
      break;
    }
    default:
    {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    }
    }
    }
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mIDENTIFIER(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = IDENTIFIER;
  int _saveIndex;
  
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>('a'):
  case static_cast<unsigned char>('b'):
  case static_cast<unsigned char>('c'):
  case static_cast<unsigned char>('d'):
  case static_cast<unsigned char>('e'):
  case static_cast<unsigned char>('f'):
  case static_cast<unsigned char>('g'):
  case static_cast<unsigned char>('h'):
  case static_cast<unsigned char>('i'):
  case static_cast<unsigned char>('j'):
  case static_cast<unsigned char>('k'):
  case static_cast<unsigned char>('l'):
  case static_cast<unsigned char>('m'):
  case static_cast<unsigned char>('n'):
  case static_cast<unsigned char>('o'):
  case static_cast<unsigned char>('p'):
  case static_cast<unsigned char>('q'):
  case static_cast<unsigned char>('r'):
  case static_cast<unsigned char>('s'):
  case static_cast<unsigned char>('t'):
  case static_cast<unsigned char>('u'):
  case static_cast<unsigned char>('v'):
  case static_cast<unsigned char>('w'):
  case static_cast<unsigned char>('x'):
  case static_cast<unsigned char>('y'):
  case static_cast<unsigned char>('z'):
  {
    matchRange(static_cast<unsigned char>('a'),static_cast<unsigned char>('z'));
    break;
  }
  case static_cast<unsigned char>('A'):
  case static_cast<unsigned char>('B'):
  case static_cast<unsigned char>('C'):
  case static_cast<unsigned char>('D'):
  case static_cast<unsigned char>('E'):
  case static_cast<unsigned char>('F'):
  case static_cast<unsigned char>('G'):
  case static_cast<unsigned char>('H'):
  case static_cast<unsigned char>('I'):
  case static_cast<unsigned char>('J'):
  case static_cast<unsigned char>('K'):
  case static_cast<unsigned char>('L'):
  case static_cast<unsigned char>('M'):
  case static_cast<unsigned char>('N'):
  case static_cast<unsigned char>('O'):
  case static_cast<unsigned char>('P'):
  case static_cast<unsigned char>('Q'):
  case static_cast<unsigned char>('R'):
  case static_cast<unsigned char>('S'):
  case static_cast<unsigned char>('T'):
  case static_cast<unsigned char>('U'):
  case static_cast<unsigned char>('V'):
  case static_cast<unsigned char>('W'):
  case static_cast<unsigned char>('X'):
  case static_cast<unsigned char>('Y'):
  case static_cast<unsigned char>('Z'):
  {
    matchRange(static_cast<unsigned char>('A'),static_cast<unsigned char>('Z'));
    break;
  }
  case static_cast<unsigned char>('_'):
  {
    match(static_cast<unsigned char>('_'));
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  {
  for (;;) {
    switch ( LA(1)) {
    case static_cast<unsigned char>('a'):
    case static_cast<unsigned char>('b'):
    case static_cast<unsigned char>('c'):
    case static_cast<unsigned char>('d'):
    case static_cast<unsigned char>('e'):
    case static_cast<unsigned char>('f'):
    case static_cast<unsigned char>('g'):
    case static_cast<unsigned char>('h'):
    case static_cast<unsigned char>('i'):
    case static_cast<unsigned char>('j'):
    case static_cast<unsigned char>('k'):
    case static_cast<unsigned char>('l'):
    case static_cast<unsigned char>('m'):
    case static_cast<unsigned char>('n'):
    case static_cast<unsigned char>('o'):
    case static_cast<unsigned char>('p'):
    case static_cast<unsigned char>('q'):
    case static_cast<unsigned char>('r'):
    case static_cast<unsigned char>('s'):
    case static_cast<unsigned char>('t'):
    case static_cast<unsigned char>('u'):
    case static_cast<unsigned char>('v'):
    case static_cast<unsigned char>('w'):
    case static_cast<unsigned char>('x'):
    case static_cast<unsigned char>('y'):
    case static_cast<unsigned char>('z'):
    {
      matchRange(static_cast<unsigned char>('a'),static_cast<unsigned char>('z'));
      break;
    }
    case static_cast<unsigned char>('A'):
    case static_cast<unsigned char>('B'):
    case static_cast<unsigned char>('C'):
    case static_cast<unsigned char>('D'):
    case static_cast<unsigned char>('E'):
    case static_cast<unsigned char>('F'):
    case static_cast<unsigned char>('G'):
    case static_cast<unsigned char>('H'):
    case static_cast<unsigned char>('I'):
    case static_cast<unsigned char>('J'):
    case static_cast<unsigned char>('K'):
    case static_cast<unsigned char>('L'):
    case static_cast<unsigned char>('M'):
    case static_cast<unsigned char>('N'):
    case static_cast<unsigned char>('O'):
    case static_cast<unsigned char>('P'):
    case static_cast<unsigned char>('Q'):
    case static_cast<unsigned char>('R'):
    case static_cast<unsigned char>('S'):
    case static_cast<unsigned char>('T'):
    case static_cast<unsigned char>('U'):
    case static_cast<unsigned char>('V'):
    case static_cast<unsigned char>('W'):
    case static_cast<unsigned char>('X'):
    case static_cast<unsigned char>('Y'):
    case static_cast<unsigned char>('Z'):
    {
      matchRange(static_cast<unsigned char>('A'),static_cast<unsigned char>('Z'));
      break;
    }
    case static_cast<unsigned char>('_'):
    {
      match(static_cast<unsigned char>('_'));
      break;
    }
    case static_cast<unsigned char>('0'):
    case static_cast<unsigned char>('1'):
    case static_cast<unsigned char>('2'):
    case static_cast<unsigned char>('3'):
    case static_cast<unsigned char>('4'):
    case static_cast<unsigned char>('5'):
    case static_cast<unsigned char>('6'):
    case static_cast<unsigned char>('7'):
    case static_cast<unsigned char>('8'):
    case static_cast<unsigned char>('9'):
    {
      mDIGIT(false);
      break;
    }
    default:
    {
      goto _loop215;
    }
    }
  }
  _loop215:;
  }
  _ttype = testLiteralsTable(_ttype);
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mHEX_DIGIT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = HEX_DIGIT;
  int _saveIndex;
  
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>('0'):
  case static_cast<unsigned char>('1'):
  case static_cast<unsigned char>('2'):
  case static_cast<unsigned char>('3'):
  case static_cast<unsigned char>('4'):
  case static_cast<unsigned char>('5'):
  case static_cast<unsigned char>('6'):
  case static_cast<unsigned char>('7'):
  case static_cast<unsigned char>('8'):
  case static_cast<unsigned char>('9'):
  {
    mDIGIT(false);
    break;
  }
  case static_cast<unsigned char>('A'):
  case static_cast<unsigned char>('B'):
  case static_cast<unsigned char>('C'):
  case static_cast<unsigned char>('D'):
  case static_cast<unsigned char>('E'):
  case static_cast<unsigned char>('F'):
  {
    matchRange(static_cast<unsigned char>('A'),static_cast<unsigned char>('F'));
    break;
  }
  case static_cast<unsigned char>('a'):
  case static_cast<unsigned char>('b'):
  case static_cast<unsigned char>('c'):
  case static_cast<unsigned char>('d'):
  case static_cast<unsigned char>('e'):
  case static_cast<unsigned char>('f'):
  {
    matchRange(static_cast<unsigned char>('a'),static_cast<unsigned char>('f'));
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mDIGIT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = DIGIT;
  int _saveIndex;
  
  matchRange(static_cast<unsigned char>('0'),static_cast<unsigned char>('9'));
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/** a hexadecimal numeric literal. */
void ZLangLexer::mNUM_HEX_INT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = NUM_HEX_INT;
  int _saveIndex;
  
  {
  if ((LA(1)==static_cast<unsigned char>('0')) && (LA(2)==static_cast<unsigned char>('x'))) {
    match("0x");
  }
  else if ((LA(1)==static_cast<unsigned char>('0')) && (LA(2)==static_cast<unsigned char>('X'))) {
    match("0X");
  }
  else {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  
  }
  {
  int _cnt225=0;
  for (;;) {
    if ((_tokenSet_3.member(LA(1)))) {
      mHEX_DIGIT(false);
    }
    else {
      if ( _cnt225>=1 ) { goto _loop225; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
    }
    
    _cnt225++;
  }
  _loop225:;
  }
  {
  if ((LA(1)==static_cast<unsigned char>('L')||LA(1)==static_cast<unsigned char>('l'))) {
    {
    switch ( LA(1)) {
    case static_cast<unsigned char>('L'):
    {
      match(static_cast<unsigned char>('L'));
      break;
    }
    case static_cast<unsigned char>('l'):
    {
      match(static_cast<unsigned char>('l'));
      break;
    }
    default:
    {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    }
    }
    if ( inputState->guessing==0 ) {
#line 1029 "zlangpass1.g"
      _ttype = NUM_HEX_QUAD;
#line 2238 "ZLangLexer.cpp"
    }
  }
  else {
  }
  
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/** a numeric literal. */
void ZLangLexer::mNUM_INT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = NUM_INT;
  int _saveIndex;
  
  {
  int _cnt230=0;
  for (;;) {
    if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
      mDIGIT(false);
    }
    else {
      if ( _cnt230>=1 ) { goto _loop230; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
    }
    
    _cnt230++;
  }
  _loop230:;
  }
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>('.'):
  {
    match(static_cast<unsigned char>('.'));
    {
    for (;;) {
      if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
        mDIGIT(false);
      }
      else {
        goto _loop233;
      }
      
    }
    _loop233:;
    }
    if ( inputState->guessing==0 ) {
#line 1038 "zlangpass1.g"
      _ttype = NUM_FLOAT;
#line 2293 "ZLangLexer.cpp"
    }
    {
    if ((LA(1)==static_cast<unsigned char>('E')||LA(1)==static_cast<unsigned char>('e'))) {
      mEXPONENT(false);
    }
    else {
    }
    
    }
    break;
  }
  case static_cast<unsigned char>('E'):
  case static_cast<unsigned char>('e'):
  {
    mEXPONENT(false);
    if ( inputState->guessing==0 ) {
#line 1039 "zlangpass1.g"
      _ttype = NUM_FLOAT;
#line 2312 "ZLangLexer.cpp"
    }
    break;
  }
  case static_cast<unsigned char>('L'):
  case static_cast<unsigned char>('l'):
  {
    {
    switch ( LA(1)) {
    case static_cast<unsigned char>('L'):
    {
      match(static_cast<unsigned char>('L'));
      break;
    }
    case static_cast<unsigned char>('l'):
    {
      match(static_cast<unsigned char>('l'));
      break;
    }
    default:
    {
      throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
    }
    }
    }
    if ( inputState->guessing==0 ) {
#line 1040 "zlangpass1.g"
      _ttype = NUM_QUAD;
#line 2340 "ZLangLexer.cpp"
    }
    break;
  }
  default:
    {
    }
  }
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/** a couple protected methods to assist in matching floating point numbers. */
void ZLangLexer::mEXPONENT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = EXPONENT;
  int _saveIndex;
  
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>('e'):
  {
    match(static_cast<unsigned char>('e'));
    break;
  }
  case static_cast<unsigned char>('E'):
  {
    match(static_cast<unsigned char>('E'));
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>('+'):
  {
    match(static_cast<unsigned char>('+'));
    break;
  }
  case static_cast<unsigned char>('-'):
  {
    match(static_cast<unsigned char>('-'));
    break;
  }
  case static_cast<unsigned char>('0'):
  case static_cast<unsigned char>('1'):
  case static_cast<unsigned char>('2'):
  case static_cast<unsigned char>('3'):
  case static_cast<unsigned char>('4'):
  case static_cast<unsigned char>('5'):
  case static_cast<unsigned char>('6'):
  case static_cast<unsigned char>('7'):
  case static_cast<unsigned char>('8'):
  case static_cast<unsigned char>('9'):
  {
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  {
  int _cnt244=0;
  for (;;) {
    if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
      mDIGIT(false);
    }
    else {
      if ( _cnt244>=1 ) { goto _loop244; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
    }
    
    _cnt244++;
  }
  _loop244:;
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/** a float literal. */
void ZLangLexer::mNUM_FLOAT(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = NUM_FLOAT;
  int _saveIndex;
  
  match(static_cast<unsigned char>('.'));
  {
  int _cnt238=0;
  for (;;) {
    if (((LA(1) >= static_cast<unsigned char>('0') && LA(1) <= static_cast<unsigned char>('9')))) {
      mDIGIT(false);
    }
    else {
      if ( _cnt238>=1 ) { goto _loop238; } else {throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());}
    }
    
    _cnt238++;
  }
  _loop238:;
  }
  {
  if ((LA(1)==static_cast<unsigned char>('E')||LA(1)==static_cast<unsigned char>('e'))) {
    mEXPONENT(false);
  }
  else {
  }
  
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

/**
 * Deal with 'gnu cpp' line control.
 * @note 'gnu cpp' line control have the format :
 * <pre>
 *   # number "/usr/include/stdio.h" number [number]
 * </pre>
 */
void ZLangLexer::mCPP_LINE_CONTROL(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = CPP_LINE_CONTROL;
  int _saveIndex;
  antlr::RefToken tLineNumber;
  antlr::RefToken tIncludeFile;
  
  match(static_cast<unsigned char>('#'));
  if ( inputState->guessing==0 ) {
#line 1070 "zlangpass1.g"
    
    int nColumnNumber = getColumn();  // Must be '2', then it means '#' is at line-head.
    //std::cout << "start column: " << nColumnNumber << std::endl;
    
#line 2492 "ZLangLexer.cpp"
  }
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>(' '):
  {
    match(static_cast<unsigned char>(' '));
    break;
  }
  case static_cast<unsigned char>('\t'):
  {
    match(static_cast<unsigned char>('\t'));
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  mPURE_INT(true);
  tLineNumber=_returnToken;
  if ( inputState->guessing==0 ) {
#line 1076 "zlangpass1.g"
    
    int nLineNumber = strtol(tLineNumber->getText().c_str(), (char **)0, 10);
    //std::cout << "cpp line: " << nLineNumber << std::endl;
    setLine(nLineNumber);
    
#line 2521 "ZLangLexer.cpp"
  }
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>(' '):
  {
    match(static_cast<unsigned char>(' '));
    break;
  }
  case static_cast<unsigned char>('\t'):
  {
    match(static_cast<unsigned char>('\t'));
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  match(static_cast<unsigned char>('"'));
  mCPP_LINE_CONTROL_INCLUDE_FILE(true);
  tIncludeFile=_returnToken;
  if ( inputState->guessing==0 ) {
#line 1083 "zlangpass1.g"
    
    //std::cout << "'cpp' include file: " << tIncludeFile->getText() << std::endl;
    std::string stringSwitchToFile = tIncludeFile->getText();
    if (stringSwitchToFile.size() == 0 || stringSwitchToFile == "<stdin>")
    // now return to 'compiled source file'
    {
    setFilename(_stringCompiledSourceFileName);
    }
    else
    // now switch to '#include file'
    {
    setFilename(stringSwitchToFile);
    }
    
#line 2560 "ZLangLexer.cpp"
  }
  match(static_cast<unsigned char>('"'));
  {
  for (;;) {
    if ((_tokenSet_0.member(LA(1)))) {
      {
      match(_tokenSet_0);
      }
    }
    else {
      goto _loop250;
    }
    
  }
  _loop250:;
  }
  {
  switch ( LA(1)) {
  case static_cast<unsigned char>('\n'):
  {
    match(static_cast<unsigned char>('\n'));
    break;
  }
  case static_cast<unsigned char>('\r'):
  {
    match(static_cast<unsigned char>('\r'));
    {
    if ((LA(1)==static_cast<unsigned char>('\n'))) {
      match(static_cast<unsigned char>('\n'));
    }
    else {
    }
    
    }
    break;
  }
  default:
  {
    throw antlr::NoViableAltForCharException(LA(1), getFilename(), getLine());
  }
  }
  }
  if ( inputState->guessing==0 ) {
#line 1098 "zlangpass1.g"
    _ttype = ANTLR_USE_NAMESPACE(antlr)Token::SKIP;
#line 2606 "ZLangLexer.cpp"
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}

void ZLangLexer::mCPP_LINE_CONTROL_INCLUDE_FILE(bool _createToken) {
  int _ttype; antlr::RefToken _token; int _begin=text.length();
  _ttype = CPP_LINE_CONTROL_INCLUDE_FILE;
  int _saveIndex;
  
  {
  for (;;) {
    if ((_tokenSet_7.member(LA(1)))) {
      {
      match(_tokenSet_7);
      }
    }
    else {
      goto _loop256;
    }
    
  }
  _loop256:;
  }
  if ( _createToken && _token==antlr::nullToken && _ttype!=antlr::Token::SKIP ) {
     _token = makeToken(_ttype);
     _token->setText(text.substr(_begin, text.length()-_begin));
  }
  _returnToken = _token;
  _saveIndex=0;
}


const unsigned long ZLangLexer::_tokenSet_0_data_[] = { 4294958072UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const antlr::BitSet ZLangLexer::_tokenSet_0(_tokenSet_0_data_,16);
const unsigned long ZLangLexer::_tokenSet_1_data_[] = { 4294958072UL, 4294966271UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const antlr::BitSet ZLangLexer::_tokenSet_1(_tokenSet_1_data_,16);
const unsigned long ZLangLexer::_tokenSet_2_data_[] = { 4294967288UL, 4294967167UL, 4026531839UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const antlr::BitSet ZLangLexer::_tokenSet_2(_tokenSet_2_data_,16);
const unsigned long ZLangLexer::_tokenSet_3_data_[] = { 0UL, 67043328UL, 126UL, 126UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const antlr::BitSet ZLangLexer::_tokenSet_3(_tokenSet_3_data_,10);
const unsigned long ZLangLexer::_tokenSet_4_data_[] = { 4294967288UL, 4294967291UL, 4026531839UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const antlr::BitSet ZLangLexer::_tokenSet_4(_tokenSet_4_data_,16);
const unsigned long ZLangLexer::_tokenSet_5_data_[] = { 4294967288UL, 4294967295UL, 3355443199UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const antlr::BitSet ZLangLexer::_tokenSet_5(_tokenSet_5_data_,16);
const unsigned long ZLangLexer::_tokenSet_6_data_[] = { 0UL, 67043328UL, 2281701374UL, 134217726UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const antlr::BitSet ZLangLexer::_tokenSet_6(_tokenSet_6_data_,10);
const unsigned long ZLangLexer::_tokenSet_7_data_[] = { 4294958072UL, 4294967291UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 4294967295UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL, 0UL };
const antlr::BitSet ZLangLexer::_tokenSet_7(_tokenSet_7_data_,16);

ANTLR_END_NAMESPACE
