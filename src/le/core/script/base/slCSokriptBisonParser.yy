
%{
	#include <list>
	#include <le/core/slCNumber.h>
	#include "slCSokriptImpl.hp"
	#include "slCSokriptInstruction.hp"

	#define _sokira_lelex(val, loc) mSokript->lex(static_cast<void*>(val), static_cast<void*>(loc))

	using namespace ::sokira::le;
%}

//%debug

%skeleton "lalr1.cc"
%defines

%name-prefix="_sokira_le"
%define "parser_class_name" "CSokriptBisonParser"
%parse-param { ::sokira::le::CSokriptImpl* mSokript }
// %lex-param { } // Place additional parameters here, if needed
%locations

// The structure for passing value between lexer and parser
%union
{
	char *stringValue;
	char charValue;
	float floatValue;
	int intValue;
	CObject* objectValue;
	std::list<char*>* stringList;
	CSokriptInstruction* instruction;
}


%token EQ
%token NE
%token LT
%token LE
%token GT
%token GE
%token NOT
%left  PLUS MINUS
%left  MULT DIVIDE
%left  UMINUS UPLUS						// Unary minus and plus. Pseudo-token
%token LPAREN RPAREN
%token LBRACE RBRACE
%token LBRAKET RBRAKET
%token TOKEN_ASSIGN
%token SEMICOLON
%token COMMA
%token IF
%token ELSE
%token WHILE
%token FOR
%token DO
%token FUNCTION
%token RETURN
%token <intValue> LITERAL_INT
%token <floatValue> LITERAL_FLOAT
%token <stringValue> LITERAL_STRING
%token <stringValue> IDENTIFIER

%type <stringValue> function_arg_definition

%type <objectValue> constant_expression literal string_literal simple_string_literal


%type <instruction> statement_list statement selection_statement loop_statement
%type <instruction> function_definition function_call function_arg_list not_empty_function_arg_list
%type <instruction> expression_or_nothing expression assignment_expression
%type <instruction> arithmetic_expression logic_expression // assignable_exression
%type <instruction> return_statement

%type <stringList> function_arg_list_definition not_empty_function_arg_list_definition

%initial-action
{
	// Initialize the initial location.
//	@$.begin.filename = @$.end.filename = &driver.file;
}

%% // Grammar rules and actions follow.

program
	: statement_list
		{
			CSokriptInstruction* returnInstruction = new CSokriptInstruction(eInstructionReturn);
			if ($1)
				$1->addInstruction(returnInstruction);
			else
				$1 = returnInstruction;

			$1 = CSokriptInstruction::postProcessBytecode($1, NULL);
			mSokript->setInstruction($1);
		}
	;

statement_list
	:									{ $$ = NULL; }
	| statement_list statement
		{
			$$ = $1;
			if ($$)
				$$->addInstruction($2);
			else
				$$ = $2;
		}
	;

statement
	: function_definition
	| expression_or_nothing SEMICOLON			{ $$ = $1; if ($$) $$->addInstruction(new CSokriptInstruction(eInstructionDiscard));	}
	| selection_statement
	| loop_statement
	| LBRACE statement_list RBRACE				{ $$ = $2;																					}
	| return_statement
	;

function_definition
	: FUNCTION IDENTIFIER LPAREN function_arg_list_definition RPAREN LBRACE statement_list RBRACE
		{
			$$ = CSokriptInstruction::createFunctionDefinition($2, $4, $7);
		}
	;

function_arg_list_definition
	:													{ $$ = new std::list<char*>(); }
	| not_empty_function_arg_list_definition
	;

not_empty_function_arg_list_definition
	: function_arg_definition												{ $$ = new std::list<char*>(); $$->push_back($1); }
	| not_empty_function_arg_list_definition COMMA function_arg_definition	{ $$ = $1; $$->push_back($3); }
	;

function_arg_definition
	: IDENTIFIER
	;

return_statement
	: RETURN expression_or_nothing SEMICOLON
		{
			$$ = ($2)?($2):(new CSokriptInstruction(eInstructionPushFloat, new CNumber(0)));
			$$->addInstruction(new CSokriptInstruction(eInstructionJumpToReturn));
		}
	;

selection_statement
: IF LPAREN expression RPAREN statement					{ $$ = CSokriptInstruction::createIfThenElse($3, $5, NULL);	}
	| IF LPAREN expression RPAREN statement ELSE statement	{ $$ = CSokriptInstruction::createIfThenElse($3, $5, $7);		}
	;

