#ifndef CPP_EXTENSIONS_H
#define CPP_EXTENSIONS_H

#include <memory>


#if __cplusplus <= 201103L
namespace std
{
template< class T, class... Args >
std::unique_ptr< T > make_unique( Args&&... args )
{
    return std::unique_ptr< T >( new T( std::forward< Args >( args )... ) );
}
}
#endif // __cplusplus <= 201103L

#endif // CPP_EXTENSIONS_H
