#ifndef CGAMEINFO
#define CGAMEINFO

#include <Common/CAssetID.h>
#include <Common/EGame.h>
#include <Common/TString.h>

#include <map>
#include <vector>

class IArchive;

//@todo merge this class into CGameTemplate
// they serve similar purposes, no real reason for them to be different classes
class CGameInfo
{
    EGame mGame{EGame::Invalid};

    // List of known builds of each game
    struct SBuildInfo;
    std::vector<SBuildInfo> mBuilds;

    // List of internal area names; used for MP1 which doesn't store area names in the MLVL
    std::map<CAssetID, TString> mAreaNameMap;

public:
    CGameInfo();
    ~CGameInfo();

    bool LoadGameInfo(EGame Game);
    bool LoadGameInfo(const TString& Path);
    bool SaveGameInfo(TString Path = "");
    void Serialize(IArchive& rArc);

    TString GetBuildName(float BuildVer, ERegion Region) const;
    TString GetAreaName(const CAssetID& rkID) const;

    // Accessors
    EGame Game() const { return mGame; }

    // Static
    static EGame RoundGame(EGame Game);
    static TString GetDefaultGameInfoPath(EGame Game);

    static TString GetExtension();
};

#endif // CGAMEINFO

