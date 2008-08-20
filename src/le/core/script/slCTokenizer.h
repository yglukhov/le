#if !defined included_core_script_slCTokenizer_h
#define included_core_script_slCTokenizer_h

#include <iosfwd>
#include <string>
#include <vector>
#include <set>

namespace sokira
{
	namespace le
	{

typedef std::set<char> CCharSet;

enum ETokenMatchResult
{
	eInvalidToken = 0,
	eTokenIncomplete,
	eTokenComplete
};

enum ETokenType
{
	eTokenTypeUnknown = 0,
	eTokenTypeSpace,
	eTokenTypePunctuation,
	eTokenTypeIdentifier,
	eTokenTypeNumericLiteral,
	eTokenTypeStringLiteral
};

class ITokenMatch
{
	public:
		virtual ETokenType match(const char* string) const = 0;
};

struct CToken
{
	CToken(const std::string& tokenString, ETokenType inType = eTokenTypeUnknown) :
		token(tokenString), type(inType) {}
	std::string token;
	ETokenType type;
};

class CTokenizer
{
	public:
		CTokenizer();
		~CTokenizer();
		void setInputStream(std::istream* stream)
		{
			mStream = stream;
		}

		CToken nextToken();
		bool eof();

		char nextChar();
		void putBack(const std::string& string);

	protected:
		std::vector<ITokenMatch*> mTokenMatches;

	private:
		std::istream* mStream;
		std::string mBuffer;
};

	} // namespace le
} // namespace sokira

#endif // not defined included_core_script_slCTokenizer_h
