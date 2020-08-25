#include "TerminalCanvas2dViewer.h"

TerminalCanvas2dViewer::TerminalCanvas2dViewer() {}

TerminalCanvas2dViewer::~TerminalCanvas2dViewer() {}

void TerminalCanvas2dViewer::ViewResult(
    const ra_core::canvas2d::RectangularPixelBuffer& pb,
    const std::string_view                           description) const
{
    using namespace std;
    cout << endl;
    cout << "Current canvas 2d viewer provides only basic information." << endl;
    cout << std::string(50, '=') << endl;
    cout << description << endl;
    cout << ra_types::GetString(pb);
    cout << std::string(50, '=') << endl;
    cout << endl;
}