loop_statement
	: WHILE LPAREN expression RPAREN statement				{ $$ = CSokriptInstruction::createLoop($3, $5); }
	| FOR LPAREN expression_or_nothing SEMICOLON expression SEMICOLON expression_or_nothing RPAREN statement
		{
			if ($7)
			{
				$7->addInstruction(new CSokriptInstruction(eInstructionDiscard));
				if ($9)
					$9->addInstruction($7);
				else
					$9 = $7;
			}

			CSokriptInstruction* loopInstruction = CSokriptInstruction::createLoop($5, $9);
			if ($3)
			{
				CSokriptInstruction* discard = new CSokriptInstruction(eInstructionDiscard);
				discard->addInstruction(loopInstruction);
				$3->addInstruction(discard);
			}
			else
				$3 = loopInstruction;

			$$ = $3;
		}
	;

expression_or_nothing
	: expression
	|				{ $$ = NULL; }
	;

expression
	: assignment_expression
	| arithmetic_expression
	| logic_expression
	| IDENTIFIER { $$ = new CSokriptInstruction(eInstructionPushVar, new CString(
						CString::__CStringNoCopyDeallocWithFree($1)
											)); }
	| constant_expression { $$ = mSokript->pushConstantInstruction($1); }
	| function_call
	;

function_call
	: IDENTIFIER LPAREN function_arg_list RPAREN
		{
			$$ = $3;
			CSokriptInstruction* call = new CSokriptInstruction(eInstructionCall, new CString(
						CString::__CStringNoCopyDeallocWithFree($1)
											));
			if ($$)
				$$->addInstruction(call);
			else
				$$ = call;
		}
	;

function_arg_list
	:					{ $$ = NULL; }
	| not_empty_function_arg_list
	;

not_empty_function_arg_list
	: expression
	| not_empty_function_arg_list COMMA expression { $$ = $1; $$->addInstruction($3); }
	;

arithmetic_expression
	: expression PLUS expression		{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionAdd));		$$->addInstruction($3);		}
	| expression MINUS expression		{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionSubstract)); $$->addInstruction($3);		}
	| expression MULT expression		{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionMultiply));	$$->addInstruction($3);		}
	| expression DIVIDE expression		{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionDivide));	$$->addInstruction($3);		}
	| MINUS expression	%prec UMINUS	{ $$ = $2; $$->addInstruction(new CSokriptInstruction(eInstructionNegate));								}
	| PLUS expression	%prec UPLUS		{ $$ = $2;																										}
	| LPAREN expression RPAREN			{ $$ = $2;																										}
	;

logic_expression
	: expression LT expression			{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionLessThan));		$$->addInstruction($3);	}
	| expression LE expression			{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionLessEqual));		$$->addInstruction($3);	}
	| expression GT expression			{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionGreaterThan));	$$->addInstruction($3);	}
	| expression GE expression			{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionGreaterEqual));	$$->addInstruction($3);	}
	| expression EQ expression			{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionEqual));			$$->addInstruction($3);	}
	| expression NE expression			{ $$ = $1; $3->addInstruction(new CSokriptInstruction(eInstructionNotEqual));		$$->addInstruction($3);	}
	| NOT expression					{ $$ = $2; $2->addInstruction(new CSokriptInstruction(eInstructionNot));									}
	;

assignment_expression
	: IDENTIFIER TOKEN_ASSIGN expression { $$ = $3;
		$$->addInstruction(
			new CSokriptInstruction(
				eInstructionAssign,
				new CString(CString::__CStringNoCopyDeallocWithFree($1))
						)); }
	;

//assignable_exression
//	: IDENTIFIER										{ $$ = mSokript->assignableObjectByName($1); }
//	;

constant_expression										// Constant expressions are almost the same as arithmetic,
														// except they are calculated on compile time
	: literal
//	| constant_expression PLUS constant_expression		{ $$ = mSokript->addObjects($1, $3);		}
//	| constant_expression MINUS constant_expression		{ $$ = mSokript->substractObjects($1, $3);	}
//	| constant_expression MULT constant_expression		{ $$ = mSokript->multiplyObjects($1, $3);	}
//	| constant_expression DIVIDE constant_expression	{ $$ = mSokript->divideObjects($1, $3);		}
//	| MINUS constant_expression	%prec UMINUS			{ $$ = mSokript->negateObject($2);			}
//	| PLUS constant_expression	%prec UPLUS				{ $$ = $2;									}
//	| LPAREN constant_expression RPAREN					{ $$ = $2;									}
	;

literal
	: LITERAL_INT { $$ = new CNumber($1); }
	| LITERAL_FLOAT { $$ = new CNumber($1); }
	| string_literal
	;

string_literal
	: simple_string_literal
	| string_literal simple_string_literal { $$ = mSokript->addObjects($1, $2); }
	;

simple_string_literal
	: LITERAL_STRING { $$ = new CString(CString::__CStringNoCopyDeallocWithFree($1)); }
	;

%%

void _sokira_le::CSokriptBisonParser::error(const CSokriptBisonParser::location_type& l,
											const std::string& m)
{
	mSokript->parse_error(static_cast<const void*>(&l), static_cast<const void*>(&m));
}
