#include "Core/Resource/Factory/CPoiToWorldLoader.h"

#include "Core/Resource/CPoiToWorld.h"
#include <Common/FileIO/IInputStream.h>

std::unique_ptr<CPoiToWorld> CPoiToWorldLoader::LoadEGMC(IInputStream& rEGMC, CResourceEntry *pEntry)
{
    auto pOut = std::make_unique<CPoiToWorld>(pEntry);
    const auto NumMappings = rEGMC.ReadU32();

    for (uint32_t iMap = 0; iMap < NumMappings; iMap++)
    {
        const auto MeshID = rEGMC.ReadU32();
        const auto InstanceID = CInstanceID(rEGMC.ReadU32() & 0x03FFFFFF);
        pOut->AddPoiMeshMap(InstanceID, MeshID);
    }

    return pOut;
}
