#ifndef CPOINTOFINTERESTEXTRA_H
#define CPOINTOFINTERESTEXTRA_H

#include "Core/Resource/TResPtr.h"
#include "Core/Resource/Script/Property/TPropertyRef.h"
#include "Core/ScriptExtra/CScriptExtra.h"

class CColor;
class CScan;

class CPointOfInterestExtra : public CScriptExtra
{
    // Tint POI billboard orange/red depending on scan importance
    CAssetRef mScanProperty;
    TResPtr<CScan> mpScanData;
    CBoolRef mScanIsCritical;

public:
    explicit CPointOfInterestExtra(CScriptObject *pInstance, CScene *pScene, CScriptNode *pParent = nullptr);
    void PropertyModified(IProperty* pProperty) override;
    void ModifyTintColor(CColor& Color) override;
    CScan* GetScan() const { return mpScanData; }
};

#endif // CPOINTOFINTERESTEXTRA_H
