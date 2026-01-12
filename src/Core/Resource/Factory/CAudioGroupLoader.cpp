#include "Core/Resource/Factory/CAudioGroupLoader.h"

#include "Core/Resource/CAudioGroup.h"
#include "Core/Resource/CAudioLookupTable.h"
#include "Core/Resource/CStringList.h"

std::unique_ptr<CAudioGroup> CAudioGroupLoader::LoadAGSC(IInputStream& rAGSC, CResourceEntry *pEntry)
{
    // For now we only load sound define IDs and the group ID!
    // Version check
    const auto Check = rAGSC.PeekU32();
    const auto Game = Check == 0x1 ? EGame::Echoes : EGame::Prime;
    auto pOut = std::make_unique<CAudioGroup>(pEntry);

    // Read header, navigate to Proj chunk
    if (Game == EGame::Prime)
    {
        rAGSC.ReadString();
        pOut->mGroupName = rAGSC.ReadString();
        const auto PoolSize = rAGSC.ReadU32();
        rAGSC.Seek(PoolSize + 0x4, SEEK_CUR);
    }
    else
    {
        rAGSC.Seek(0x4, SEEK_CUR);
        pOut->mGroupName = rAGSC.ReadString();
        pOut->mGroupID = rAGSC.ReadU16();
        const auto PoolSize = rAGSC.ReadU32();
        rAGSC.Seek(0xC + PoolSize, SEEK_CUR);
    }

    // Read needed data from the Proj chunk
    const auto Peek = rAGSC.PeekU16();

    if (Peek != 0xFFFF)
    {
        const auto ProjStart = rAGSC.Tell();
        rAGSC.Seek(0x4, SEEK_CUR);
        const auto GroupID = rAGSC.ReadU16();
        const auto GroupType = rAGSC.ReadU16();
        rAGSC.Seek(0x14, SEEK_CUR);
        const auto SfxTableStart = rAGSC.ReadU32();

        if (Game == EGame::Prime)
            pOut->mGroupID = GroupID;
        else
            ASSERT(pOut->mGroupID == GroupID);

        if (GroupType == 1)
        {
            rAGSC.Seek(ProjStart + SfxTableStart, SEEK_SET);
            const auto NumSounds = rAGSC.ReadU16();
            rAGSC.Seek(0x2, SEEK_CUR);

            pOut->mDefineIDs.reserve(NumSounds);
            for (uint32_t i = 0; i < NumSounds; i++)
            {
                pOut->mDefineIDs.push_back(rAGSC.ReadU16());
                rAGSC.Seek(0x8, SEEK_CUR);
            }
        }
    }

    return pOut;
}

std::unique_ptr<CAudioLookupTable> CAudioGroupLoader::LoadATBL(IInputStream& rATBL, CResourceEntry *pEntry)
{
    auto pOut = std::make_unique<CAudioLookupTable>(pEntry);
    const auto NumMacroIDs = rATBL.ReadU32();

    pOut->mDefineIDs.reserve(NumMacroIDs);
    for (uint32_t i = 0; i < NumMacroIDs; i++)
        pOut->mDefineIDs.push_back(rATBL.ReadU16());

    return pOut;
}

std::unique_ptr<CStringList> CAudioGroupLoader::LoadSTLC(IInputStream& rSTLC, CResourceEntry *pEntry)
{
    auto pOut = std::make_unique<CStringList>(pEntry);
    const auto NumStrings = rSTLC.ReadU32();

    pOut->mStringList.reserve(NumStrings);
    for (uint32_t i = 0; i < NumStrings; i++)
        pOut->mStringList.push_back(rSTLC.ReadString());

    return pOut;
}
