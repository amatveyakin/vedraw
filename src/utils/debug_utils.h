// TODO: rename this file
// TODO: Fix indentation
// TODO: Rename: "ASSERT" -> "FAIL"/"FATAL"/"CRASH"/"TERMINATE"/...; "ASSERT_..." -> "CHECK_..."; "ERROR" -> ""
// TODO: Add log strings: i.e. {CHECK,/*empty means unconditionally*/}_{LOG,THROW,FAIL,/*empty means just pause*/}(...) << "log_message"   (Will "_STD" still be necessary?)
// TODO: When should debugger be paused?
//         - on log with high level (and depending on a flag (?))
//         - on throw (depending on a flag (?))
//         - on fail (always)

#pragma once

#include <exception>
#include <string>


// In debug mode, pause the program.
// In release mode, do nothing.
#ifdef _MSC_VER
#  if defined _DEBUG
#    include <intrin.h>
#    define ERROR()                 __debugbreak ()
#  else
#    define ERROR()                 do { } while (0)
#  endif
#else // !_MSC_VER
#  if !defined (QT_NO_DEBUG) && (defined (__i386__) || defined (__x86_64__))
#    define ERROR()                 asm ("int $3")                    // TODO: Use gcc build-in command instead
#  else
#    define ERROR()                 do { } while (0)
#  endif
#endif // !_MSC_VER


#define ASSERT( expression )                        \
do {                                                \
  if ( !( expression ) )                            \
    ERROR();                                        \
} while (0)


#define ASSERT_RETURN_X( expression, return_value ) \
do {                                                \
  if ( !( expression ) ) {                          \
    ERROR();                                        \
    return return_value;                            \
  }                                                 \
} while (0)

#define ASSERT_RETURN( expression )     ASSERT_RETURN_X( expression, )
#define ERROR_RETURN_X( return_value )  ASSERT_RETURN_X( false, return_value )
#define ERROR_RETURN()                  ASSERT_RETURN_X( false, )

struct standard_exception : std::exception
{
    standard_exception( const char* file, int line );
    const char* what() const noexcept override;
private:
    std::string m_what;
};

// TODO: Add text to standard errors
#define ASSERT_THROW( expression, exception )       \
do {                                                \
  if ( !( expression ) ) {                          \
    ERROR();                                        \
    throw exception;                                \
  }                                                 \
} while (0)

#define ERROR_THROW( exception )        ASSERT_THROW( false, exception )
#define ASSERT_THROW_STD( expression )  ASSERT_THROW( expression, standard_exception( __FILE__, __LINE__ ) )
#define ERROR_THROW_STD()               ASSERT_THROW( false, standard_exception( __FILE__, __LINE__ ) )
