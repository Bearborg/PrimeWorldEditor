#ifndef CSOUNDPROPERTY_H
#define CSOUNDPROPERTY_H

#include "Core/Resource/Script/Property/IProperty.h"
#include <string>

class CSoundProperty : public TSerializeableTypedProperty<int32_t, EPropertyType::Sound>
{
    friend class IProperty;

protected:
    explicit CSoundProperty(EGame Game)
        : TSerializeableTypedProperty(Game)
    {}

public:
    void SerializeValue(void* pData, IArchive& Arc) override
    {
        Arc.SerializePrimitive(ValueRef(pData), 0);
    }

    TString ValueAsString(const void* pData) const override
    {
        return std::to_string(Value(pData));
    }
};

#endif // CSOUNDPROPERTY_H
