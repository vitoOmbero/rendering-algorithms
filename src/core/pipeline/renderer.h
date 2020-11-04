#ifndef RENDERINGPIPELLINE2D_H
#define RENDERINGPIPELLINE2D_H

#include "canvas2d.h"
#include "color_map.h"
#include "DEFAULT_PIPELINE_VALUES.h"
#include "drawable_interface.h"
#include "drawing_mode.h"
#include "matrix_calculator_simple.h"
#include "pipeline_targets.h"
#include "algorithms_registry.h"
#include "algorithms_types.h"

#include "ra_types.h"

/**
 * Singleton Facade in C++ way
 */
namespace ra_core::renderer
{

/**
 * @brief Init - initialize rendering pipeline with default values
 */
void Init();

/**
 * @brief Destroy - destroy rendering pipeline object
 */
void Destroy();

/**
 * @brief getColorMap
 * @return reference to color name conversion service
 */
const ra_services::color_rgb::ColorMap& getColorMap();

/**
 * @brief getMatrixCalculatorSimple
 * @return reference to stateful matrix calculation service
 */
ra_services::geometric_transformations_in_homogeneous_coordinates::
    MatrixCalculatorSimple&
    getMatrixCalculatorSimple();

/**
 * @brief Draw - try to draw supported object
 * @param drawable - something from ra_core::figures2d
 */
void Draw(const ra_core::figures2d::DrawableInterface& drawable);

/**
 * @brief setDrawingMode - allows to change drawing mode
 * @param mode - the default moe is Circuit.
 */
void setDrawingMode(pipeline::DrawingMode mode);

/**
 * @brief getCanvas
 * @return Canvas2d
 */
ra_core::pipeline::Canvas2d getCanvas();

/**
 * @brief setExportTarget
 * @param target - target buffer to be exported into canvas
 * @details Dot buffer is the default export target.
 */
void setExportTarget(pipeline::Target target);

/**
 * @brief setRenderingTarget
 * @param target - target buffer to apply rendering algorithms
 */
void setRenderingTarget(pipeline::Target target);

/**
 * @brief UseLineAlgorithm
 * @param algo_ptr - enum pointer to line rendering algorithm
 */
void UseLineAlgorithm(ra_core::rendering2d::RenderingAlgorithm kAlgo);

/**
 * @brief UseCircleAlgorithm
 * @param algo_ptr - enum pointer to circle rendering algorithm
 */
void UseCircleAlgorithm(ra_core::rendering2d::RenderingAlgorithm kAlgo);

/**
 * @brief UseFillingTriangle
 * @param algo_ptr - enum pointer to filling algorithm.
 * @details There are various filling algorithms which works with different
 * buffers. If nothing is set from client code, default settings are applied.
 */
void UseFillingTriangle(ra_core::rendering2d::FillingAlgorithm kAlgo);

/**
 * @brief UseCustomFillingTriangle
 * @param func_ptr - function with triangle filling algorithm
 */
void UseCustomFillingTriangle(
    ra_core::rendering2d::FillingTriangleFunction func_ptr);

/**
 * @brief UseClippingWindow - forces to use centered rectangular clipping window
 * @param offsetX - 0x offset for central point of the clipping window
 * @param offsetY -  0y offset for central point of the clipping window
 * @param algo_ptr - enum pointer to clipping algorithm
 * @details Pipline doesn't use clipping by default. Cutting is used implicitly
 * in buffers. Points from world's space are not drawn if they are out of
 * the buffer space.
 */
void UseClippingWindow(ra_types::n0_t offsetX, ra_types::n0_t offsetY,
                       ra_core::rendering2d::ClippingAlgorithm kAlgo);
/**
 * @brief UseNoClippingWindow - destroy clipping window if it is set
 */
void UseNoClippingWindow();

/**
 * @brief StumpCanvas - stump target buffer into canvas
 */
void StumpCanvas();

} // namespace ra_core::renderer

#endif // RENDERINGPIPELLINE2D_H
