#include "Core/Resource/Cooker/CTextureEncoder.h"

#include "Core/Resource/CTexture.h"

#include <Common/Log.h>
#include <Common/FileIO/CMemoryInStream.h>

CTextureEncoder::CTextureEncoder() = default;
CTextureEncoder::~CTextureEncoder() = default;

void CTextureEncoder::WriteTXTR(IOutputStream& rTXTR)
{
    // Only DXT1->CMPR supported at the moment
    rTXTR.WriteU32(static_cast<uint32_t>(mOutputFormat));
    rTXTR.WriteU16(mpTexture->mWidth);
    rTXTR.WriteU16(mpTexture->mHeight);
    rTXTR.WriteU32(mpTexture->mNumMipMaps);

    uint32_t MipW = mpTexture->Width() / 4;
    uint32_t MipH = mpTexture->Height() / 4;
    CMemoryInStream Image(mpTexture->mpImgDataBuffer.get(), mpTexture->mImgDataSize, std::endian::little);
    uint32_t MipOffset = Image.Tell();

    for (uint32_t iMip = 0; iMip < mpTexture->mNumMipMaps; iMip++)
    {
        for (uint32_t iBlockY = 0; iBlockY < MipH; iBlockY += 2)
        {
            for (uint32_t iBlockX = 0; iBlockX < MipW; iBlockX += 2)
            {
                for (uint32_t iImgY = iBlockY; iImgY < iBlockY + 2; iImgY++)
                {
                    for (uint32_t iImgX = iBlockX; iImgX < iBlockX + 2; iImgX++)
                    {
                        uint32_t SrcPos = ((iImgY * MipW) + iImgX) * 8;
                        Image.Seek(MipOffset + SrcPos, SEEK_SET);

                        ReadSubBlockCMPR(Image, rTXTR);
                    }
                }
            }
        }

        MipOffset += MipW * MipH * 8;
        MipW /= 2;
        MipH /= 2;

        if (MipW < 2)
            MipW = 2;

        if (MipH < 2)
            MipH = 2;
    }
}

void CTextureEncoder::DetermineBestOutputFormat()
{
    // todo
}

void CTextureEncoder::ReadSubBlockCMPR(IInputStream& rSource, IOutputStream& rDest)
{
    rDest.WriteS16(rSource.ReadS16());
    rDest.WriteS16(rSource.ReadS16());

    for (uint32_t iByte = 0; iByte < 4; iByte++)
    {
        uint8_t Byte = rSource.ReadU8();
        Byte = ((Byte & 0x3) << 6) | ((Byte & 0xC) << 2) | ((Byte & 0x30) >> 2) | ((Byte & 0xC0) >> 6);
        rDest.WriteU8(Byte);
    }
}

// ************ STATIC ************
void CTextureEncoder::EncodeTXTR(IOutputStream& rTXTR, CTexture *pTex)
{
    if (pTex->mTexelFormat != ETexelFormat::DXT1)
    {
        NLog::Error("Unsupported texel format for decoding");
        return;
    }

    CTextureEncoder Encoder;
    Encoder.mpTexture = pTex;
    Encoder.mSourceFormat = ETexelFormat::DXT1;
    Encoder.mOutputFormat = ETexelFormat::GX_CMPR;
    Encoder.WriteTXTR(rTXTR);
}

void CTextureEncoder::EncodeTXTR(IOutputStream& rTXTR, CTexture *pTex, ETexelFormat /*OutputFormat*/)
{
    // todo: support for encoding a specific format
    EncodeTXTR(rTXTR, pTex);
}

ETexelFormat CTextureEncoder::GetGXFormat(ETexelFormat Format)
{
    switch (Format)
    {
    case ETexelFormat::Luminance:       return ETexelFormat::GX_I8;
    case ETexelFormat::LuminanceAlpha:  return ETexelFormat::GX_IA8;
    case ETexelFormat::RGBA4:           return ETexelFormat::GX_RGB5A3;
    case ETexelFormat::RGB565:          return ETexelFormat::GX_RGB565;
    case ETexelFormat::RGBA8:           return ETexelFormat::GX_RGBA8;
    case ETexelFormat::DXT1:            return ETexelFormat::GX_CMPR;
    default:                            return ETexelFormat::Invalid;
    }
}

ETexelFormat CTextureEncoder::GetFormat(ETexelFormat Format)
{
    switch (Format)
    {
    case ETexelFormat::GX_I4:   return ETexelFormat::Luminance;
    case ETexelFormat::GX_I8:   return ETexelFormat::Luminance;
    case ETexelFormat::GX_IA4:  return ETexelFormat::LuminanceAlpha;
    case ETexelFormat::GX_IA8:  return ETexelFormat::LuminanceAlpha;
        // todo rest of these
    case ETexelFormat::GX_CMPR: return ETexelFormat::DXT1;
    default:                    return ETexelFormat::Invalid;
    }
}
