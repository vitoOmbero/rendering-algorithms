#ifndef FIGURES2DREGISTRY_H
#define FIGURES2DREGISTRY_H

namespace ra_core::figures2d
{

/**
 * @brief The eFigure2dType enum - static explicit definition of supported
 * figures2d types
 * @details Showcase provides number of rendering algorithms, which can be drawn
 * in diferrent ways
 */
enum class Figure2dType
{
    kDot,
    kLine,
    kCircle,
    kTriangle,
};

} // namespace ra_core::figures2d

#endif // FIGURES2DREGISTRY_H
