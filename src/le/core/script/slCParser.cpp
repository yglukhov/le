#include <le/core/config/slCompiler.h>

#include <functional>


#if LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_WINDOWS
#define BUILD_OS_WINDOWS
#define BUILD_PLATFORM_MSVC
#include <iterator>
#elif LE_TARGET_PLATFORM_FAMILY == LE_PLATFORM_FAMILY_UNIX
#define BUILD_OS_MACOSX
#endif


#define BUILD_MODULE_ASSERT


#include <le/core/script/slCParser.h>
#include <le/core/slCNumber.h>

namespace std
{
	namespace tr1 = ::std;
}

#include <sweet/assert/assert.cpp>

#include <sweet/parser/ParserGenerator.cpp>
#include <sweet/parser/ParserState.cpp>
#include <sweet/parser/ParserGrammar.cpp>
#include <sweet/parser/ParserItem.cpp>
#include <sweet/parser/ParserSymbol.cpp>
#include <sweet/parser/ParserAction.cpp>
#include <sweet/parser/ParserProduction.cpp>
#include <sweet/parser/ParserTransition.cpp>
#include <sweet/parser/ParserStateMachine.cpp>
#include <sweet/parser/Parser.ipp>
#include <sweet/parser/GrammarParser.cpp>
#include <sweet/parser/Error.cpp>
#include <sweet/parser/parser_types.cpp>
#include <sweet/parser/ParserErrorPolicy.cpp>

#include <sweet/pointer/ReferenceCount.cpp>

#include <sweet/atomic/atomic.ipp>

#include <sweet/error/Error.cpp>

#include <sweet/lexer/LexerStateMachine.cpp>
#include <sweet/lexer/LexerToken.cpp>
#include <sweet/lexer/LexerGenerator.cpp>
#include <sweet/lexer/LexerState.cpp>
#include <sweet/lexer/LexerAction.cpp>
#include <sweet/lexer/LexerTransition.cpp>
#include <sweet/lexer/LexerItem.cpp>
#include <sweet/lexer/RegexParser.cpp>
#include <sweet/lexer/RegexCharacter.cpp>
#include <sweet/lexer/RegexNode.cpp>
#include <sweet/lexer/RegexNodeLess.cpp>
#include <sweet/lexer/Lexer.ipp>
#include <sweet/lexer/Error.cpp>


namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CParser);


using namespace std;

struct SGramarConverter
{
	static inline SymbolAssociativity associativityFromGrammar(CParserGrammar::EAssociativity assoc)
	{
		switch (assoc)
		{
			case CParserGrammar::eAssociativityLeft: return ASSOCIATE_LEFT;
			case CParserGrammar::eAssociativityRight: return ASSOCIATE_RIGHT;
			case CParserGrammar::eAssociativityNone: return ASSOCIATE_NONE;
			default:;
		}
	//	return ASSOCIATE_NONE;
		return ASSOCIATE_NULL;
	}

	TCPointer<ITokenMatcher> matcherForTerminal(const CString& identifier)
	{
		ITokenMatcher* matcher = inGrammar->matcherForTerminal(identifier);
		if (matcher)
		{
			matcher->retain();
		}
		else
		{
			matcher = new CConstStringTokenMatcher(identifier);
		}
		return matcher;
	}

	ParserSymbol* symbol( SymbolType type, lexer::LexerTokenType token_type, const CString& lexeme)
	{
		pair<lexer::LexerTokenType, CString> key( make_pair(token_type, lexeme) );
		map<pair<lexer::LexerTokenType, CString>, ParserSymbol*>::iterator i = symbols_.find( key );
		if ( i == symbols_.end() )
		{
			i = symbols_.insert( make_pair(key, outGrammar->add_symbol(type, lexeme.UTF8String(), 0)) ).first;
			if (type == SYMBOL_TERMINAL)
			{
				i->second->set_associativity(associativityFromGrammar(inGrammar->associativityForTerminal(lexeme)));
				i->second->set_precedence(inGrammar->precedenceForTerminal(lexeme));
				//std::cout << "symbol " << lexeme << " " << i->second->get_associativity() << " " << i->second->get_precedence() << std::endl;

				TCPointer<ITokenMatcher> matcher = matcherForTerminal(lexeme);
				outLexer->addMatcher(matcher.get(), lexeme);
			}
		}

		if ( type != SYMBOL_NULL && i->second->get_type() == SYMBOL_NULL )
		{
			i->second->set_type( type );
		}

		return i->second;
	}

	inline void addIgnoreRule(CParserGrammar::SRule* rule)
	{
		for (std::vector<CString>::const_iterator it = rule->subIdentifiers.begin(); it != rule->subIdentifiers.end(); ++it)
		{
			TCPointer<ITokenMatcher> matcher = matcherForTerminal(*it);
			outLexer->addMatcher(matcher.get(), *it);
			outLexer->addIgnoredIdentifier(*it);
		}
	}

