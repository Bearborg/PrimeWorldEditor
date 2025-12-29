#ifndef CAUDIOGROUP
#define CAUDIOGROUP

#include "Core/Resource/CResource.h"
#include <span>
#include <vector>

// Very limited functionality - mostly just intended to find the AGSC that a sound ID belongs to
class CAudioGroup : public CResource
{
    DECLARE_RESOURCE_TYPE(AudioGroup)
    friend class CAudioGroupLoader;

    TString mGroupName;
    uint32_t mGroupID = UINT32_MAX;
    std::vector<uint16_t> mDefineIDs;

public:
    explicit CAudioGroup(CResourceEntry *pEntry = nullptr)
        : CResource(pEntry)
    {}

    // Accessors
    const TString& GroupName() const               { return mGroupName; }
    uint32_t GroupID() const                       { return mGroupID; }
    std::span<const uint16_t> SoundDefines() const { return mDefineIDs; }
};

#endif // CAUDIOGROUP

