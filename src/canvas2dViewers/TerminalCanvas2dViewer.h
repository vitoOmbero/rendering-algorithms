#ifndef DEFAULTCANVAS2DVIEWER_H
#define DEFAULTCANVAS2DVIEWER_H

#include <iostream>
#include <string>

#include "Canvas2dViewerInterface.h"
#include "GetString.h"
#include "RectangularPixelBuffer.h"
/**
 * @brief The TerminalCanvas2dViewer class prints some info about PixelBuffer
 * into stdout
 */
class TerminalCanvas2dViewer : public Canvas2dViewerInterface
{
public:
    TerminalCanvas2dViewer();
    ~TerminalCanvas2dViewer();

    void ViewResult(const ra_core::canvas2d::RectangularPixelBuffer& pb,
                    const std::string_view description) const override;
};

#endif // DEFAULTCANVAS2DVIEWER_H
