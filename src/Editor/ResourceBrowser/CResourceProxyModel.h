#ifndef CRESOURCEPROXYMODEL
#define CRESOURCEPROXYMODEL

#include <Common/TString.h>
#include <Core/GameProject/CResourceEntry.h>
#include <Core/GameProject/CVirtualDirectory.h>
#include <Core/Resource/CResTypeInfo.h>
#include "Editor/ResourceBrowser/CResourceTableModel.h"

#include <QSortFilterProxyModel>

class CResourceProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    enum class ESortMode
    {
        ByName, BySize
    };

    explicit CResourceProxyModel(QObject* parent = nullptr);
    ~CResourceProxyModel() override;

    void setSourceModel(QAbstractItemModel* pSourceModel) override;
    bool lessThan(const QModelIndex& rkLeft, const QModelIndex& rkRight) const override;
    bool filterAcceptsRow(int SourceRow, const QModelIndex& rkSourceParent) const override;

    void SetTypeFilter(CResTypeInfo *pInfo, bool Allow);
    void ClearTypeFilter() { mTypeFilter.clear(); }
    bool HasTypeFilter() const { return !mTypeFilter.isEmpty(); }
    bool IsTypeAccepted(CResTypeInfo* pTypeInfo) const;

    void SetSortMode(ESortMode Mode);

public slots:
    void SetSearchString(const TString& rkString);

private:
    CResourceTableModel *mpModel = nullptr;
    TString mSearchString;
    ESortMode mSortMode{};
    QSet<CResTypeInfo*> mTypeFilter;

    uint64 mCompareID = 0;
    uint64 mCompareMask = 0;
    uint32 mCompareBitLength = 0;
};

#endif // CRESOURCEPROXYMODEL

