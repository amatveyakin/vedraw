// This module defines CARTESIAN_CALL macro that allows to call a template function parametrized by
// integral types to be called with values knows only at runtime.
//
// ===== Usage
//
// CARTESIAN_CALL( <callable>, <template_arg_1>, <template_arg_2>, ..., <template_arg_N> )
//               ( <normal_arg_1>, <normal_arg_2>, ..., <normal_arg_M> )
//
// <template_arg> ::= ( <anything> )
//                  | ( <type> )( <variable> )
//
// The first form of template argument passes <anything> as-is. It can be used to pass both
// type parameters and integral constants known at compile time.
// The second form will be unrolled at compile-time to generate all invocations of <callable>
// and select the right invocation at run-time based on <variable> value. <type> should be
// either a built-in Cartesian type or registered as described below.
//
//
// ===== Types overview; registering new types
//
// Cartesian types are registereda as follows:
//
//     #define CARTESIAN_CALL_TYPE_<type_name>  <value_1>, <value_2>, ..., <value_N>
//
// Cartesian type name can differ from C++ type. You can register several Cartesian types
// that cover different subsets of one C++ type values. Cartesian type name can contain only
// latin letters, digits and underscore marks.
//
// We recommend to put Cartesian type declaration next to where the type itself is declared.
// You do _not_ need to include this (or any other) header where a Cartesian type is declared.
// However, you do need to include this head if you want to use check if all enum values are
// handled using CARTESIAN_CALL_CHECK_ENUM_VALUE_LIST_COMPLETNESS or
// CARTESIAN_CALL_CHECK_VALUE_LIST_COMPLETNESS_2 macros.
//
// For the list of built-in Cartesian types see declarations after CARTESIAN_CALL definition.
//
//
// ===== Example
//
// Image you have a fancy hello world generator:
//
//     enum ProgrammingLanguage {
//         Cpp, Python, Haskell
//     };
//
//     template< typename HelloWorldGeneratorT, ProgrammingLanguage language, bool fast, bool correct >
//     void generateHelloWorld( int max_loc );
//
// To call this function from
//
//     template< typename HelloWorldGeneratorT >
//     void generateHelloWorld( ProgrammingLanguage language, bool fast, int max_loc );
//
// you need to write
//
//     #define CARTESIAN_CALL_TYPE_ProgrammingLanguage  Cpp, Python, Haskell
//
//     CARTESIAN_CALL_CHECK_ENUM_VALUE_LIST_COMPLETNESS(  )
//
//     CARTESIAN_CALL( generateHelloWorld,
//                     ( HelloWorldGeneratorT ),
//                     ( ProgrammingLanguage )( language ),
//                     ( bool )( fast ),
//                     ( true ),
//                   )( max_loc )

#pragma once

// TODO: Add boost headers to CMake dependencies
#include <boost/preprocessor.hpp>

#include "debug_utils.h"


// BEGIN: implementation details

#define CARTESIAN_IMPL_ADD_PAIR_FOR_VALUE( r, data, value ) \
    ( value ) data

#define CARTESIAN_IMPL_ADD_PAIR_FOR_EACH_IN_SEQ( seq, second ) \
    BOOST_PP_SEQ_TRANSFORM( CARTESIAN_IMPL_ADD_PAIR_FOR_VALUE, second, seq )


// Example.
// Requires:
//      #define CARTESIAN_CALL_TYPE_ProgrammingLanguage  Cpp, Python, Haskell
//
// Input:
//      value_pair = ( ProgrammingLanguage )( language )
// Output:
//      ( ( ( language )( Cpp ) )( ( language )( Python ) )( ( language )( Haskell ) ) )
//
// Input:
//      value_pair = ( false )
// Output:
//      ( ( ( false ) ) )
//
#define CARTESIAN_IMPL_ARG_TO_VALUE_PAIR_SEQ( r, data, value_pair ) \
    BOOST_PP_IIF( BOOST_PP_DEC( BOOST_PP_SEQ_SIZE( value_pair ) ), \
                  ( CARTESIAN_IMPL_ADD_PAIR_FOR_EACH_IN_SEQ( BOOST_PP_VARIADIC_TO_SEQ( BOOST_PP_CAT( CARTESIAN_CALL_TYPE_, BOOST_PP_SEQ_HEAD( value_pair ) ) ), \
                                                             BOOST_PP_SEQ_TAIL( value_pair ) ) ), \
                  ( ( value_pair ) ) \
                )

