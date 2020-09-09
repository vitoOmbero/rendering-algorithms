#include "GlutViewerSimple.h"

#include "DEFAULT_PIPELINE_VALUES.h"
#include "ra_get_string.h"

GlutViewerSimple::GlutViewerSimple()
{
    
}

void GlutViewerSimple::ViewResult(const ra_core::pipeline::Canvas2d& canvas,
                                  const std::string_view description) const
{
    using namespace std;
    cout << endl;
    cout << "Current canvas 2d viewer provides only basic view." << endl;
    cout << "Do not resize windows." << endl;
    cout << std::string(50, '=') << endl;
    cout << description << endl;
    cout << ra_core::pipeline::GetString(canvas);
    cout << std::string(50, '=') << endl;
    cout << endl;
}

void GlutViewerSimple::glutMainLoop(int argc, char* argv[])
{
    auto wtests =
        visual_tests_glut_window<ra_core::renderer::CANVAS_WIDTH_PX,
                                 ra_core::renderer::CANVAS_HEIGHT_PX,
                                 ra_core::renderer::CANVAS_WIDTH_PX *
                                     ra_core::renderer::CANVAS_HEIGHT_PX>(argc,
                                                                          argv);
    // never return from this
    wtests.run();
}
