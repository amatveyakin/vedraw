#include <string>

#include "debug_utils.h"


standard_exception::standard_exception( const char* file, int line )
    : m_what( std::string( "Unknown exception in file '" ) + file + "', line " + std::to_string( line ) )
{
}

const char* standard_exception::what() const noexcept
{
    return m_what.c_str();
}
