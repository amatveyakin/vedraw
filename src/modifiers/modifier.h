#ifndef MODIFIER_H
#define MODIFIER_H

class Modifier
{
public:
    ~Modifier() { }

    bool affectsColors() = 0;
    bool affectsGeometry() = 0;
};

#endif
