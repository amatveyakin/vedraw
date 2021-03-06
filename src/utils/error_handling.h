// TODO: Add logging
// TODO: Create some predefined exceptions, to handle RAM exhaustion.
// TODO: QString vs std::string vs char*
// TODO: Use format strings instead of streams; store both english and translated message. It will probably require to abandon atream logic and pass format string and all args to macro instead, wrapped to a special help macro MAYBE_TR.

#pragma once

#include <csignal>
#include <exception>
#include <memory>
#include <sstream>
#include <string>

#include "qt_extensions.h"


class Exception;

class Status {
public:
    enum class ErrorCode {
        Ok = 0,
        IllegalArgument,
        NotFound,
        FailedPrecondition,
        DataLoss,
        Aborted,
        OutOfMemory,
        InternalError,
        Unknown,
    };

    // Use STATUS macro to create a new Status
    Status( ErrorCode errorCode_, const char* sourceFileName, int sourceLine, const char* sourceFunction );
    Status( ErrorCode errorCode_, const char* sourceFileName, int sourceLine, const char* sourceFunction, std::shared_ptr< Status > nestedError );
    Status( ErrorCode errorCode_, const char* sourceFileName, int sourceLine, const char* sourceFunction, const Exception& nestedException );

    bool ok() const noexcept                            { return m_errorCode == ErrorCode::Ok; }
    ErrorCode errorCode() const noexcept                { return m_errorCode; }
    const std::string& errorMessage() const noexcept    { return m_errorMessage; }
    QString errorStory() const;
    QString errorStoryDebugInfo() const;

    template< typename T >
    Status& operator<<( T&& message ) {
        std::ostringstream stream;
        stream << message;
        m_errorMessage += stream.str();
        return *this;
    }

private:
    ErrorCode m_errorCode = ErrorCode::Ok;
    std::string m_errorMessage;
    const char* m_sourceFileName = nullptr;
    int m_sourceLine = 0;
    const char* m_sourceFunction = nullptr;
    // Invariant: m_nestedError is never Ok.
    // Invariant: if this is Ok, m_nestedError is always null.
    std::shared_ptr< const Status > m_nestedError;
};


class Exception : std::exception
{
public:
    explicit Exception( std::shared_ptr< Status > status_ );

    const Status& status() const                { return *m_status; }
    const char* what() const noexcept override;
    QString errorStory() const;
    QString errorStoryDebugInfo() const;

    template< typename T >
    Exception& operator<<( T&& message ) {
        *m_status << message;
        return *this;
    }

private:
    // Invariant: m_status is not null.
    // Invariant: *m_status is not Ok.
    std::shared_ptr< Status > m_status;

    friend class Status;
};


#define STATUS( code ) \
    Status( Status::ErrorCode::code, __FILE__, __LINE__, __func__ )
#define CHAIN_STATUS( code, nested_error ) \
    Status( code, __FILE__, __LINE__, __func__, nested_error )

#define EXCEPTION( code ) \
    Exception( std::make_shared< Status >( STATUS( code ) ) )
#define CHAIN_EXCEPTION( code, nested_error ) \
    Exception( std::make_shared< Status >( STATUS( code, nested_error ) ) )

// Try/catch replacement. Converts all exceptions to instances of Exception type.
// Always has one catch clause, because Exception is not supposed to be derived from.
// Use these macros everywhere instead of normal try/catch.
#define TRY                                                 \
    try {                                                   \
        try
#define CATCH                                               \
        catch ( Exception e ) {                             \
            throw;                                          \
        }                                                   \
        catch ( const std::exception& e ) {                 \
            throw EXCEPTION( Unknown ) << e.what();  /* TODO: Assign specific types to standard exceptions when possible */ \
        }                                                   \
        catch ( ... ) {                                     \
            throw EXCEPTION( Unknown );                     \
        }                                                   \
    } catch ( Exception e )


// TODO: Limit the number of times each PAUSE triggers per launch
// In debug mode, pause the program.
// In release mode, do nothing.
#ifdef _MSC_VER
#   if defined _DEBUG
#       include <intrin.h>
#       define PAUSE()                  __debugbreak ()
#   else
#       define PAUSE()                  do { } while ( false )
#   endif
#else // !_MSC_VER
#   if !defined ( QT_NO_DEBUG ) && ( defined ( __i386__ ) || defined ( __x86_64__ ) )
#       define PAUSE()                  ::raise( SIGTRAP );    // CLEAN-UP: Isn't there a gcc intrinsic?
#   else
#       define PAUSE()                  do { } while ( false )
#   endif
#endif // !_MSC_VER


// Macro for really unexpected internal logic errors.
// If the error might have happened due to an external reason (missing or broken file, user requested an impossible action, etc.),
// return a Status or throw an Exception manually.
#define ERROR()                                             \
do {                                                        \
    PAUSE();                                                \
    throw EXCEPTION( InternalError );                       \
} while ( false )

#define CHECK( expression )                                 \
do {                                                        \
    if ( !( expression ) ) {                                \
        PAUSE();                                            \
        throw EXCEPTION( InternalError ) << "Assertion failed: " << #expression; \
    }                                                       \
} while ( false )

#define CHECK_OK( status )                                  \
do {                                                        \
    if ( !( status ).ok() ) {                               \
        PAUSE();                                            \
        throw CHAIN_EXCEPTION( InternalError, status ) << "Assertion failed: status is expected to be OK."; \
    }                                                       \
} while ( false )
