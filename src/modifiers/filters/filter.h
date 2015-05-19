#pragma once

#include "modifiers/modifier.h"


class Filter : public Modifier
{
public:
    bool affectsColors() const override = 0;
    bool affectsGeometry() const override final     { return false; }
};
