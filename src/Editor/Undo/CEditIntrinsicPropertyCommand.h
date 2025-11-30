#ifndef CEDITINTRINSICPROPERTYCOMMAND_H
#define CEDITINTRINSICPROPERTYCOMMAND_H

#include "IEditPropertyCommand.h"

class CEditIntrinsicPropertyCommand : public IEditPropertyCommand
{
protected:
    QList<void*> mDataPointers;

public:
    CEditIntrinsicPropertyCommand(IProperty* pProperty,
                                  const QList<void*>& kDataPointers,
                                  CPropertyModel* pModel,
                                  QModelIndex Index = QModelIndex(),
                                  const QString& kCommandName = "Edit Property")
        : IEditPropertyCommand(pProperty, pModel, Index, kCommandName)
        , mDataPointers(kDataPointers)
    {
    }

    void GetObjectDataPointers(QList<void*>& rOutPointers) const override
    {
        rOutPointers = mDataPointers;
    }
};

#endif // CEDITINTRINSICPROPERTYCOMMAND_H
