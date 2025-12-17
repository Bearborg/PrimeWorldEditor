#ifndef CSKINLOADER_H
#define CSKINLOADER_H

#include <memory>

class CResourceEntry;
class CSkin;
class IInputStream;

class CSkinLoader
{
    CSkinLoader() = delete;

public:
    static std::unique_ptr<CSkin> LoadCSKR(IInputStream& rCSKR, CResourceEntry *pEntry);
};

#endif // CSKINLOADER_H
