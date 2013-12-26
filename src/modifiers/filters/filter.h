#pragma once

#include "modifiers/modifier.h"


class Filter : public Modifier
{
public:
    virtual bool affectsColors() const override = 0;
    virtual bool affectsGeometry() const override final     { return false; }
};
