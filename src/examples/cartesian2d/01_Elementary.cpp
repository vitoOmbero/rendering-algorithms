#include "01_Elemantary.h"

// TODO: provide function name with compiler detection for every example
// (macros?)

ra_core::canvas2d::RectangularPixelBuffer example_draw_dot()
{

    // TODO: implement draw dot
    return ra_core::canvas2d::RectangularPixelBuffer();
}

namespace ra_examples
{

namespace cartesian2d
{

Elementary::Elementary()
{
    examples->push_back(example_draw_dot);
    names->push_back("example_draw_dot");
}

} // namespace cartesian2d

} // namespace ra_examples
