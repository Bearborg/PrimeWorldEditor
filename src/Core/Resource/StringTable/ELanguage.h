#ifndef ELANGUAGE_H
#define ELANGUAGE_H

#include <Common/CFourCC.h>
#include <Common/EnumReflection.h>

/** A language in the game's localization system */
enum class ELanguage
{
    // The original release of Metroid Prime only supported English
    English                 = FOURCC('ENGL'),
    // Support for these languages was added in the PAL version of Metroid Prime
    German                  = FOURCC('GERM'),
    French                  = FOURCC('FREN'),
    Spanish                 = FOURCC('SPAN'),
    Italian                 = FOURCC('ITAL'),
    Dutch                   = FOURCC('DUTC'), // Unused
    Japanese                = FOURCC('JAPN'),
    // The rest of these languages were added in Donkey Kong Country Returns
    SimplifiedChinese       = FOURCC('SCHN'), // Unused
    TraditionalChinese      = FOURCC('TCHN'), // Unused
    UKEnglish               = FOURCC('UKEN'),
    Korean                  = FOURCC('KORE'),
    NAFrench                = FOURCC('NAFR'),
    NASpanish               = FOURCC('NASP'),
    // Invalid
    Invalid                 = FOURCC('INVD')
};

template <>
const CEnumNameMap TEnumReflection<ELanguage>::skNameMap = {
    {1162757964, "English"},
    {1195725389, "German"},
    {1179796814, "French"},
    {1397768526, "Spanish"},
    {1230258508, "Italian"},
    {1146442819, "Dutch"},
    {1245794382, "Japanese"},
    {1396918350, "SimplifiedChinese"},
    {1413695566, "TraditionalChinese"},
    {1430996302, "UKEnglish"},
    {1263489605, "Korean"},
    {1312900690, "NAFrench"},
    {1312904016, "NASpanish"},
    {1229870660, "Invalid"},
};
template <>
const int TEnumReflection<ELanguage>::skErrorValue = 1229870660;

#endif // ELANGUAGE_H
