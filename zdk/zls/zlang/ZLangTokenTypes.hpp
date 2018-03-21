#ifndef INC_ZLangTokenTypes_hpp_
#define INC_ZLangTokenTypes_hpp_

ANTLR_BEGIN_NAMESPACE(zlang)
/* $ANTLR 2.7.1: "zlangpass1.g" -> "ZLangTokenTypes.hpp"$ */
struct ZLangTokenTypes {
  enum {
    EOF_ = 1,
    EXTERN_GFUNCTION_DECLARATION = 4,
    EXTERN_GVARIABLE_DECLARATION = 5,
    GFUNCTION_DEFINITION = 6,
    GVARIABLE_DEFINITION = 7,
    PARAMETERS_DECLARATION = 8,
    LVARIABLE_DEFINITION = 9,
    ELEMENT_INIT = 10,
    CODE_BLOCK = 11,
    COMPOUND_STATEMENTS = 12,
    EXPRESSION = 13,
    UNARY_PLUS = 14,
    UNARY_MINUS = 15,
    TYPECAST = 16,
    SUBSCRIPT = 17,
    CALLING = 18,
    POST_INC = 19,
    POST_DEC = 20,
    FOR_EXPRESSION1 = 21,
    FOR_EXPRESSION2 = 22,
    FOR_EXPRESSION3 = 23,
    LITERAL_extern = 24,
    LITERAL_table = 25,
    LT_ = 26,
    GT = 27,
    BAND = 28,
    IDENTIFIER = 29,
    LPAREN = 30,
    RPAREN = 31,
    SEMI = 32,
    COMMA = 33,
    LITERAL_void = 34,
    LITERAL_static = 35,
    ASSIGN = 36,
    LCURLY = 37,
    RCURLY = 38,
    LITERAL_break = 39,
    LITERAL_continue = 40,
    LITERAL_return = 41,
    LITERAL_if = 42,
    LITERAL_else = 43,
    LITERAL_while = 44,
    LITERAL_for = 45,
    LITERAL_byte = 46,
    LITERAL_bool = 47,
    LITERAL_sdword = 48,
    LITERAL_udword = 49,
    LITERAL_sqword = 50,
    LITERAL_uqword = 51,
    LITERAL_double = 52,
    LITERAL_string = 53,
    LITERAL_ipaddress = 54,
    LITERAL_pport = 55,
    LITERAL_rope = 56,
    LOR = 57,
    LAND = 58,
    BOR = 59,
    BXOR = 60,
    NOT_EQUAL = 61,
    EQUAL = 62,
    LE = 63,
    GE = 64,
    SL = 65,
    SR = 66,
    PLUS = 67,
    MINUS = 68,
    STAR = 69,
    DIV = 70,
    MOD = 71,
    INC = 72,
    DEC = 73,
    BNOT = 74,
    LNOT = 75,
    DOT = 76,
    LBRACK = 77,
    RBRACK = 78,
    NUM_INT = 79,
    NUM_HEX_INT = 80,
    NUM_QUAD = 81,
    NUM_HEX_QUAD = 82,
    NUM_FLOAT = 83,
    CHAR_LITERAL = 84,
    STRING_LITERAL = 85,
    IPv4ADDR_LITERAL = 86,
    PPORT_LITERAL = 87,
    LITERAL_true = 88,
    LITERAL_false = 89,
    ROPE_LITERAL = 90,
    NULL_TREE_LOOKAHEAD = 3
  };
};
ANTLR_END_NAMESPACE
#endif /*INC_ZLangTokenTypes_hpp_*/
