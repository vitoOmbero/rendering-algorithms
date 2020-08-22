#include <iostream>

#include "01_Elemantary.h"
#include "ExampleRunner.h"
#include "PpxCanvas2dViewer.h"

int main(int argc, char* argv[])
{
    ExampleRunner er;

    ra_examples::cartesian2d::Elementary expack;

    er.Run(expack);

    std::cout << "Argc " << argc << std::endl;
    std::cout << "Argv " << argv << std::endl;
    return 0;
}
