#ifndef CSCAN_H
#define CSCAN_H

#include "Core/Resource/CResource.h"
#include "Core/Resource/Script/Property/TPropertyRef.h"

#include <memory>

class CDependencyTree;
class CScriptTemplate;

/** Scannable object parameters from SCAN assets */
class CScan : public CResource
{
    DECLARE_RESOURCE_TYPE(Scan)
    friend class CScanLoader;
    friend class CScanCooker;

    /** Script template specifying scan data layout */
    CScriptTemplate* mpTemplate;

    /** Scan property data */
    std::vector<uint8_t> mPropertyData;

public:
    explicit CScan(CResourceEntry* pEntry = nullptr);
    ~CScan() override;

    CStructRef ScanData();

    /** Convenience property accessors */
    CAssetRef ScanStringPropertyRef();
    CBoolRef IsCriticalPropertyRef();

    /** CResource interface */
    std::unique_ptr<CDependencyTree> BuildDependencyTree() override;
};

#endif // CSCAN_H
