#ifndef CPOINTERPROPERTY_H
#define CPOINTERPROPERTY_H

#include "Core/Resource/Script/Property/IProperty.h"

class CPointerProperty : public TTypedProperty<void*, EPropertyType::Pointer>
{
    friend class IProperty;

    explicit CPointerProperty(EGame Game)
        : TTypedProperty(Game)
    {}

public:
    bool IsPointerType() const override
    {
        return true;
    }

    void* GetChildDataPointer(void* pPropertyData) override
    {
        return ValueRef(pPropertyData);
    }
    const void* GetChildDataPointer(const void* pPropertyData) const override
    {
        return ValueRef(pPropertyData);
    }

    void SerializeValue(void*, IArchive&)  override
    {
        // pointers are not serializable, this shouldn't happen
        ASSERT(false);
    }
};

#endif // CPOINTERPROPERTY_H
