#pragma once

#include <memory>

#include "defs.h"

class QImage;
class QSize;
class QString;

namespace cv { class Mat; }


class Image
{
public:
    struct CopyCtor {};

    explicit Image();
    explicit Image( CopyCtor, const Image& other );  // prevent accidental copying
    explicit Image( const QImage& qImage );
    explicit Image( QSize size, ColorSpace space, bool alpha, ColorDepth depth );
    explicit Image( int width, int height, ColorSpace space, bool alpha, ColorDepth depth );
    explicit Image( const QString& filename );
    ~Image();

    bool isNull() const;
    bool isValid() const;
    int channelsCount() const;
    ColorDepth colorDepth() const;
    ColorSpace colorSpace() const;
    bool isColorful() const;
    bool isGray() const;
    bool hasAlpha() const;
    int width() const;
    int height() const;
    QSize size() const;

    const cv::Mat& cvMat() const        { return *m_mat.get(); }
    cv::Mat& cvMat()                    { return *m_mat.get(); }

    QImage toQImage() const;
    bool save( const QString& filename ) const;

private:
    std::unique_ptr< cv::Mat > m_mat;
    ColorSpace m_colorSpace = ColorSpace::Gray;   // TODO: Do we want to store something other than Gray and RGB?
    bool m_hasAlpha = false;
};
