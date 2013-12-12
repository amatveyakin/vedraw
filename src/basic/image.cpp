#include <QImage>

#include <opencv2/opencv.hpp>

#include "image.h"

#include "basic/defs.h"
#include "utils/cpp_extensions.h"


// TODO: implement

Image::Image()
{
    m_mat = std::make_unique< cv::Mat >();
}

// Image::Image( const QImage& qimage )
// {
//
// }

Image::Image( QSize size_, ImageFormat format, ColorDepth depth )
    : Image( size_.width(), size_.height(), format, depth )
{
}

Image::Image( int width_, int height_, ImageFormat format, ColorDepth depth )
{
    m_mat = std::make_unique< cv::Mat >( height_, width_, cvType( format, depth ) );
}

Image::Image( const QString& filename )
{
    cv::imread( filename.toStdString(), CV_LOAD_IMAGE_UNCHANGED );
}

Image::~Image()
{

}
