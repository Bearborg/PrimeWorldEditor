#ifndef CASSETID_H
#define CASSETID_H

#include "TString.h"
#include "types.h"
#include <FileIO/FileIO.h>

enum EIDLength
{
    e32Bit = 4,
    e64Bit = 8,
    eInvalidIDLength = 0
};

class CAssetID
{
    EIDLength mLength;
    u64 mID;

public:
    CAssetID();
    CAssetID(u64 ID);
    CAssetID(u64 ID, EIDLength Length);
    CAssetID(const char* pkID);
    CAssetID(IInputStream& rInput, EIDLength Length);
    TString ToString() const;
    bool IsValid() const;
\
    // Operators
    inline void operator=(const u64& rkInput)               { *this = CAssetID(rkInput); }
    inline void operator=(const char *pkInput)              { *this = CAssetID(pkInput); }
    inline bool operator==(const CAssetID& rkOther) const   { return mLength == rkOther.mLength && mID == rkOther.mID; }
    inline bool operator!=(const CAssetID& rkOther) const   { return mLength != rkOther.mLength || mID != rkOther.mID; }
    inline bool operator>(const CAssetID& rkOther) const    { return mID > rkOther.mID; }
    inline bool operator>=(const CAssetID& rkOther) const   { return mID >= rkOther.mID; }
    inline bool operator<(const CAssetID& rkOther) const    { return mID < rkOther.mID; }
    inline bool operator<=(const CAssetID& rkOther) const   { return mID <= rkOther.mID; }
    inline bool operator==(u64 Other) const                 { return mID == Other; }
    inline bool operator!=(u64 Other) const                 { return mID != Other; }

    // Accessors
    inline u32 ToLong() const               { return (u32) mID; }
    inline u64 ToLongLong() const           { return mID; }
    inline EIDLength Length() const         { return mLength; }
    inline void SetLength(EIDLength Length) { mLength = Length; }

    // Static
    static CAssetID FromString(const TString& rkString);
    static CAssetID RandomID();

    static CAssetID skInvalidID32;
    static CAssetID skInvalidID64;
};

#endif // CASSETID_H