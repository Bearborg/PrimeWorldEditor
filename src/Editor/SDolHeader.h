#ifndef CDOLHEADER_H
#define CDOLHEADER_H

#include <Common/Log.h>
#include <Common/FileIO/IOutputStream.h>
#include <Common/FileIO/IInputStream.h>

class SDolHeader
{
public:
    static const size_t kNumTextSections = 7;
    static const size_t kNumDataSections = 11;
    static const size_t kNumSections = kNumTextSections + kNumDataSections;

    struct Section
    {
        uint32_t Offset;
        uint32_t BaseAddress;
        uint32_t Size;

        bool IsEmpty() const {
            return Size == 0;
        }
    };

    Section Sections[kNumSections];
    uint32_t BssAddress;
    uint32_t BssSize;
    uint32_t EntryPoint;

    explicit SDolHeader(IInputStream& rInput)
    {
        for (size_t i = 0; i < kNumSections; ++i)
        {
            Sections[i].Offset = rInput.ReadU32();
        }
        for (size_t i = 0; i < kNumSections; ++i)
        {
            Sections[i].BaseAddress = rInput.ReadU32();
        }
        for (size_t i = 0; i < kNumSections; ++i)
        {
            Sections[i].Size = rInput.ReadU32();
        }
        BssAddress = rInput.ReadU32();
        BssSize = rInput.ReadU32();
        EntryPoint = rInput.ReadU32();
    }

    void Write(IOutputStream& rOutput) const
    {
        for (size_t i = 0; i < kNumSections; ++i)
        {
            rOutput.WriteULong(Sections[i].Offset);
        }
        for (size_t i = 0; i < kNumSections; ++i)
        {
            rOutput.WriteULong(Sections[i].BaseAddress);
        }
        for (size_t i = 0; i < kNumSections; ++i)
        {
            rOutput.WriteULong(Sections[i].Size);
        }
        rOutput.WriteULong(BssAddress);
        rOutput.WriteULong(BssSize);
        rOutput.WriteULong(EntryPoint);
    }

    bool AddTextSection(uint32_t address, uint32_t fileOffset, uint32_t size)
    {
        if ((size & 0x1f) != 0)
        {
            NLog::Warn("Unable to add text section: Size not 32-bit aligned.");
            return false;
        }

        for (size_t i = 0; i < kNumTextSections; ++i)
        {
            if (Sections[i].IsEmpty())
            {
                Sections[i].BaseAddress = address;
                Sections[i].Offset = fileOffset;
                Sections[i].Size = size;
                return true;
            }
        }

        NLog::Warn("Unable to add text section: no empty section found.");
        return false;
    }

    uint32_t OffsetForAddress(uint32_t address) const
    {
        for (size_t i = 0; i < kNumSections; ++i)
        {
            const auto& sec = Sections[i];
            if (address > sec.BaseAddress && address < sec.BaseAddress + sec.Size)
            {
                return sec.Offset + (address - sec.BaseAddress);
            }
        }
        NLog::Warn("Unable to add section for address: {:x}", address);
        return 0;
    }
};

#endif // SDOLHEADER_H
