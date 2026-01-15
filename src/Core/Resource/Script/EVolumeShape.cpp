#include "Core/Resource/Script/EVolumeShape.h"

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