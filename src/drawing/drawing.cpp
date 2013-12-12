#include "commit_history.h"
#include "drawing.h"

#include "utils/cpp_extensions.h"
#include "modifiers/modifier.h"


Drawing::Drawing()
{
}

Drawing::Drawing( Drawing::CreateNewFromFileCtor, const QString& fileName )
    : m_changes( std::make_unique< CommitHistory >() )
{
    m_sourceImageFileName = fileName;
    m_isValid = m_sourceImage.load( fileName );
    if ( !m_isValid )
        return;
    m_currentImage = m_sourceImage;
}

Drawing::~Drawing()
{
}


bool Drawing::isModified() const
{
    return m_isModified;
}

bool Drawing::addModifier( std::unique_ptr< Modifier > modifier )
{
    bool wasModified = m_isModified;
    if ( !m_isValid )
        return false;
    QImage newImage = m_currentImage;
    bool ok = modifier->apply( newImage );
    if ( !ok )
        return false;
    m_currentImage = newImage;
    m_changes->addCommit( std::move( modifier ) );
    m_isModified = true;
    emit currentImageChanged();
    if ( !wasModified )
        emit modifiedFlagChanged( true );
    return true;
}
