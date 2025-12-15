#ifndef CCHARACTERNODE_H
#define CCHARACTERNODE_H

#include "Core/Render/CBoneTransformData.h"
#include "Core/Resource/Animation/CAnimSet.h"
#include "Core/Scene/CSceneNode.h"

class CAnimSet;

class CCharacterNode : public CSceneNode
{
    TResPtr<CAnimSet> mpCharacter;
    CBoneTransformData mTransformData;
    uint32_t mActiveCharSet;
    uint32_t mActiveAnim;
    bool mAnimated;
    float mAnimTime;

    mutable bool mTransformDataDirty;

public:
    explicit CCharacterNode(CScene *pScene, uint32_t NodeID, CAnimSet *pChar = nullptr, CSceneNode *pParent = nullptr);
    ~CCharacterNode() override;

    ENodeType NodeType() const override;
    void PostLoad() override;
    void AddToRenderer(CRenderer *pRenderer, const SViewInfo& rkViewInfo) override;
    void Draw(FRenderOptions Options, int ComponentIndex, ERenderCommand Command, const SViewInfo& rkViewInfo) override;
    SRayIntersection RayNodeIntersectTest(const CRay& rkRay, uint32_t AssetID, const SViewInfo& rkViewInfo) override;

    CVector3f BonePosition(uint32_t BoneID);
    void SetCharSet(CAnimSet *pChar);
    void SetActiveChar(uint32_t CharIndex);
    void SetActiveAnim(uint32_t AnimIndex);

    CAnimSet* Character() const      { return mpCharacter; }
    uint32_t ActiveCharIndex() const { return mActiveCharSet; }
    uint32_t ActiveAnimIndex() const { return mActiveAnim; }
    CAnimation* CurrentAnim() const  { return (mAnimated && mpCharacter ? mpCharacter->FindAnimationAsset(mActiveAnim) : nullptr); }
    bool IsAnimated() const          { return (mAnimated && CurrentAnim() != nullptr); }

    void SetAnimated(bool Animated)     { mAnimated = Animated; SetDirty(); }
    void SetAnimTime(float Time)        { mAnimTime = Time; ConditionalSetDirty(); }

protected:
    bool IsDirty() const         { return mTransformDataDirty; }
    void SetDirty()              { mTransformDataDirty = true; }
    void ConditionalSetDirty()   { if (IsAnimated()) SetDirty(); }
    void UpdateTransformData();
};

#endif // CCHARACTERNODE_H
