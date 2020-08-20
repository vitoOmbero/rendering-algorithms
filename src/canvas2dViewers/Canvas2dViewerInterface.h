#ifndef CANVAS2DVIEWERINTERFACE_H
#define CANVAS2DVIEWERINTERFACE_H

#include "PixelBuffer.h"

class Canvas2dViewerInterface
{
public:
    virtual void ViewResult(PixelBuffer& pb) = 0;
};

#endif // CANVAS2DVIEWERINTERFACE_H
