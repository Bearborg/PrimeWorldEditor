#include "Core/Resource/Factory/CAnimEventLoader.h"

#include "Core/CAudioManager.h"
#include "Core/GameProject/CGameProject.h"
#include "Core/Resource/CAudioGroup.h"
#include "Core/Resource/Animation/CAnimEventData.h"

void CAnimEventLoader::LoadEvents(IInputStream& rEVNT)
{
    const auto Version = rEVNT.ReadULong();
    ASSERT(Version == 1 || Version == 2);

    // Loop Events
    const auto NumLoopEvents = rEVNT.ReadULong();
    for (uint32 iLoop = 0; iLoop < NumLoopEvents; iLoop++)
    {
        LoadLoopEvent(rEVNT);
    }

    // User Events
    const auto NumUserEvents = rEVNT.ReadULong();
    for (uint32 iUser = 0; iUser < NumUserEvents; iUser++)
    {
        LoadUserEvent(rEVNT);
    }

    // Effect Events
    const auto NumEffectEvents = rEVNT.ReadULong();
    for (uint32 iFX = 0; iFX < NumEffectEvents; iFX++)
    {
        LoadEffectEvent(rEVNT);
    }

    // Sound Events
    if (Version == 2)
    {
        const auto NumSoundEvents = rEVNT.ReadULong();
        for (uint32 iSound = 0; iSound < NumSoundEvents; iSound++)
        {
            LoadSoundEvent(rEVNT);
        }
    }
}

int32 CAnimEventLoader::LoadEventBase(IInputStream& rEVNT)
{
    rEVNT.Skip(0x2);
    rEVNT.ReadString();
    rEVNT.Skip(mGame < EGame::CorruptionProto ? 0x13 : 0x17);
    const int32 CharacterIndex = rEVNT.ReadLong();
    rEVNT.Skip(mGame < EGame::CorruptionProto ? 0x4 : 0x18);
    return CharacterIndex;
}

void CAnimEventLoader::LoadLoopEvent(IInputStream& rEVNT)
{
    LoadEventBase(rEVNT);
    rEVNT.Skip(0x1);
}

void CAnimEventLoader::LoadUserEvent(IInputStream& rEVNT)
{
    LoadEventBase(rEVNT);
    rEVNT.Skip(0x4);
    rEVNT.ReadString();
}

void CAnimEventLoader::LoadEffectEvent(IInputStream& rEVNT)
{
    const int32 CharIndex = LoadEventBase(rEVNT);
    rEVNT.Skip(mGame < EGame::CorruptionProto ? 0x8 : 0x4);
    const CAssetID ParticleID(rEVNT, mGame);
    mpEventData->AddEvent(CharIndex, ParticleID);

    if (mGame <= EGame::Prime)
        rEVNT.ReadString();
    else if (mGame <= EGame::Echoes)
        rEVNT.Skip(0x4);

    rEVNT.Skip(0x8);
}

void CAnimEventLoader::LoadSoundEvent(IInputStream& rEVNT)
{
    const int32 CharIndex = LoadEventBase(rEVNT);

    // Metroid Prime 1/2
    if (mGame <= EGame::Echoes)
    {
        const uint32 SoundID = rEVNT.ReadULong() & 0xFFFF;
        rEVNT.Skip(0x8);
        if (mGame >= EGame::Echoes)
            rEVNT.Skip(0xC);

        if (SoundID != 0xFFFF)
        {
            const SSoundInfo SoundInfo = gpResourceStore->Project()->AudioManager()->GetSoundInfo(SoundID);

            if (SoundInfo.pAudioGroup)
                mpEventData->AddEvent(CharIndex, SoundInfo.pAudioGroup->ID());
        }
    }
    // Metroid Prime 3
    else
    {
        const CAssetID SoundID(rEVNT, mGame);
        mpEventData->AddEvent(CharIndex, SoundID);
        rEVNT.Skip(0x8);

        for (uint32 StructIdx = 0; StructIdx < 2; StructIdx++)
        {
            const auto StructType = rEVNT.ReadULong();
            ASSERT(StructType <= 2);

            if (StructType == 1)
            {
                rEVNT.Skip(4);
            }
            else if (StructType == 2)
            {
                // This is a maya spline
                rEVNT.Skip(2);
                const auto KnotCount = rEVNT.ReadULong();
                rEVNT.Skip(0xA * KnotCount);
                rEVNT.Skip(9);
            }
        }
    }
}

// ************ STATIC ************
std::unique_ptr<CAnimEventData> CAnimEventLoader::LoadEVNT(IInputStream& rEVNT, CResourceEntry *pEntry)
{
    auto ptr = std::make_unique<CAnimEventData>(pEntry);

    CAnimEventLoader Loader;
    Loader.mpEventData = ptr.get();
    Loader.mGame = EGame::Prime;
    Loader.LoadEvents(rEVNT);

    return ptr;
}

std::unique_ptr<CAnimEventData> CAnimEventLoader::LoadAnimSetEvents(IInputStream& rANCS)
{
    auto ptr = std::make_unique<CAnimEventData>();

    CAnimEventLoader Loader;
    Loader.mpEventData = ptr.get();
    Loader.mGame = EGame::Echoes;
    Loader.LoadEvents(rANCS);

    return ptr;
}

std::unique_ptr<CAnimEventData> CAnimEventLoader::LoadCorruptionCharacterEventSet(IInputStream& rCHAR)
{
    auto ptr = std::make_unique<CAnimEventData>();

    CAnimEventLoader Loader;
    Loader.mpEventData = ptr.get();
    Loader.mGame = EGame::Corruption;

    // Read event set header
    rCHAR.Skip(0x4); // Skip animation ID
    rCHAR.ReadString(); // Skip set name

    // Read effect events
    const auto NumEffectEvents = rCHAR.ReadULong();
    for (uint32 EventIdx = 0; EventIdx < NumEffectEvents; EventIdx++)
    {
        rCHAR.ReadString();
        Loader.LoadEffectEvent(rCHAR);
    }

    // Read sound events
    const auto NumSoundEvents = rCHAR.ReadULong();
    for (uint32 EventIdx = 0; EventIdx < NumSoundEvents; EventIdx++)
    {
        rCHAR.ReadString();
        Loader.LoadSoundEvent(rCHAR);
    }

    return ptr;
}
