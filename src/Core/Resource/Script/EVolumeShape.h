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
template <>
const CEnumNameMap TEnumReflection<EVolumeShape>::skNameMap = {
    { 0, "NoShape" },
    { 1, "AxisAlignedBoxShape" },
    { 2, "BoxShape" },
    { 3, "EllipsoidShape" },
    { 4, "CylinderShape" },
    { 5, "ConditionalShape" },
    { 6, "InvalidShape" },
 };
template <>
const int TEnumReflection<EVolumeShape>::skErrorValue = 6;

#endif // EVOLUMESHAPE

