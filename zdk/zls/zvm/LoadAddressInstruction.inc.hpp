/******************************************************************************
 * Load value指令Interpreter
 ******************************************************************************/
TZVMIndex _loadBoolGlobalVariableAddress();
TZVMIndex _loadByteGlobalVariableAddress();
TZVMIndex _loadSDWORDGlobalVariableAddress();
TZVMIndex _loadUDWORDGlobalVariableAddress();
TZVMIndex _loadSQWORDGlobalVariableAddress();
TZVMIndex _loadUQWORDGlobalVariableAddress();
TZVMIndex _loadDoubleGlobalVariableAddress();
TZVMIndex _loadStringGlobalVariableAddress();
TZVMIndex _loadRopeGlobalVariableAddress();
TZVMIndex _loadPPortGlobalVariableAddress();
TZVMIndex _loadIPv4AddressGlobalVariableAddress();
TZVMIndex _loadTableGlobalVariableAddress();

TZVMIndex _loadBoolStackVariableAddress();
TZVMIndex _loadByteStackVariableAddress();
TZVMIndex _loadSDWORDStackVariableAddress();
TZVMIndex _loadUDWORDStackVariableAddress();
TZVMIndex _loadSQWORDStackVariableAddress();
TZVMIndex _loadUQWORDStackVariableAddress();
TZVMIndex _loadDoubleStackVariableAddress();
TZVMIndex _loadStringStackVariableAddress();
TZVMIndex _loadRopeStackVariableAddress();
TZVMIndex _loadIPv4AddressStackVariableAddress();
TZVMIndex _loadPPortStackVariableAddress();
TZVMIndex _loadTableStackVariableAddress();

TZVMIndex _loadReferenceStackVariableReferenceToAddress();

TZVMIndex _loadBoolTableElementAddressByBoolKey();
TZVMIndex _loadBoolTableElementAddressByByteKey();
TZVMIndex _loadBoolTableElementAddressBySDWORDKey();
TZVMIndex _loadBoolTableElementAddressByUDWORDKey();
TZVMIndex _loadBoolTableElementAddressBySQWORDKey();
TZVMIndex _loadBoolTableElementAddressByUQWORDKey();
TZVMIndex _loadBoolTableElementAddressByDoubleKey();
TZVMIndex _loadBoolTableElementAddressByStringKey();
TZVMIndex _loadBoolTableElementAddressByRopeKey();
TZVMIndex _loadBoolTableElementAddressByPPortKey();
TZVMIndex _loadBoolTableElementAddressByIPv4AddressKey();

TZVMIndex _loadByteTableElementAddressByBoolKey();
TZVMIndex _loadByteTableElementAddressByByteKey();
TZVMIndex _loadByteTableElementAddressBySDWORDKey();
TZVMIndex _loadByteTableElementAddressByUDWORDKey();
TZVMIndex _loadByteTableElementAddressBySQWORDKey();
TZVMIndex _loadByteTableElementAddressByUQWORDKey();
TZVMIndex _loadByteTableElementAddressByDoubleKey();
TZVMIndex _loadByteTableElementAddressByStringKey();
TZVMIndex _loadByteTableElementAddressByRopeKey();
TZVMIndex _loadByteTableElementAddressByPPortKey();
TZVMIndex _loadByteTableElementAddressByIPv4AddressKey();

TZVMIndex _loadSDWORDTableElementAddressByBoolKey();
TZVMIndex _loadSDWORDTableElementAddressByByteKey();
TZVMIndex _loadSDWORDTableElementAddressBySDWORDKey();
TZVMIndex _loadSDWORDTableElementAddressByUDWORDKey();
TZVMIndex _loadSDWORDTableElementAddressBySQWORDKey();
TZVMIndex _loadSDWORDTableElementAddressByUQWORDKey();
TZVMIndex _loadSDWORDTableElementAddressByDoubleKey();
TZVMIndex _loadSDWORDTableElementAddressByStringKey();
TZVMIndex _loadSDWORDTableElementAddressByRopeKey();
TZVMIndex _loadSDWORDTableElementAddressByPPortKey();
TZVMIndex _loadSDWORDTableElementAddressByIPv4AddressKey();

TZVMIndex _loadUDWORDTableElementAddressByBoolKey();
TZVMIndex _loadUDWORDTableElementAddressByByteKey();
TZVMIndex _loadUDWORDTableElementAddressBySDWORDKey();
TZVMIndex _loadUDWORDTableElementAddressByUDWORDKey();
TZVMIndex _loadUDWORDTableElementAddressBySQWORDKey();
TZVMIndex _loadUDWORDTableElementAddressByUQWORDKey();
TZVMIndex _loadUDWORDTableElementAddressByDoubleKey();
TZVMIndex _loadUDWORDTableElementAddressByStringKey();
TZVMIndex _loadUDWORDTableElementAddressByRopeKey();
TZVMIndex _loadUDWORDTableElementAddressByPPortKey();
TZVMIndex _loadUDWORDTableElementAddressByIPv4AddressKey();

TZVMIndex _loadSQWORDTableElementAddressByBoolKey();
TZVMIndex _loadSQWORDTableElementAddressByByteKey();
TZVMIndex _loadSQWORDTableElementAddressBySDWORDKey();
TZVMIndex _loadSQWORDTableElementAddressByUDWORDKey();
TZVMIndex _loadSQWORDTableElementAddressBySQWORDKey();
TZVMIndex _loadSQWORDTableElementAddressByUQWORDKey();
TZVMIndex _loadSQWORDTableElementAddressByDoubleKey();
TZVMIndex _loadSQWORDTableElementAddressByStringKey();
TZVMIndex _loadSQWORDTableElementAddressByRopeKey();
TZVMIndex _loadSQWORDTableElementAddressByPPortKey();
TZVMIndex _loadSQWORDTableElementAddressByIPv4AddressKey();

