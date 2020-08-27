#ifndef ALGORITHM_REGISTRY_INC
#define ALGORITHM_REGISTRY_INC
/**
 * @brief The rendering_algorithm enum - static explicit definition of
 * supported rendering algorithmes
 */
enum rendering_algorithm
{
    custom,
    dot_naive,
    line_naive_hor_vert_diag,
    line_bresenham_defect,
    line_bresenham_int,
    circle_bresenham_int,
};

#endif // ALGORITHM_REGISTRY_INC
