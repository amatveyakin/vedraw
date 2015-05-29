#include <string>

#include "debug_utils.h"


Status::Status( ErrorCode errorCode_, const char* sourceFileName, int sourceLine, const char* sourceFunction )
    : m_errorCode( errorCode_ )
    , m_sourceFileName( sourceFileName )
    , m_sourceLine( sourceLine )
    , m_sourceFunction( sourceFunction )
{
}

Status::Status( ErrorCode errorCode_, const char* sourceFileName, int sourceLine, const char* sourceFunction, std::shared_ptr<Status> nestedError )
    : Status( errorCode_, sourceFileName, sourceLine, sourceFunction )
{
    m_nestedError = nestedError;
}

Status::Status( ErrorCode errorCode_, const char* sourceFileName, int sourceLine, const char* sourceFunction, const Exception& nestedException )
    : Status( errorCode_, sourceFileName, sourceLine, sourceFunction )
{
    m_nestedError = nestedException.m_status;
}

QString Status::errorStory() const
{
    QString story;
    const Status* status = this;
    bool first = true;
    while ( status ) {
        // TODO: Format - ?
        story += (first ? "" : "-> ") + args( "%1\n", status->m_errorMessage );
        status = status->m_nestedError.get();
        first = false;
    }
    return story.trimmed();
}

QString Status::errorStoryDebugInfo() const
{
    QString story;
    const Status* status = this;
    bool first = true;
    while ( status ) {
        // TODO: Format - ?
        // TODO: Print code name, not number (?)
        story += (first ? "" : "-> ") + args( "%1:%2 @ %3:\n[Error %4] %5\n\n",
                                              status->m_sourceFileName, status->m_sourceLine, status->m_sourceFunction,
                                              int( status->m_errorCode ), status->m_errorMessage );
        status = status->m_nestedError.get();
        first = false;
    }
    return story.trimmed();
}


Exception::Exception( std::shared_ptr< Status > status_ )
    : m_status( status_ )
{
}

const char* Exception::what() const noexcept
{
    return m_status->errorMessage().c_str();
}

QString Exception::errorStory() const
{
    return m_status->errorStory();
}

QString Exception::errorStoryDebugInfo() const
{
    return m_status->errorStoryDebugInfo();
}