#define CARTESIAN_IMPL_ARGS_TO_VALUE_PAIR_SEQ_SEQ( ... ) \
    BOOST_PP_SEQ_FOR_EACH( CARTESIAN_IMPL_ARG_TO_VALUE_PAIR_SEQ, , BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ ) )


#define CARTESIAN_IMPL_FIRST( r, data, value_pair ) \
    BOOST_PP_SEQ_HEAD( value_pair )

#define CARTESIAN_IMPL_CHECK_EQ( r, data, value_pair ) \
    BOOST_PP_IIF( BOOST_PP_DEC( BOOST_PP_SEQ_SIZE( value_pair ) ), \
                  && BOOST_PP_SEQ_HEAD( value_pair ) == BOOST_PP_SEQ_TAIL( value_pair ), \
                )


// Example.
// Input:
//      seqs = ( ( func )( ( magic )( true ) )( ( false ) )( ( language )( Cpp ) ) )
// Output:
//      if ( magic == true || language == Cpp )
//          return func< true, false, Cpp >;
//
#define CARTESIAN_IMPL_CHECKED_CALL( r, seqs ) \
    if ( true BOOST_PP_SEQ_FOR_EACH( CARTESIAN_IMPL_CHECK_EQ, , BOOST_PP_SEQ_POP_FRONT( seqs ) ) ) \
        return BOOST_PP_SEQ_HEAD( seqs )< BOOST_PP_TUPLE_REM_CTOR( BOOST_PP_SEQ_TO_TUPLE( BOOST_PP_SEQ_TRANSFORM( CARTESIAN_IMPL_FIRST, , BOOST_PP_SEQ_POP_FRONT( seqs ) ) ) ) >;

// END: implementation details


// See comment on top of the file
//
// TODO: throw a custom exception: argument out of range
#define CARTESIAN_CALL( func, ... )  \
    [ & ](){ \
        BOOST_PP_SEQ_FOR_EACH_PRODUCT( CARTESIAN_IMPL_CHECKED_CALL, \
                                       BOOST_PP_SEQ_PUSH_FRONT( CARTESIAN_IMPL_ARGS_TO_VALUE_PAIR_SEQ_SEQ( __VA_ARGS__ ), ( func ) ) ) \
        ERROR; \
    }()



#define CARTESIAN_CALL_TYPE_bool  false, true
#define CARTESIAN_CALL_TYPE_binary  0, 1



// BEGIN: implementation details

#define CARTESIAN_IMPL_ELEM_TO_CASE( r, data, elem ) \
    case elem: break;

#define CARTESIAN_IMPL_ARGS_TO_CASES( ... ) \
    BOOST_PP_SEQ_FOR_EACH( CARTESIAN_IMPL_ELEM_TO_CASE, , BOOST_PP_VARIADIC_TO_SEQ( __VA_ARGS__ ) )

// END: implementation details


#define CARTESIAN_CALL_CHECK_VALUE_LIST_COMPLETNESS_2( cartesian_type, cpp_type ) \
    static inline void BOOST_PP_CAT( cartesianCallCheckEnumValueListCompletness_, cartesian_type )() { \
        cpp_type v; \
        switch ( v ) { \
            CARTESIAN_IMPL_ARGS_TO_CASES( BOOST_PP_CAT( CARTESIAN_CALL_TYPE_, cartesian_type ) ) \
        }; \
    }

#define CARTESIAN_CALL_CHECK_VALUE_LIST_COMPLETNESS( type ) \
    CARTESIAN_CALL_CHECK_VALUE_LIST_COMPLETNESS_2( type, type )
