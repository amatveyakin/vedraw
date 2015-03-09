#include "commit_history.h"
#include "drawing.h"

#include "basic/image.h"
#include "modifiers/modifier.h"


Drawing::Drawing()
{
    m_sourceImage = std::make_unique< Image >();
    cloneCurrentImageFromSource();
}

Drawing::Drawing( Drawing::CreateNewFromFileCtor, const QString& fileName )
    : m_changes( std::make_unique< CommitHistory >() )
{
    m_sourceImageFileName = fileName;
    m_sourceImage = std::make_unique< Image >( fileName );
    if ( !m_sourceImage->isValid() )
        return;
    cloneCurrentImageFromSource();
}

Drawing::~Drawing()
{
}


bool Drawing::isValid() const
{
    return m_sourceImage->isValid();
}

bool Drawing::isModified() const
{
    return m_isModified;
}

bool Drawing::addModifier( std::unique_ptr< Modifier > modifier )
{
    if ( !isValid() )
        return false;
    auto newImage = std::make_unique< Image >( Image::CopyCtor(), *m_currentImage );
    bool ok = modifier->apply( *newImage );
    if ( !ok )
        return false;
    m_currentImage = std::move( newImage );
    m_changes->addCommit( std::move( modifier ) );
    m_isModified = true;
    emit changed();
    return true;
}

void Drawing::cloneCurrentImageFromSource()
{
    m_currentImage = std::make_unique< Image >( Image::CopyCtor(), *m_sourceImage );
}
