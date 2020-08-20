#include <iostream>

#include "ExampleRunner.h"
#include "PpxCanvas2dViewer.h"

int main(int argc, char* argv[])
{
    ExampleRunner er;

    PpxCanvas2dViewer ppxViewer;

    er.UseCanvas2dViewer(ppxViewer);

    std::cout << "Argc " << argc << std::endl;
    std::cout << "Argv " << argv << std::endl;
    return 0;
}
