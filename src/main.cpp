#include <iostream>

#include "01_elemantary.h"
#include "02_shapes.h"
#include "03_clipping.h"
#include "04_transitions.h"
#include "05_shaders.h"
#include "example_runner.h"
#include "glut_viewer_simple.h"
#include "ppx_canvas2d_viewer.h"
#include "terminal_canvas2d_viewer.h"

int main(int argc, char* argv[])
{
    /*
        // TODO ? : orgaize example pack execution with CLI
    */
    std::cout << "Argc " << argc << std::endl;
    std::cout << "Argv " << argv << std::endl;
    /*
        {
            TerminalCanvas2dViewer               tViewer;
            ExampleRunner                        er(tViewer);
            ra_examples::cartesian2d::Elementary expack;
            er.Run(expack);
        }
*/
    {
        PpxCanvas2dViewer                    ppxViewer;
        ExampleRunner                        er(ppxViewer);
        ra_examples::cartesian2d::Elementary expack;
        er.Run(expack);
    }

    {
        PpxCanvas2dViewer                ppxViewer;
        ExampleRunner                    er(ppxViewer);
        ra_examples::cartesian2d::Shapes expack;
        er.Run(expack);
    }

    {
        PpxCanvas2dViewer                  ppxViewer;
        ExampleRunner                      er(ppxViewer);
        ra_examples::cartesian2d::Clipping expack;
        er.Run(expack);
    }

    {
        PpxCanvas2dViewer                     ppxViewer;
        ExampleRunner                         er(ppxViewer);
        ra_examples::cartesian2d::Transitions expack;
        er.Run(expack);
    }

    {
        PpxCanvas2dViewer                 ppxViewer;
        ExampleRunner                     er(ppxViewer);
        ra_examples::cartesian2d::Shaders expack;
        er.Run(expack);
    }

    if (argc > 1)
        return 0;
    {
        GlutViewerSimple                  glutViewer(argc, argv);
        ExampleRunner                     er_1(glutViewer);
        ra_examples::cartesian2d::Shaders expack_1;
        er_1.Run(expack_1);
        glutViewer.glutMainLoop(); // never return from this
    }
    return 0;
}
