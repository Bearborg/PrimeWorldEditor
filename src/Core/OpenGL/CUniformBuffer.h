#ifndef CUNIFORMBUFFER_H
#define CUNIFORMBUFFER_H

#include <Common/BasicTypes.h>
#include <GL/glew.h>

class CUniformBuffer
{
    GLuint mUniformBuffer;
    uint mBufferSize;

public:

    CUniformBuffer()
    {
        glGenBuffers(1, &mUniformBuffer);
        SetBufferSize(0);
    }

    CUniformBuffer(uint Size)
    {
        glGenBuffers(1, &mUniformBuffer);
        SetBufferSize(Size);
    }

    ~CUniformBuffer()
    {
        glDeleteBuffers(1, &mUniformBuffer);
    }

    void Bind()
    {
        glBindBuffer(GL_UNIFORM_BUFFER, mUniformBuffer);
    }

    void Unbind()
    {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void BindBase(GLuint Index)
    {
        Bind();
        glBindBufferBase(GL_UNIFORM_BUFFER, Index, mUniformBuffer);
        Unbind();
    }

    void Buffer(const void *pkData)
    {
        Bind();
        glBufferSubData(GL_UNIFORM_BUFFER, 0, mBufferSize, pkData);
        Unbind();
    }

    void BufferRange(const void *pkData, uint Offset, uint Size)
    {
        Bind();
        glBufferSubData(GL_UNIFORM_BUFFER, Offset, Size, pkData);
        Unbind();
    }

    void SetBufferSize(uint Size)
    {
        mBufferSize = Size;
        InitializeBuffer();
    }

    uint GetBufferSize()
    {
        return mBufferSize;
    }

private:
    void InitializeBuffer()
    {
        Bind();
        glBufferData(GL_UNIFORM_BUFFER, mBufferSize, 0, GL_DYNAMIC_DRAW);
        Unbind();
    }
};

#endif // CUNIFORMBUFFER_H
