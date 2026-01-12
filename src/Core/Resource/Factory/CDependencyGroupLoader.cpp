#include "Core/Resource/Factory/CDependencyGroupLoader.h"

#include <Common/Macros.h>
#include "Core/Resource/CDependencyGroup.h"

static EGame VersionTest(IInputStream& rDGRP, uint32_t DepCount)
{
    // Only difference between versions is asset ID length. Just check for EOF with 32-bit ID length.
    const auto Start = rDGRP.Tell();
    rDGRP.Seek(DepCount * 8, SEEK_CUR);
    const auto Remaining = rDGRP.Size() - rDGRP.Tell();

    EGame Game = EGame::CorruptionProto;

    if (Remaining < 32)
    {
        bool IsEOF = true;

        for (uint32_t iRem = 0; iRem < Remaining; iRem++)
        {
            const auto Byte = rDGRP.ReadU8();

            if (Byte != 0xFF)
            {
                IsEOF = false;
                break;
            }
        }

        if (IsEOF)
            Game = EGame::PrimeDemo;
    }

    rDGRP.Seek(Start, SEEK_SET);
    return Game;
}

std::unique_ptr<CDependencyGroup> CDependencyGroupLoader::LoadDGRP(IInputStream& rDGRP, CResourceEntry *pEntry)
{
    if (!rDGRP.IsValid())
        return nullptr;

    const auto NumDependencies = rDGRP.ReadU32();
    const auto Game = VersionTest(rDGRP, NumDependencies);

    auto pGroup = std::make_unique<CDependencyGroup>(pEntry);

    for (uint32_t iDep = 0; iDep < NumDependencies; iDep++)
    {
        rDGRP.Seek(0x4, SEEK_CUR); // Skip dependency type
        const CAssetID AssetID(rDGRP, Game);
        pGroup->AddDependency(AssetID);
    }

    return pGroup;
}
