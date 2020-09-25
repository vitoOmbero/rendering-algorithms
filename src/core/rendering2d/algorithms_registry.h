#ifndef ALGORITHMS_REGISTRY_H
#define ALGORITHMS_REGISTRY_H

namespace ra_core::rendering2d
{
enum class ClippingAlgorithm
{
    kCohenSutherland,
    kCyrusBeck,
};
enum class FillingAlgorithm
{
    kFill3NaiveHorizontal,
    kFill3LineSweepingPhase01,
    kFill3LineSweepingPhase02,
    kFill3LineSweeping,
};
enum class RenderingAlgorithm
{
    kCustom,
    kDotNaive,
    kLineNaiveHorVertDiag,
    kLineBresenhamDefect,
    kLineBresenhamInt,
    kCircleBresenhamInt,
};
}; // namespace ra_core::rendering2d

#endif // ALGORITHMS_REGISTRY_H
