#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

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


#define ASSERT(expression)                          \
do {                                                \
  if ( !( expression ) )                            \
    ERROR();                                        \
} while (0)


#define ASSERT_RETURN_X(expression, return_value)   \
do {                                                \
  if ( !( expression ) ) {                          \
    ERROR();                                        \
    return return_value;                            \
  }                                                 \
} while (0)

#define ASSERT_RETURN(expression)     ASSERT_RETURN_X( expression, )
#define ERROR_RETURN_X(return_value)  ASSERT_RETURN_X( false, return_value )
#define ERROR_RETURN()                ASSERT_RETURN_X( false, )

// TODO: Add exception-based versions and use them


#endif // DEBUG_UTILS_H
