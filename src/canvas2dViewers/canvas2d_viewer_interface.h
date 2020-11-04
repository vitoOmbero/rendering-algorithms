#ifndef CANVAS2DVIEWERINTERFACE_H
#define CANVAS2DVIEWERINTERFACE_H

#include <string>

#include "canvas2d.h"
#include "ra_types.h"

class Canvas2dViewerInterface
{
public:
    virtual ~Canvas2dViewerInterface()                          = default;
    virtual void ViewResult(const ra_core::pipeline::Canvas2d& canvas,
                            std::string_view description) const = 0;
};

#endif // CANVAS2DVIEWERINTERFACE_H
