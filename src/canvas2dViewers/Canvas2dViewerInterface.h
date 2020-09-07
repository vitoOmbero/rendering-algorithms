#ifndef CANVAS2DVIEWERINTERFACE_H
#define CANVAS2DVIEWERINTERFACE_H

#include <string>

#include "Canvas2d.h"
#include "ra_types.h"

class Canvas2dViewerInterface
{
public:
    virtual ~Canvas2dViewerInterface(){};
    virtual void ViewResult(const ra_core::pipeline::Canvas2d& canvas,
                            const std::string_view description) const = 0;
};

#endif // CANVAS2DVIEWERINTERFACE_H
