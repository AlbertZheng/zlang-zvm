/******************************************************************************
 * Stack指令Interpreter
 ******************************************************************************/
TZVMIndex _popAny();
TZVMIndex _popBool();
TZVMIndex _popByte();
TZVMIndex _popSDWORD();
TZVMIndex _popUDWORD();
TZVMIndex _popSQWORD();
TZVMIndex _popUQWORD();
TZVMIndex _popDouble();
TZVMIndex _popString();
TZVMIndex _popRope();
TZVMIndex _popIPv4Address();
TZVMIndex _popPPort();
TZVMIndex _popTable();

TZVMIndex _ret();
TZVMIndex _pushBP();

TZVMIndex _constructBool();
TZVMIndex _constructByte();
TZVMIndex _constructSDWORD();
TZVMIndex _constructUDWORD();
TZVMIndex _constructSQWORD();
TZVMIndex _constructUQWORD();
TZVMIndex _constructDouble();
TZVMIndex _constructString();
TZVMIndex _constructRope();
TZVMIndex _constructIPv4Address();
TZVMIndex _constructPPort();

TZVMIndex _constructBoolTable();
TZVMIndex _constructByteTable();
TZVMIndex _constructSDWORDTable();
TZVMIndex _constructUDWORDTable();
TZVMIndex _constructSQWORDTable();
TZVMIndex _constructUQWORDTable();
TZVMIndex _constructDoubleTable();
TZVMIndex _constructStringTable();
TZVMIndex _constructRopeTable();
TZVMIndex _constructIPv4AddressTable();
TZVMIndex _constructPPortTable();

TZVMIndex _constructBoolReference();
TZVMIndex _constructByteReference();
TZVMIndex _constructSDWORDReference();
TZVMIndex _constructUDWORDReference();
TZVMIndex _constructSQWORDReference();
TZVMIndex _constructUQWORDReference();
TZVMIndex _constructDoubleReference();
TZVMIndex _constructStringReference();
TZVMIndex _constructRopeReference();
TZVMIndex _constructIPv4AddressReference();
TZVMIndex _constructPPortReference();
TZVMIndex _constructTableReference();

TZVMIndex _quickConstructStringObject();
TZVMIndex _quickConstructRopeObject();
TZVMIndex _quickConstructIPv4AddressObject();
TZVMIndex _quickConstructPPortObject();
TZVMIndex _quickConstructTableObject();


/******************************************************************************
 * Jump指令Interpreter
 ******************************************************************************/
TZVMIndex _boolFalseJump();
TZVMIndex _byteFalseJump();
TZVMIndex _sdwordFalseJump();
TZVMIndex _udwordFalseJump();
TZVMIndex _sqwordFalseJump();
TZVMIndex _uqwordFalseJump();
TZVMIndex _doubleFalseJump();
TZVMIndex _stringFalseJump();
TZVMIndex _ropeFalseJump();
TZVMIndex _ipv4addressFalseJump();
TZVMIndex _pportFalseJump();
TZVMIndex _tableFalseJump();

TZVMIndex _boolFalseCircuitJump();
TZVMIndex _byteFalseCircuitJump();
TZVMIndex _sdwordFalseCircuitJump();
TZVMIndex _udwordFalseCircuitJump();
TZVMIndex _sqwordFalseCircuitJump();
TZVMIndex _uqwordFalseCircuitJump();
TZVMIndex _doubleFalseCircuitJump();
TZVMIndex _stringFalseCircuitJump();
TZVMIndex _ropeFalseCircuitJump();
TZVMIndex _ipv4addressFalseCircuitJump();
TZVMIndex _pportFalseCircuitJump();

TZVMIndex _boolTrueCircuitJump();
TZVMIndex _byteTrueCircuitJump();
TZVMIndex _sdwordTrueCircuitJump();
TZVMIndex _udwordTrueCircuitJump();
TZVMIndex _sqwordTrueCircuitJump();
TZVMIndex _uqwordTrueCircuitJump();
TZVMIndex _doubleTrueCircuitJump();
TZVMIndex _stringTrueCircuitJump();
TZVMIndex _ropeTrueCircuitJump();
TZVMIndex _ipv4addressTrueCircuitJump();
TZVMIndex _pportTrueCircuitJump();

TZVMIndex _unlimitJump();

TZVMIndex _call();

