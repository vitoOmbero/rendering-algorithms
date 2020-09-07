#include <iostream>

#include "01_Elemantary.h"
#include "02_Shapes.h"
#include "03_Clipping.h"
#include "ExampleRunner.h"
#include "PpxCanvas2dViewer.h"
#include "TerminalCanvas2dViewer.h"

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

    return 0;
}
