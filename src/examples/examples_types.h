#ifndef EXAMPLES_TYPES_H
#define EXAMPLES_TYPES_H
#include <memory>

#include "Canvas2d.h"
namespace ra_examples
{

/**
 * @brief canvas2d_example_ft - type for functions with client code using 2d
 * canvas
 */
typedef ra_core::pipeline::Canvas2d (*canvas2d_example_ft)(void);

} // namespace ra_examples
#endif // EXAMPLES_TYPES_H
