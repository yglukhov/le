#if !defined H_slPrefix_included
#define H_slPrefix_included


#define LE_IN_OWN_NAMESPACE 0
#define LE_IN_SOKIRA_NAMESPACE 0

#if LE_IN_SOKIRA_NAMESPACE
	#define SOKIRA_NAMESPACE_START namespace sokira {
	#define SOKIRA_NAMESPACE_END };
	#define SOKIRA_NESTED_NAMESPACE sokira::
#else
	#define SOKIRA_NAMESPACE_START
	#define SOKIRA_NAMESPACE_END
	#define SOKIRA_NESTED_NAMESPACE
#endif // not LE_IN_SOKIRA_NAMESPACE

#if LE_IN_OWN_NAMESPACE
	#define LE_NAMESPACE_START SOKIRA_NAMESPACE_START namespace le {
	#define LE_NAMESPACE_END }; SOKIRA_NAMESPACE_END
	#define LE_NESTED_NAMESPACE SOKIRA_NESTED_NAMESPACE le::
#else
	#define LE_NAMESPACE_START SOKIRA_NAMESPACE_START
	#define LE_NAMESPACE_END SOKIRA_NAMESPACE_END
	#define LE_NESTED_NAMESPACE SOKIRA_NESTED_NAMESPACE
#endif // not LE_IN_OWN_NAMESPACE


#endif // not defined H_slPrefix_included
