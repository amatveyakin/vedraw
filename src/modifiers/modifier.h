#ifndef MODIFIER_H
#define MODIFIER_H

class QImage;


class Modifier
{
public:
    virtual ~Modifier() {}

    virtual bool affectsColors() const = 0;
    virtual bool affectsGeometry() const = 0;

    virtual bool apply( QImage& image ) const = 0;
};

#endif
