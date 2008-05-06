#if !defined H_included_slCAssertionPolicy
#define H_included_slCAssertionPolicy


namespace sokira
{
	namespace le
	{

class CAssertionPolicy : public CObject
{
	public:
		virtual void performAssert(const CString& expression, UInt lineNumber,
							const CString& fileName, const CObject *object,
							const CString& message);
};

class CUnitTestingAssertionPolicy : public CAssertionPolicy
{
	public:
		virtual void performAssert(const CString& expression, UInt lineNumber,
							const CString& fileName, const CObject *object,
							const CString& message);
};

	} // namespace le
} // namespace sokira


#endif // not defined H_included_slCAssertionPolicy
