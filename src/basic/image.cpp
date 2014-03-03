#include <QImage>

#include <opencv2/opencv.hpp>

#include "image.h"

#include "basic/defs.h"
#include "utils/cpp_extensions.h"
#include "utils/debug_utils.h"
#include "utils/opencv_type_traits.h"


Image::Image()
{
    m_mat = std::make_unique< cv::Mat >();
}

Image::Image( CopyCtor, const Image& other )
{
    m_mat = std::make_unique< cv::Mat >( other.m_mat->clone() );
    m_colorSpace = other.m_colorSpace;
    m_hasAlpha = other.m_hasAlpha;
}

Image::Image( const QImage& origQImage )
{
    // TODO FIXME: fix byte order
    if ( origQImage.isNull() )
        m_mat = std::make_unique< cv::Mat >();
    // The stupidest implementation: always convert to a fixed format
    // TODO: choose closest format
    QImage qImage = origQImage;
    qImage.convertToFormat( QImage::Format_ARGB32 );
    cv::Mat rgbMat( qImage.height(), qImage.width(), CV_8UC4, qImage.bits(), qImage.bytesPerLine() );
    m_mat = std::make_unique< cv::Mat >();
    cv::cvtColor( rgbMat, *m_mat, CV_RGBA2BGRA );
    m_colorSpace = ColorSpace::RGB;
    m_hasAlpha = false;
}

Image::Image( QSize size_, ColorSpace space, bool alpha, ColorDepth depth )
    : Image( size_.width(), size_.height(), space, alpha, depth )
{
}

Image::Image( int width_, int height_, ColorSpace space, bool alpha, ColorDepth depth )
{
    m_mat = std::make_unique< cv::Mat >( height_, width_, toCvType( colorSpaceChannels( space, alpha ), depth ) );
    m_colorSpace = space;
    m_hasAlpha = alpha;
}

Image::Image( const QString& filename )
{
    m_mat = std::make_unique< cv::Mat >( cv::imread( filename.toStdString(), CV_LOAD_IMAGE_UNCHANGED ) );
}

Image::~Image()
{
}

bool Image::isNull() const
{
    return !m_mat->data;
}

bool Image::isValid() const
{
    return !isNull();
}

int Image::channelsCount() const
{
    int nChannels = m_mat->channels();
    ASSERT_THROW_STD( nChannels == colorSpaceChannels( colorSpace(), hasAlpha() ) );
    return nChannels;
}

ColorDepth Image::colorDepth() const
{
    return formCvDepth( m_mat->depth() );
}

ColorSpace Image::colorSpace() const
{
    return m_colorSpace;
}

bool Image::isColorful() const
{
    return !isGray();
}

bool Image::isGray() const
{
    return colorSpace() == ColorSpace::Gray;
}

bool Image::hasAlpha() const
{
    return m_hasAlpha;
}

int Image::width() const
{
    return m_mat->cols;
}

int Image::height() const
{
    return m_mat->rows;
}

QSize Image::size() const
{
    return QSize( width(), height() );
}


QImage Image::toQImage() const
{
    // TODO FIXME: fix byte order
    if ( isNull() )
        return QImage();
    // The stupidest implementation: always convert to a fixed format
    // TODO: choose closest format
    cv::Mat rgbMat;

//     cv::cvtColor( *m_mat, rgbMat, CV_BGRA2RGBA );
//     QImage result1( rgbMat.data, rgbMat.cols, rgbMat.rows, rgbMat.step, QImage::Format_ARGB32 );
    cv::cvtColor( *m_mat, rgbMat, CV_BGRA2RGB );
    QImage result1( rgbMat.data, rgbMat.cols, rgbMat.rows, rgbMat.step, QImage::Format_RGB888);

    QImage result2( result1 );
    result2.detach(); // enforce deep copy
    return result2;
}

bool Image::save( const QString& filename ) const
{
    return cv::imwrite( filename.toStdString(), *m_mat );
}
