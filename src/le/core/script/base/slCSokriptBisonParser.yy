
%{
	#include <stdio.h>
	#include <le/core/slCNumber.h>
	#include "slCSokriptImpl.hp"
	#include "slCSokriptInstruction.hp"

	#define _sokira_lelex(val, loc) mSokript->lex(static_cast<void*>(val), static_cast<void*>(loc))

//	using namespace ::sokira::le;

	inline ::sokira::le::CSokriptInstruction* newInstruction(::sokira::le::EInstruction instruction, ::sokira::le::CObject* arg = NULL)
	{
		return new ::sokira::le::CSokriptInstruction(instruction, arg);
	}

	static ::sokira::le::CSokriptInstruction* createIfThenElseInstruction(
			::sokira::le::CSokriptInstruction* expression,
			::sokira::le::CSokriptInstruction* ifPart,
			::sokira::le::CSokriptInstruction* elsePart);

	static ::sokira::le::CSokriptInstruction* createLoopInstruction(
			::sokira::le::CSokriptInstruction* expression,
			::sokira::le::CSokriptInstruction* loopPart);
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
	::sokira::le::CObject* objectValue;
	::sokira::le::CSokriptInstruction* instruction;
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
%token TOKEN_ASSIGN
%token SEMICOLON
%token COMMA
%token IF
%token ELSE
%token WHILE
%token FOR
%token DO
%token PRINT
%token FUNCTION
%token VAR
%token <intValue> LITERAL_INT
%token <floatValue> LITERAL_FLOAT
%token <stringValue> LITERAL_STRING
%token <stringValue> IDENTIFIER

%type <objectValue> constant_expression literal string_literal simple_string_literal


%type <instruction> statement_list statement selection_statement loop_statement
%type <instruction> function_definition function_call function_arg_list
%type <instruction> expression_or_nothing expression assignment_expression
%type <instruction> arithmetic_expression logic_expression // assignable_exression

%initial-action
{
	// Initialize the initial location.
//	@$.begin.filename = @$.end.filename = &driver.file;
}

%% // Grammar rules and actions follow.

program
	: statement_list { $1->addInstruction(newInstruction(::sokira::le::eInstructionReturn)); mSokript->setInstruction($1); }
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
	| expression_or_nothing SEMICOLON			{ $$ = $1; if ($$) $$->addInstruction(newInstruction(::sokira::le::eInstructionDiscard));	}
	| selection_statement
	| loop_statement
	| LBRACE statement_list RBRACE				{ $$ = $2;																					}
	;

function_definition
	: FUNCTION IDENTIFIER LPAREN function_arg_list_definition RPAREN LBRACE statement_list RBRACE
		{
			::sokira::le::CSokriptInstruction* instruction = newInstruction(::sokira::le::eInstructionReturn);
			if ($7)
				$7->addInstruction(instruction);
			else
				$7 = instruction;

			::sokira::le::CSokriptInstruction* jump = newInstruction(::sokira::le::eInstructionJump);
			jump->mArg = (::sokira::le::CObject*)((::sokira::le::SInt32)$7->length());
			instruction = newInstruction(::sokira::le::eInstructionStartFunction, new ::sokira::le::CString(
						::sokira::le::CString::__CStringNoCopyDeallocWithFree($2)
											));
			jump->addInstruction($7);
			instruction->addInstruction(jump);
			$$ = instruction;
		}
	;

function_arg_list_definition
	: // empty
	| function_arg_list_definition COMMA function_arg_definition
	;

function_arg_definition
	: VAR IDENTIFIER
	;

selection_statement
	: IF LPAREN expression RPAREN statement					{ $$ = createIfThenElseInstruction($3, $5, NULL);	}
	| IF LPAREN expression RPAREN statement ELSE statement	{ $$ = createIfThenElseInstruction($3, $5, $7);		}
	;

loop_statement
	: WHILE LPAREN expression RPAREN statement				{ $$ = createLoopInstruction($3, $5); }
	| FOR LPAREN expression_or_nothing SEMICOLON expression SEMICOLON expression_or_nothing RPAREN statement
		{
			if ($7)
			{
				$7->addInstruction(newInstruction(::sokira::le::eInstructionDiscard));
				if ($9)
					$9->addInstruction($7);
				else
					$9 = $7;
			}

			::sokira::le::CSokriptInstruction* loopInstruction = createLoopInstruction($5, $9);
			if ($3)
			{
				::sokira::le::CSokriptInstruction* discard = newInstruction(::sokira::le::eInstructionDiscard);
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
	| IDENTIFIER { $$ = newInstruction(::sokira::le::eInstructionPushVar, new ::sokira::le::CString(
						::sokira::le::CString::__CStringNoCopyDeallocWithFree($1)
											)); }
	| constant_expression { $$ = mSokript->pushConstantInstruction($1); }
	| function_call
	;

function_call
	: IDENTIFIER LPAREN function_arg_list RPAREN
		{
			$$ = $3;
			::sokira::le::CSokriptInstruction* call = newInstruction(::sokira::le::eInstructionCall, new ::sokira::le::CString(
						::sokira::le::CString::__CStringNoCopyDeallocWithFree($1)
											));
			if ($$)
				$$->addInstruction(call);
			else
				$$ = call;
		}

	| PRINT LPAREN expression RPAREN	{ $$ = $3; $$->addInstruction(newInstruction(::sokira::le::eInstructionPrint));				}
	;

function_arg_list
	:					{ $$ = NULL; }
	| expression
	| function_arg_list COMMA expression
	;

arithmetic_expression
	: expression PLUS expression		{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionAdd));		$$->addInstruction($3);		}
	| expression MINUS expression		{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionSubstract)); $$->addInstruction($3);		}
	| expression MULT expression		{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionMultiply));	$$->addInstruction($3);		}
	| expression DIVIDE expression		{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionDivide));	$$->addInstruction($3);		}
	| MINUS expression	%prec UMINUS	{ $$ = $2; $$->addInstruction(newInstruction(::sokira::le::eInstructionNegate));								}
	| PLUS expression	%prec UPLUS		{ $$ = $2;																										}
	| LPAREN expression RPAREN			{ $$ = $2;																										}
	;

