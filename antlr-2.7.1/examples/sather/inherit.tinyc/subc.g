options {
	language = "Sather";
	mangleLiteralPrefix = "TK_";
}

class MYC_PARSER extends TINYC_PARSER;

 
// add initializers to variables
variable
{
	-- init action
}
	:	type_ declarator (ASSIGN aexpr)? SEMI
	;

