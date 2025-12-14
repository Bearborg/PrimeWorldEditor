#ifndef SRAYINTERSECTION
#define SRAYINTERSECTION

#include <Common/Math/CVector3f.h>
#include <cstdint>

class CSceneNode;

struct SRayIntersection
{
    bool Hit = false;
    float Distance = 0.0f;
    CVector3f HitPoint{CVector3f::Zero()};
    CSceneNode *pNode = nullptr;
    uint32_t ComponentIndex = UINT32_MAX;

    SRayIntersection() = default;
    SRayIntersection(bool _Hit, float _Distance, const CVector3f& _HitPoint, CSceneNode *_pNode, uint32_t _ComponentIndex)
        : Hit(_Hit), Distance(_Distance), HitPoint(_HitPoint), pNode(_pNode), ComponentIndex(_ComponentIndex) {}
};

#endif // SRAYINTERSECTION

