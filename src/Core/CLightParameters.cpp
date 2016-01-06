#include "CLightParameters.h"

CLightParameters::CLightParameters(CPropertyStruct *pStruct, EGame game)
    : mpStruct(pStruct), mGame(game)
{
}

CLightParameters::~CLightParameters()
{
}

int CLightParameters::LightLayerIndex()
{
    if (!mpStruct) return 0;

    TLongProperty *pParam;

    if (mGame <= ePrime)
        pParam = (TLongProperty*) mpStruct->PropertyByIndex(0xD);
    else
        pParam = (TLongProperty*) mpStruct->PropertyByID(0x1F715FD3);

    if (!pParam) return 0;
    else return pParam->Get();
}