#ifndef SRENDERABLEPTR_H
#define SRENDERABLEPTR_H

#include "ERenderCommand.h"
#include "IRenderable.h"
#include <Common/Math/CAABox.h>
#include <cstdint>

struct SRenderablePtr
{
    IRenderable *pRenderable;
    int32_t ComponentIndex;
    CAABox AABox;
    ERenderCommand Command;
};

#endif // SRENDERABLEPTR_H