logic_expression
	: expression LT expression			{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionLessThan));		$$->addInstruction($3);	}
	| expression LE expression			{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionLessEqual));		$$->addInstruction($3);	}
	| expression GT expression			{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionGreaterThan));	$$->addInstruction($3);	}
	| expression GE expression			{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionGreaterEqual));	$$->addInstruction($3);	}
	| expression EQ expression			{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionEqual));			$$->addInstruction($3);	}
	| expression NE expression			{ $$ = $1; $3->addInstruction(newInstruction(::sokira::le::eInstructionNotEqual));		$$->addInstruction($3);	}
	| NOT expression					{ $$ = $2; $2->addInstruction(newInstruction(::sokira::le::eInstructionNot));									}
	;

assignment_expression
	: IDENTIFIER TOKEN_ASSIGN expression { $$ = $3;
		$$->addInstruction(
			newInstruction(
				::sokira::le::eInstructionAssign,
				new ::sokira::le::CString(
						::sokira::le::CString::__CStringNoCopyDeallocWithFree($1)
											)
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
	: LITERAL_INT { $$ = new ::sokira::le::CNumber($1); }
	| LITERAL_FLOAT { $$ = new ::sokira::le::CNumber($1); }
	| string_literal
	;

string_literal
	: simple_string_literal
	| string_literal simple_string_literal { $$ = mSokript->addObjects($1, $2); }
	;

simple_string_literal
	: LITERAL_STRING { $$ = new ::sokira::le::CString(::sokira::le::CString::__CStringNoCopyDeallocWithFree($1)); }
	;

%%

using namespace ::sokira::le;

CSokriptInstruction* createIfThenElseInstruction(CSokriptInstruction* expression,
				CSokriptInstruction* ifPart, CSokriptInstruction* elsePart)
{
	if (elsePart)
	{
		CSokriptInstruction* secondJump = newInstruction(eInstructionJump);
		secondJump->mArg = (CObject*)((SInt32)elsePart->length());

		if (!ifPart) ifPart = newInstruction(eInstructionNOP);

		CSokriptInstruction* firstJump = newInstruction(eInstructionJumpIfFalse);

		ifPart->addInstruction(secondJump);
		firstJump->mArg = (CObject*)((SInt32)ifPart->length());
		ifPart->addInstruction(elsePart);
		firstJump->addInstruction(ifPart);
		expression->addInstruction(firstJump);
		return expression;
	}

	// else

	if (ifPart)
	{
		CSokriptInstruction* jump = newInstruction(eInstructionJumpIfFalse);
		jump->mArg = (CObject*)ifPart->length();
		jump->addInstruction(ifPart);
		expression->addInstruction(jump);
	}
	else
		expression->addInstruction(newInstruction(eInstructionDiscard));

	return expression;
}

CSokriptInstruction* createLoopInstruction(CSokriptInstruction* expression,
					CSokriptInstruction* loopPart)
{
	if (loopPart)
	{
		CSokriptInstruction* jumpBack = newInstruction(eInstructionJump);
		CSokriptInstruction* jump = newInstruction(eInstructionJumpIfFalse);
		jump->mArg = (CObject*)(loopPart->length() + jumpBack->length());
		jump->addInstruction(loopPart);
		expression->addInstruction(jump);
		jumpBack->mArg = (CObject*)(-(SInt32)(expression->length() + 1));
		jump->addInstruction(jumpBack);
	}
	else
	{
		CSokriptInstruction* jumpBack = newInstruction(eInstructionJumpIfTrue);
		jumpBack->mArg = (CObject*)(-(SInt32)(expression->length() + 1));
		expression->addInstruction(jumpBack);
	}

	return expression;
}


void _sokira_le::CSokriptBisonParser::error(const CSokriptBisonParser::location_type& l,
											const std::string& m)
{
	mSokript->parse_error(static_cast<const void*>(&l), static_cast<const void*>(&m));
}
