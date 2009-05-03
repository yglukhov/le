%{
	#include "slCSokriptFlexLexer.hp"

	#define yyterminate() return static_cast<_sokira_le::CSokriptBisonParser::token_type>(YY_NULL)

	#define YY_USER_ACTION  yylloc->columns(yyleng);

	static int yywrap();
	static void consumeComment();
%}


%option c++
%option prefix="sokira_le_base_CSokript"

/* Macros */

LETTER		[a-zA-Z_]
DIGIT		[0-9]
OCTAL_INT	0[0-7]*
DECIMAL_INT [1-9]{DIGIT}*
HEX_INT		0[xX]({DIGIT}|[a-fA-F])+
FLOAT		{DIGIT}*\.{DIGIT}*([eE][+-]{DIGIT}+)?
IDENT		{LETTER}({LETTER}|{DIGIT})*
STR			\"[^\"]*\"
WSPACE		[ \t]+

/* " */

%%

%{
	// Place code here, which will be performed at the beginning of yylex() function
	yylloc->step();
	typedef _sokira_le::CSokriptBisonParser::token Token;
%}


"=="		{ return Token::EQ; }
"!="		{ return Token::NE; }
"<"			{ return Token::LT; }
"<="		{ return Token::LE; }
">"			{ return Token::GT; }
">="		{ return Token::GE; }
"!"			{ return Token::NOT; }
"+"			{ return Token::PLUS; }
"-"			{ return Token::MINUS; }
"*"			{ return Token::MULT; }
"/"			{ return Token::DIVIDE; }
"("			{ return Token::LPAREN; }
")"			{ return Token::RPAREN; }
"{"			{ return Token::LBRACE; }
"}"			{ return Token::RBRACE; }
"["			{ return Token::LBRAKET; }
"]"			{ return Token::RBRAKET; }
"="			{ return Token::TOKEN_ASSIGN; }
";"			{ return Token::SEMICOLON; }
","			{ return Token::COMMA; }
"if"		{ return Token::IF; }
"else"		{ return Token::ELSE; }
"while"		{ return Token::WHILE; }
"for"		{ return Token::FOR; }
"do"		{ return Token::DO; }
"function"	{ return Token::FUNCTION; }
"return"	{ return Token::RETURN; }
{OCTAL_INT}		{ yylval->intValue = (int)strtol(yytext, NULL, 8); return Token::LITERAL_INT; }
{DECIMAL_INT}	{ yylval->intValue = atoi(yytext); return Token::LITERAL_INT; }
{HEX_INT}		{ yylval->intValue = (int)strtol(yytext, NULL, 16); return Token::LITERAL_INT; }
{FLOAT}			{ yylval->floatValue = strtof(yytext, NULL); return Token::LITERAL_FLOAT; }
{IDENT}		{
				yylval->stringValue = strdup(yytext);
				return Token::IDENTIFIER;
			}
\"(\\.|[^\\"\n])*\"	{   /* " */
						yylval->stringValue = strdup(yytext + 1);
						yylval->stringValue[strlen(yylval->stringValue) - 1] = '\0';
						return Token::LITERAL_STRING;
					}

(\r\n|\n)+	{ yylloc->lines(yyleng); yylloc->step(); } // The regex handles both unix and windows line endings.
{WSPACE}	{ yylloc->step(); }
"//".*\n	{ yylloc->lines(); yylloc->step(); }
"/*"		{
				char c, c1;
				do
				{
					while ((c = yyinput()) != '*' && c != 0);

					if ((c1 = yyinput()) != '/' && c != 0)
						unput(c1);
					else
						break;
				}
				while (true);
			}

.			{ _le_sokript->lex_error("illegal token", static_cast<const void*>(yylloc)); }

%%

int yyFlexLexer::yylex()
{
	return 0;
}

#ifndef yywrap
int yywrap() { return 1; }
#endif
