#ifndef CINTPROPERTY_H
#define CINTPROPERTY_H

#include "Core/Resource/Script/Property/IProperty.h"
#include <string>

class CIntProperty : public TNumericalProperty<int32_t, EPropertyType::Int>
{
    friend class IProperty;

protected:
    explicit CIntProperty(EGame Game)
        : TNumericalProperty(Game)
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

#endif // CINTPROPERTY_H
