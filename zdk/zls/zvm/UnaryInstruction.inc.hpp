/******************************************************************************
 * Unary指令Interpreter
 ******************************************************************************/
TZVMIndex _bytePrefixInc();
TZVMIndex _sdwordPrefixInc();
TZVMIndex _udwordPrefixInc();
TZVMIndex _sqwordPrefixInc();
TZVMIndex _uqwordPrefixInc();
TZVMIndex _doublePrefixInc();

TZVMIndex _bytePrefixDec();
TZVMIndex _sdwordPrefixDec();
TZVMIndex _udwordPrefixDec();
TZVMIndex _sqwordPrefixDec();
TZVMIndex _uqwordPrefixDec();
TZVMIndex _doublePrefixDec();

TZVMIndex _bytePostfixInc();
TZVMIndex _sdwordPostfixInc();
TZVMIndex _udwordPostfixInc();
TZVMIndex _sqwordPostfixInc();
TZVMIndex _uqwordPostfixInc();
TZVMIndex _doublePostfixInc();

TZVMIndex _bytePostfixDec();
TZVMIndex _sdwordPostfixDec();
TZVMIndex _udwordPostfixDec();
TZVMIndex _sqwordPostfixDec();
TZVMIndex _uqwordPostfixDec();
TZVMIndex _doublePostfixDec();

TZVMIndex _byteUnaryPlus();
TZVMIndex _sdwordUnaryPlus();
TZVMIndex _udwordUnaryPlus();
TZVMIndex _sqwordUnaryPlus();
TZVMIndex _uqwordUnaryPlus();
TZVMIndex _doubleUnaryPlus();

TZVMIndex _byteUnaryMinus();
TZVMIndex _sdwordUnaryMinus();
TZVMIndex _udwordUnaryMinus();
TZVMIndex _sqwordUnaryMinus();
TZVMIndex _uqwordUnaryMinus();
TZVMIndex _doubleUnaryMinus();

TZVMIndex _byteBitNot();
TZVMIndex _sdwordBitNot();
TZVMIndex _udwordBitNot();
TZVMIndex _sqwordBitNot();
TZVMIndex _uqwordBitNot();
TZVMIndex _doubleBitNot();

TZVMIndex _boolLogicNot();

TZVMIndex _boolToByte();
TZVMIndex _boolToSDWORD();
TZVMIndex _boolToUDWORD();
TZVMIndex _boolToSQWORD();
TZVMIndex _boolToUQWORD();

TZVMIndex _byteToBool();
TZVMIndex _byteToSDWORD();
TZVMIndex _byteToUDWORD();
TZVMIndex _byteToSQWORD();
TZVMIndex _byteToUQWORD();
TZVMIndex _byteToDouble();

TZVMIndex _sdwordToBool();
TZVMIndex _sdwordToByte();
TZVMIndex _sdwordToUDWORD();
TZVMIndex _sdwordToSQWORD();
TZVMIndex _sdwordToUQWORD();
TZVMIndex _sdwordToDouble();

TZVMIndex _udwordToBool();
TZVMIndex _udwordToByte();
TZVMIndex _udwordToSDWORD();
TZVMIndex _udwordToSQWORD();
TZVMIndex _udwordToUQWORD();
TZVMIndex _udwordToDouble();

TZVMIndex _sqwordToBool();
TZVMIndex _sqwordToByte();
TZVMIndex _sqwordToSDWORD();
TZVMIndex _sqwordToUDWORD();
TZVMIndex _sqwordToUQWORD();
TZVMIndex _sqwordToDouble();

TZVMIndex _uqwordToBool();
TZVMIndex _uqwordToByte();
TZVMIndex _uqwordToSDWORD();
TZVMIndex _uqwordToUDWORD();
TZVMIndex _uqwordToSQWORD();
TZVMIndex _uqwordToDouble();

TZVMIndex _doubleToByte();
TZVMIndex _doubleToSDWORD();
TZVMIndex _doubleToUDWORD();
TZVMIndex _doubleToSQWORD();
TZVMIndex _doubleToUQWORD();

