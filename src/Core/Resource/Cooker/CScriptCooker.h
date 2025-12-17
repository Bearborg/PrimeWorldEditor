#ifndef CSCRIPTCOOKER_H
#define CSCRIPTCOOKER_H

#include <Common/EGame.h>
#include <vector>

class CScriptLayer;
class CScriptObject;
class IOutputStream;
class IProperty;

class CScriptCooker
{
    EGame mGame;
    std::vector<CScriptObject*> mGeneratedObjects;
    bool mWriteGeneratedSeparately;

public:
    explicit CScriptCooker(EGame Game, bool WriteGeneratedObjectsSeparately = true);
    ~CScriptCooker();

    void WriteProperty(IOutputStream& rOut, IProperty* pProperty, void* pData, bool InAtomicStruct);
    void WriteInstance(IOutputStream& rOut, CScriptObject *pInstance);
    void WriteLayer(IOutputStream& rOut, CScriptLayer *pLayer);
    void WriteGeneratedLayer(IOutputStream& rOut);
};

#endif // CSCRIPTCOOKER_H
