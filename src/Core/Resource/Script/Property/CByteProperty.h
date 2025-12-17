#ifndef CBYTEPROPERTY_H
#define CBYTEPROPERTY_H

#include "Core/Resource/Script/Property/IProperty.h"

class CByteProperty : public TNumericalProperty<int8_t, EPropertyType::Byte>
{
    friend class IProperty;

protected:
    explicit CByteProperty(EGame Game)
        : TNumericalProperty(Game)
    {}

public:
    void SerializeValue(void* pData, IArchive& Arc) override
    {
        Arc.SerializePrimitive(ValueRef(pData), 0);
    }

    TString ValueAsString(const void* pData) const override
    {
        return TString::FromInt32(Value(pData), 0, 10);
    }
};

#endif // CBYTEPROPERTY_H
