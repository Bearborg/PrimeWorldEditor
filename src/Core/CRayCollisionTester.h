#ifndef CRAYCOLLISIONHELPER_H
#define CRAYCOLLISIONHELPER_H

#include <Common/Math/CRay.h>

#include <cstdint>
#include <list>

class CBasicModel;
class CSceneNode;
struct SRayIntersection;
struct SViewInfo;

class CRayCollisionTester
{
    CRay mRay;
    std::list<SRayIntersection> mBoxIntersectList;

public:
    explicit CRayCollisionTester(const CRay& rkRay);
    ~CRayCollisionTester();

    const CRay& Ray() const { return mRay; }

    void AddNode(CSceneNode *pNode, uint32_t AssetIndex, float Distance);
    void AddNodeModel(CSceneNode *pNode, CBasicModel *pModel);
    SRayIntersection TestNodes(const SViewInfo& rkViewInfo);
};

#endif // CRAYCOLLISIONHELPER_H
