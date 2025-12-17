#ifndef CBOOLPROPERTY_H
#define CBOOLPROPERTY_H

#include "Core/Resource/Script/Property/IProperty.h"

class CBoolProperty : public TSerializeableTypedProperty<bool, EPropertyType::Bool>
{
    friend class IProperty;

protected:
    explicit CBoolProperty(EGame Game)
        : TSerializeableTypedProperty(Game)
    {}

public:
    void SerializeValue(void* pData, IArchive& Arc) override
    {
        Arc.SerializePrimitive(ValueRef(pData), 0);
    }

    TString ValueAsString(const void* pData) const override
    {
        return Value(pData) ? "true" : "false";
    }
};

#endif // CBOOLPROPERTY_H
