#ifndef EXAMPLERUNNER_H
#define EXAMPLERUNNER_H

#include "Canvas2dViewerInterface.h"
#include "PixelBuffer.h"

class ExampleRunner
{
public:
    ExampleRunner();

    void UseCanvas2dViewer(Canvas2dViewerInterface& cv);
};

#endif // EXAMPLERUNNER_H
