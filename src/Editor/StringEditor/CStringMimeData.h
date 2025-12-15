#ifndef CSTRINGMIMEDATA_H
#define CSTRINGMIMEDATA_H

#include <QMimeData>
#include <QString>

#include <Common/CAssetID.h>
#include <cstdint>

/** Mime data encoding a reference to a string for drag&drop support in string editor */
class CStringMimeData : public QMimeData
{
    Q_OBJECT
    CAssetID mAssetID;
    uint32_t mStringIndex;

public:
    CStringMimeData(const CAssetID& AssetID, uint32_t StringIndex)
        : mAssetID(AssetID), mStringIndex(StringIndex)
    {}

    bool hasFormat(const QString& kMimeType) const override { return true; }

    const CAssetID& AssetID() const { return mAssetID; }
    uint32_t StringIndex() const { return mStringIndex; }
};

#endif // CSTRINGMIMEDATA_H