TZVMIndex _loadUQWORDTableElementAddressByBoolKey();
TZVMIndex _loadUQWORDTableElementAddressByByteKey();
TZVMIndex _loadUQWORDTableElementAddressBySDWORDKey();
TZVMIndex _loadUQWORDTableElementAddressByUDWORDKey();
TZVMIndex _loadUQWORDTableElementAddressBySQWORDKey();
TZVMIndex _loadUQWORDTableElementAddressByUQWORDKey();
TZVMIndex _loadUQWORDTableElementAddressByDoubleKey();
TZVMIndex _loadUQWORDTableElementAddressByStringKey();
TZVMIndex _loadUQWORDTableElementAddressByRopeKey();
TZVMIndex _loadUQWORDTableElementAddressByPPortKey();
TZVMIndex _loadUQWORDTableElementAddressByIPv4AddressKey();

TZVMIndex _loadDoubleTableElementAddressByBoolKey();
TZVMIndex _loadDoubleTableElementAddressByByteKey();
TZVMIndex _loadDoubleTableElementAddressBySDWORDKey();
TZVMIndex _loadDoubleTableElementAddressByUDWORDKey();
TZVMIndex _loadDoubleTableElementAddressBySQWORDKey();
TZVMIndex _loadDoubleTableElementAddressByUQWORDKey();
TZVMIndex _loadDoubleTableElementAddressByDoubleKey();
TZVMIndex _loadDoubleTableElementAddressByStringKey();
TZVMIndex _loadDoubleTableElementAddressByRopeKey();
TZVMIndex _loadDoubleTableElementAddressByPPortKey();
TZVMIndex _loadDoubleTableElementAddressByIPv4AddressKey();

TZVMIndex _loadStringTableElementAddressByBoolKey();
TZVMIndex _loadStringTableElementAddressByByteKey();
TZVMIndex _loadStringTableElementAddressBySDWORDKey();
TZVMIndex _loadStringTableElementAddressByUDWORDKey();
TZVMIndex _loadStringTableElementAddressBySQWORDKey();
TZVMIndex _loadStringTableElementAddressByUQWORDKey();
TZVMIndex _loadStringTableElementAddressByDoubleKey();
TZVMIndex _loadStringTableElementAddressByStringKey();
TZVMIndex _loadStringTableElementAddressByRopeKey();
TZVMIndex _loadStringTableElementAddressByPPortKey();
TZVMIndex _loadStringTableElementAddressByIPv4AddressKey();

TZVMIndex _loadRopeTableElementAddressByBoolKey();
TZVMIndex _loadRopeTableElementAddressByByteKey();
TZVMIndex _loadRopeTableElementAddressBySDWORDKey();
TZVMIndex _loadRopeTableElementAddressByUDWORDKey();
TZVMIndex _loadRopeTableElementAddressBySQWORDKey();
TZVMIndex _loadRopeTableElementAddressByUQWORDKey();
TZVMIndex _loadRopeTableElementAddressByDoubleKey();
TZVMIndex _loadRopeTableElementAddressByStringKey();
TZVMIndex _loadRopeTableElementAddressByRopeKey();
TZVMIndex _loadRopeTableElementAddressByPPortKey();
TZVMIndex _loadRopeTableElementAddressByIPv4AddressKey();

TZVMIndex _loadIPv4AddressTableElementAddressByBoolKey();
TZVMIndex _loadIPv4AddressTableElementAddressByByteKey();
TZVMIndex _loadIPv4AddressTableElementAddressBySDWORDKey();
TZVMIndex _loadIPv4AddressTableElementAddressByUDWORDKey();
TZVMIndex _loadIPv4AddressTableElementAddressBySQWORDKey();
TZVMIndex _loadIPv4AddressTableElementAddressByUQWORDKey();
TZVMIndex _loadIPv4AddressTableElementAddressByDoubleKey();
TZVMIndex _loadIPv4AddressTableElementAddressByStringKey();
TZVMIndex _loadIPv4AddressTableElementAddressByRopeKey();
TZVMIndex _loadIPv4AddressTableElementAddressByPPortKey();
TZVMIndex _loadIPv4AddressTableElementAddressByIPv4AddressKey();

TZVMIndex _loadPPortTableElementAddressByBoolKey();
TZVMIndex _loadPPortTableElementAddressByByteKey();
TZVMIndex _loadPPortTableElementAddressBySDWORDKey();
TZVMIndex _loadPPortTableElementAddressByUDWORDKey();
TZVMIndex _loadPPortTableElementAddressBySQWORDKey();
TZVMIndex _loadPPortTableElementAddressByUQWORDKey();
TZVMIndex _loadPPortTableElementAddressByDoubleKey();
TZVMIndex _loadPPortTableElementAddressByStringKey();
TZVMIndex _loadPPortTableElementAddressByRopeKey();
TZVMIndex _loadPPortTableElementAddressByPPortKey();
TZVMIndex _loadPPortTableElementAddressByIPv4AddressKey();

/* 2001/7/17: Discarded
TZVMIndex _convertStringValueToAddress();
TZVMIndex _convertIPv4AddressValueToAddress();
TZVMIndex _convertPPortValueToAddress();
TZVMIndex _convertTableValueToAddress();
*/

TZVMIndex _loadStringConstantAddress();
TZVMIndex _loadRopeConstantAddress();
TZVMIndex _loadIPv4AddressConstantAddress();
TZVMIndex _loadPPortConstantAddress();

