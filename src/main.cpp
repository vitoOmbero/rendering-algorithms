#include <iostream>

#include "01_Elemantary.h"
#include "ExampleRunner.h"
#include "PpxCanvas2dViewer.h"
#include "TerminalCanvas2dViewer.h"

int main(int argc, char* argv[])
{
    TerminalCanvas2dViewer tViewer;
    ExampleRunner          er(tViewer);

    ra_examples::cartesian2d::Elementary expack;

    er.Run(expack);

    PpxCanvas2dViewer ppxViewer;
    ExampleRunner     er2(ppxViewer);

    er2.Run(expack);

    std::cout << "Argc " << argc << std::endl;
    std::cout << "Argv " << argv << std::endl;

    return 0;
}
