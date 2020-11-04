#ifndef EXAMPLES_TYPES_H
#define EXAMPLES_TYPES_H
#include <memory>

#include "canvas2d.h"
namespace ra_examples
{

/**
 * @brief Canvas2dExampleFunction - type for functions with client code using 2d
 * canvas
 */
typedef ra_core::pipeline::Canvas2d (*Canvas2dExampleFunction)();

} // namespace ra_examples
#endif // EXAMPLES_TYPES_H
