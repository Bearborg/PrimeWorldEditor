#ifndef CCOLLISIONNODE_H
#define CCOLLISIONNODE_H

#include "Core/Scene/CSceneNode.h"

class CCollisionMeshGroup;

class CCollisionNode : public CSceneNode
{
    TResPtr<CCollisionMeshGroup> mpCollision;

public:
    CCollisionNode(CScene *pScene, uint32_t NodeID, CSceneNode *pParent = nullptr, CCollisionMeshGroup *pCollision = nullptr);
    ~CCollisionNode() override;

    ENodeType NodeType() const override;
    void AddToRenderer(CRenderer *pRenderer, const SViewInfo& rkViewInfo) override;
    void Draw(FRenderOptions Options, int ComponentIndex, ERenderCommand Command, const SViewInfo& rkViewInfo) override;
    void RayAABoxIntersectTest(CRayCollisionTester& rTester, const SViewInfo& rkViewInfo) override;
    SRayIntersection RayNodeIntersectTest(const CRay& rkRay, uint32_t AssetID, const SViewInfo& rkViewInfo) override;
    void SetCollision(CCollisionMeshGroup *pCollision);
};

#endif // CCOLLISIONNODE_H
