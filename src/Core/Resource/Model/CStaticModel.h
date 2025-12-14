#ifndef CSTATICMODEL_H
#define CSTATICMODEL_H

#include "Core/Resource/Model/CBasicModel.h"
#include "Core/Render/FRenderOptions.h"
#include <vector>

class CIndexBuffer;
class CMaterial;

/* A CStaticModel is meant for meshes that don't move. It only links to one material,
 * and is used to combine surfaces from different world models into shared VBOs and
 * IBOs. This allows for a significantly reduced number of draw calls. */
class CStaticModel : public CBasicModel
{
    CMaterial *mpMaterial = nullptr;
    std::vector<CIndexBuffer> mIBOs;
    std::vector<std::vector<uint32_t>> mSurfaceEndOffsets;
    bool mTransparent = false;

public:
    CStaticModel();
    explicit CStaticModel(CMaterial *pMat);
    ~CStaticModel() override;
    void AddSurface(SSurface *pSurface);

    void BufferGL();
    void GenerateMaterialShaders();
    void ClearGLBuffer() override;
    void Draw(FRenderOptions Options);
    void DrawSurface(FRenderOptions Options, uint32_t Surface);
    void DrawWireframe(FRenderOptions Options, CColor WireColor = CColor::White());

    CMaterial* GetMaterial();
    void SetMaterial(CMaterial *pMat);
    bool IsTransparent() const;
    bool IsOccluder() const;

private:
    CIndexBuffer* InternalGetIBO(EPrimitiveType Primitive);
};

#endif // CSTATICMODEL_H
