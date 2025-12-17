#ifndef CANIMATIONPROPERTY_H
#define CANIMATIONPROPERTY_H

#include "Core/Resource/Script/Property/IProperty.h"

class CAnimationProperty : public TSerializeableTypedProperty<uint32_t, EPropertyType::Animation>
{
    friend class IProperty;

protected:
    explicit CAnimationProperty(EGame Game)
        : TSerializeableTypedProperty(Game)
    {}

public:
    void SerializeValue(void* pData, IArchive& rArc) override
    {
        rArc.SerializePrimitive(ValueRef(pData), SH_HexDisplay);
    }

    TString ValueAsString(const void* pData) const override
    {
        return TString::HexString(Value(pData));
    }
};

#endif // CANIMATIONPROPERTY_H
