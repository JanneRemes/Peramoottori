#ifdef _DEBUG
#ifndef DEBUG_ASSERT
#define DEBUG_ASSERT

namespace pm
{
	/** \brief Custom assertion functions for debugging.
	*
	* \ingroup Debug
	*/

	class Passert
	{
	public:

		/** \brief Assert function to be used with custom assert macros.
		*
		* \param[in] file File where assert was called.
		* \param[in] line Line number where assert was called.
		*/
		static void Assert(const char* file, const int line);
	};
}

/// Program aborts if expression == false.
#define ASSERT(expression) \
	!(expression) ? pm::Passert::Assert(__FILE__, __LINE__) : void(0)

/// Program aborts if expression1 != expression2.
#define ASSERT_EQUAL(expression1, expression2) \
	expression1 != expression2 ? pm::Passert::Assert(__FILE__, __LINE__) : void(0)

/// Program aborts if expression1 == expression2.
#define ASSERT_NEQUAL(expression1, expression2) \
	expression1 == expression2 ? pm::Passert::Assert(__FILE__, __LINE__) : void(0)

/// Program aborts if value is between expression1 and expression2.
#define ASSERT_MINMAX(expression1, expression2, value) \
	expression1 < value && value < expression2 ? pm::Passert::Assert(__FILE__, __LINE__) : void(0)

#endif // DEBUG_ASSERT
#endif // _DEBUG


// Disable custom assert for release.
#ifdef NDEBUG 
#define ASSERT
#define ASSERT_EQUAL
#define ASSERT_NEQUAL
#define ASSERT_MINMAX
#endif