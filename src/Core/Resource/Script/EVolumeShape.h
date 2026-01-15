#ifndef EVOLUMESHAPE
#define EVOLUMESHAPE

#include <Common/EnumReflection.h>

enum class EVolumeShape
{
    NoShape,
    AxisAlignedBoxShape,
    BoxShape,
    EllipsoidShape,
    CylinderShape,
    ConditionalShape,
    InvalidShape
};

#endif // EVOLUMESHAPE

