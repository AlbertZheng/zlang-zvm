#ifndef INC_ZLangLexer_hpp_
#define INC_ZLangLexer_hpp_

#include "antlr/config.hpp"
/* $ANTLR 2.7.1: "zlangpass1.g" -> "ZLangLexer.hpp"$ */
#include "antlr/CommonToken.hpp"
#include "antlr/InputBuffer.hpp"
#include "antlr/BitSet.hpp"
#include "ZLangLexerTokenTypes.hpp"
#include "antlr/CharScanner.hpp"
#line 1 "zlangpass1.g"

#include <antlr/CharScanner.hpp>
#include <zls/zlang/CZLangAST.hpp>

#line 17 "ZLangLexer.hpp"
ANTLR_BEGIN_NAMESPACE(zlang)
/**
 * <b>ZLang Lexer</b>
 *
 * <pre>
 * @version 0.2, 2000/12/16
 * @version 0.3, 2000/12/20
 * @version 1.0, 2001/5/11
 *   (1) rule 'IPv4ADDR_LITERAL' modified;
 *   (2) rule 'ESCAPE' patched;
 * @version 1.1, 2001/5/18
 *   (1) Added rule 'CPP_LINE_CONTROL';
 * @version 1.2, 2001/6/23
 *   (1) Supporting "NUM_QUAD", "NUM_HEX_QUAD";
 * @version 1.2, 2001/7/8
 *   (1) The grammar of 'ipaddress literal' and 'pport literal' was redesigned.
 * </pre>
 *
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zlang/zlangpass1.g,v $
 *
 * $Date: 2001/08/10 18:34:37 $
 *
 * $Revision: 1.5 $
 *
 * $Name:  $
 *
 * $Author: zls $
 *
 * Copyright(C) since 1998 by Albert Zheng, All Rights Reserved.
 *
 * lisong.zheng@gmail.com
 *
 * $State: Exp $
 */
class ZLangLexer : public antlr::CharScanner, public ZLangLexerTokenTypes
 {
#line 759 "zlangpass1.g"

private:
  /**
   * The member variable saves compiled-source-file-name.
   */
  std::string _stringCompiledSourceFileName;

public:
  virtual void setFilename(const std::string & f)
  {
    antlr::CharScanner::setFilename(f);
    _stringCompiledSourceFileName = f;
  }

#line 54 "ZLangLexer.hpp"
private:
  void initLiterals();
public:
  bool getCaseSensitiveLiterals() const;
public:
  ZLangLexer(std::istream& in);
  ZLangLexer(antlr::InputBuffer& ib);
  ZLangLexer(const antlr::LexerSharedInputState& state);
  antlr::RefToken nextToken();
  public: void mWS_(bool _createToken);
  public: void mSL_COMMENT(bool _createToken);
  public: void mML_COMMENT(bool _createToken);
  public: void mQUESTION(bool _createToken);
  public: void mLPAREN(bool _createToken);
  public: void mRPAREN(bool _createToken);
  public: void mLBRACK(bool _createToken);
  public: void mRBRACK(bool _createToken);
  public: void mRCURLY(bool _createToken);
  public: void mCOLON(bool _createToken);
  public: void mSCOPE(bool _createToken);
  public: void mCOMMA(bool _createToken);
  public: void mDOT(bool _createToken);
  public: void mASSIGN(bool _createToken);
  public: void mEQUAL(bool _createToken);
  public: void mLNOT(bool _createToken);
  public: void mBNOT(bool _createToken);
  public: void mNOT_EQUAL(bool _createToken);
  public: void mDIV(bool _createToken);
  public: void mDIV_ASSIGN(bool _createToken);
  public: void mPLUS(bool _createToken);
  public: void mPLUS_ASSIGN(bool _createToken);
  public: void mINC(bool _createToken);
  public: void mMINUS(bool _createToken);
  public: void mMINUS_ASSIGN(bool _createToken);
  public: void mDEC(bool _createToken);
  public: void mSTAR(bool _createToken);
  public: void mSTAR_ASSIGN(bool _createToken);
  public: void mMOD(bool _createToken);
  public: void mMOD_ASSIGN(bool _createToken);
  public: void mSR(bool _createToken);
  public: void mGE(bool _createToken);
  public: void mGT(bool _createToken);
  public: void mSL(bool _createToken);
  public: void mLE(bool _createToken);
  public: void mLT_(bool _createToken);
  public: void mBXOR(bool _createToken);
  public: void mBXOR_ASSIGN(bool _createToken);
  public: void mBOR(bool _createToken);
  public: void mBOR_ASSIGN(bool _createToken);
  public: void mLOR(bool _createToken);
  public: void mBAND(bool _createToken);
  public: void mBAND_ASSIGN(bool _createToken);
  public: void mLAND(bool _createToken);
  public: void mSEMI(bool _createToken);
  public: void mCHAR_LITERAL(bool _createToken);
  protected: void mESCAPE(bool _createToken);
  public: void mSTRING_LITERAL(bool _createToken);
  public: void mROPE_LITERAL(bool _createToken);
  public: void mIPv4ADDR_LITERAL(bool _createToken);
  protected: void mPURE_INT(bool _createToken);
  protected: void mIP_PROTOCOL(bool _createToken);
  public: void mIDENTIFIER(bool _createToken);
  protected: void mHEX_DIGIT(bool _createToken);
  protected: void mDIGIT(bool _createToken);
  public: void mNUM_HEX_INT(bool _createToken);
  public: void mNUM_INT(bool _createToken);
  protected: void mEXPONENT(bool _createToken);
  public: void mNUM_FLOAT(bool _createToken);
  public: void mCPP_LINE_CONTROL(bool _createToken);
  protected: void mCPP_LINE_CONTROL_INCLUDE_FILE(bool _createToken);
private:
  
  static const unsigned long _tokenSet_0_data_[];
  static const antlr::BitSet _tokenSet_0;
  static const unsigned long _tokenSet_1_data_[];
  static const antlr::BitSet _tokenSet_1;
  static const unsigned long _tokenSet_2_data_[];
  static const antlr::BitSet _tokenSet_2;
  static const unsigned long _tokenSet_3_data_[];
  static const antlr::BitSet _tokenSet_3;
  static const unsigned long _tokenSet_4_data_[];
  static const antlr::BitSet _tokenSet_4;
  static const unsigned long _tokenSet_5_data_[];
  static const antlr::BitSet _tokenSet_5;
  static const unsigned long _tokenSet_6_data_[];
  static const antlr::BitSet _tokenSet_6;
  static const unsigned long _tokenSet_7_data_[];
  static const antlr::BitSet _tokenSet_7;
};

ANTLR_END_NAMESPACE
#endif /*INC_ZLangLexer_hpp_*/
