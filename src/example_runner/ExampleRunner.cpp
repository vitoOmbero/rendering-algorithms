#include "ExampleRunner.h"

ExampleRunner::ExampleRunner()
{
    
}

void ExampleRunner::UseCanvas2dViewer(Canvas2dViewerInterface& cv)
{
    auto pb = new PixelBuffer();
    cv.ViewResult(*pb);
    delete pb;
}
