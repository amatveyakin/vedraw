#ifndef IMAGE_H
#define IMAGE_H

#include <memory>

class QImage;
class QSize;
class QString;

namespace cv { class Mat; }

enum class ColorDepth;
enum class ImageFormat;


class Image
{
public:
    explicit Image();
//     explicit Image( const QImage& qimage );
    explicit Image( QSize size, ImageFormat format, ColorDepth depth );
    explicit Image( int width, int height, ImageFormat format, ColorDepth depth );
    explicit Image( const QString& filename );
    ~Image();

    ImageFormat imageFormat() const;
    ColorDepth colorDepth() const;
    int width() const;
    int height() const;
    QSize size() const;

    const cv::Mat* cvMat() const        { return m_mat.get(); }
    cv::Mat* cvMat()                    { return m_mat.get(); }

    QImage toQImage() const;
    bool save( const QString& filename ) const;

private:
    std::unique_ptr< cv::Mat > m_mat;
};

#endif // IMAGE_H