	void convert()
	{
		// Fill grammar
		typedef std::vector<CParserGrammar::SRule*> CRuleVector;
		const std::vector<CParserGrammar::SRule*>& rules = inGrammar->rules();
		int i = 0;
		for (CRuleVector::const_iterator it = rules.begin(); it != rules.end(); ++it)
		{
			CParserGrammar::SRule* rule = *it;
			if (!rule->identifier.hasPrefix("%"))
			{
				outGrammar->begin_production(symbol(SYMBOL_NON_TERMINAL, TOKEN_NULL, rule->identifier), 0);
				for (std::vector<CString>::const_iterator jIt = rule->subIdentifiers.begin(); jIt != rule->subIdentifiers.end(); ++jIt)
				{
					if (inGrammar->isTerminal(*jIt))
					{
						outGrammar->symbol(symbol(SYMBOL_TERMINAL, TOKEN_NULL, *jIt));
					}
					else if (inGrammar->isNonTerminal(*jIt))
					{
						outGrammar->symbol(symbol(SYMBOL_NON_TERMINAL, TOKEN_NULL, *jIt));
					}
					else
					{
						LE_ASSERT(false);
					}
				}

				if (rule->handler)
				{
					CString str(CNumber(i).valueAsString());
					outGrammar->action(outGrammar->add_action(str.UTF8String()));
				}

				outGrammar->end_production();
			//	std::cout << "}\n";
			}
			else if (rule->identifier == "%ignore")
			{
				addIgnoreRule(rule);
			}
			++i;
		}
	}

	CParserGrammar* inGrammar;
	ParserGrammar* outGrammar;
	CLexer* outLexer;
	map<pair<lexer::LexerTokenType, CString>, ParserSymbol*> symbols_;
};

using namespace sweet::parser;

::sokira::le::CObject::Ptr CParser::parse(std::istream& stream)
{
	ParserGrammar grammar;
	typedef Parser<const char*, CObject::Ptr> TParser;

	CLexer* lexer = new CLexer();
	lexer->setInputStream(&stream);

	{
		SGramarConverter converter;
		converter.inGrammar = mGrammar.get();
		converter.outGrammar = &grammar;
		converter.outLexer = lexer;
		converter.convert();
	}

	struct SParserFunction
	{
		static CObject::Ptr defaultHandler(std::vector<CObject::Ptr>& objects)
		{
			if (objects.size() == 1)
			{
				return objects[0];
			}
			return NULL;
		}

		static TParser::ParserActionFunction::result_type func(const ParserSymbol* symbol, const TParser::ParserNode* start, const TParser::ParserNode* finish, CParserGrammar::TRuleHandler realHandler)
		{
			std::vector<CObject::Ptr> objects;
			objects.reserve(finish - start);
			for (const TParser::ParserNode* i = start; i != finish; ++i)
			{
				CObject::Ptr p = i->get_user_data();
				if (!p)
				{
					p = new CString(i->get_lexeme().c_str());
				}
				objects.push_back(p);
			}
			return realHandler(objects);
		}
	};

	struct : public ParserErrorPolicy
	{
        virtual void parser_error( int line, const error::Error& error )
		{
			std::cout << "PARSE ERROR: " << error.what() << std::endl;
		}

        virtual void parser_vprintf( const char* format, va_list args )
		{
			LE_ASSERT(false);
		}

		TParser* parser;
	} errorPolicy;
	
	
	ParserStateMachine stateMachine(grammar);
	TParser parser(&stateMachine, &errorPolicy);

	errorPolicy.parser = &parser;

	parser.mLexer = lexer;

	using namespace std::tr1::placeholders;
	const std::vector<CParserGrammar::SRule*>& rules = mGrammar->rules();
	int i = 0;
	for (std::vector<CParserGrammar::SRule*>::const_iterator it = rules.begin(); it != rules.end(); ++it)
	{
		CParserGrammar::SRule* rule = *it;
		if (rule->handler)
		{
			CString str(CNumber(i).valueAsString());
//			TParser::ParserActionFunction func = std::bind(SParserFunction::func, _1, _2, _3, rule->handler);
//			parser.set_action_handler(str.UTF8String(), func);
		}
		++i;
	}

//	TParser::ParserActionFunction func = std::bind(SParserFunction::func, _1, _2, _3, SParserFunction::defaultHandler);
//	parser.set_default_action_handler(func);

	parser.parse(NULL, NULL);
	return parser.user_data();
}

void CParser::setGrammar(CParserGrammar::Ptr grammar)
{
	mGrammar = grammar;
}

CParserGrammar::Ptr CParser::grammar() const
{
	return mGrammar;
}


	}
}
