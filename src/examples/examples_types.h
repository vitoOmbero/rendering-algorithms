#ifndef EXAMPLES_TYPES_H
#define EXAMPLES_TYPES_H
#include "RectangularPixelBuffer.h"
namespace ra_examples
{

/**
 * @brief canvas2d_example_ft - type for functions with client code using 2d
 * canvas
 */
typedef ra_core::canvas2d::RectangularPixelBuffer (*canvas2d_example_ft)(void);

} // namespace ra_examples
#endif // EXAMPLES_TYPES_H
