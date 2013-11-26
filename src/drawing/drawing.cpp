#include "drawing.h"

#include "modifiers/modifier.h"


Drawing::Drawing()
{
    m_isValid = false;
}

Drawing::Drawing( Drawing::CreateNewFromFileCtor, const QString& fileName )
{
    m_sourceImageFileName = fileName;
    m_isValid = m_sourceImage.load( fileName );
    if ( !m_isValid )
        return;
    m_currentImage = m_sourceImage;
}


bool Drawing::addModifier( std::unique_ptr< Modifier > modifier )
{
    return modifier->apply( m_currentImage );
}
