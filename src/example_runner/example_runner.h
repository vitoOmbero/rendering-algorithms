#ifndef EXAMPLERUNNER_H
#define EXAMPLERUNNER_H

#include <vector>

#include "canvas2d_viewer_interface.h"
#include "example_pack_base.h"
#include "examples_types.h"

/**
 * @brief The ExampleRunner class use Canvas2dViewer to produce viewable result
 * of example routines
 */

class ExampleRunner
{
public:
    explicit ExampleRunner(Canvas2dViewerInterface& cv);

    void UseCanvas2dViewer(Canvas2dViewerInterface& cv);

    /**
     * @brief Run - execute examples pipline
     * @param expack - pack of examples to be run
     */
    void Run(ra_examples::ExamplePackBase& expack);

private:
    Canvas2dViewerInterface& actual_canvas2d_viewer_;
};

#endif // EXAMPLERUNNER_H
