#include "Resource/Scan/CScan.h"

#include "Core/Resource/Script/CGameTemplate.h"
#include "Core/Resource/Script/NGameList.h"

CScan::CScan(CResourceEntry* pEntry)
    : CResource(pEntry)
{
    CGameTemplate* pGameTemplate = NGameList::GetGameTemplate(Game());
    mpTemplate = pGameTemplate->FindMiscTemplate("ScannableObjectInfo");
    ASSERT(mpTemplate != nullptr);

    CStructProperty* pProperties = mpTemplate->Properties();
    mPropertyData.resize(pProperties->DataSize());
    pProperties->Construct(mPropertyData.data());
}

CScan::~CScan() = default;

CStructRef CScan::ScanData()
{
    return CStructRef(mPropertyData.data(), mpTemplate->Properties());
}

/** Convenience property accessors */
CAssetRef CScan::ScanStringPropertyRef()
{
    constexpr uint32_t kStringIdMP1 = 0x1;
    constexpr uint32_t kStringIdMP2 = 0x2F5B6423;

    IProperty* pProperty = mpTemplate->Properties()->ChildByID(
        Game() <= EGame::Prime ? kStringIdMP1 : kStringIdMP2
    );

    return CAssetRef(mPropertyData.data(), pProperty);
}

CBoolRef CScan::IsCriticalPropertyRef()
{
    constexpr uint32_t kIsCriticalIdMP1 = 0x4;
    constexpr uint32_t kIsCriticalIdMP2 = 0x7B714814;

    IProperty* pProperty = mpTemplate->Properties()->ChildByID(
        Game() <= EGame::Prime ? kIsCriticalIdMP1 : kIsCriticalIdMP2
    );

    return CBoolRef(mPropertyData.data(), pProperty);
}

/** CResource interface */
std::unique_ptr<CDependencyTree> CScan::BuildDependencyTree()
{
    auto pTree = std::make_unique<CDependencyTree>();
    pTree->ParseProperties(Entry(), ScanData().Property(), ScanData().DataPointer());
    return pTree;
}
