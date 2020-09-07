#ifndef ALGORITHMS_REGISTRY_H
#define ALGORITHMS_REGISTRY_H

namespace ra_core::rendering2d
{
enum class clipping_algorithm
{
    cohen_sutherland,
    cyrus_beck,
};
enum class filling_algorithm
{
    fill3_naive_horizontal,
    fill3_line_sweeping_phase_01,
    fill3_line_sweeping_phase_02,
    fill3_line_sweeping,
};
enum class rendering_algorithm
{
    custom,
    dot_naive,
    line_naive_hor_vert_diag,
    line_bresenham_defect,
    line_bresenham_int,
    circle_bresenham_int,
};
}; // namespace ra_core::rendering2d

#endif // ALGORITHMS_REGISTRY_H
