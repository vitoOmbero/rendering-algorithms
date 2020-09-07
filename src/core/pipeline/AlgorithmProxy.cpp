#include <exception>

#include "AlgorithmProxy.h"
#include "algorithm_clipping_cohen_sutherland_int.h"
#include "algorithm_filling_3v_line_sweeping.h"
#include "algorithms_circle.h"
#include "algorithms_filling_naive.h"
#include "algorithms_line_classic.h"
#include "algorithms_lines_naive.h"

namespace ra_core::pipeline
{

AlgorithmProxy::AlgorithmProxy()
{
    rendering_dot_map = ra_dot_map{ { rendering_algorithm::dot_naive,
                                      ra_core::rendering2d::line::naive_dot } };
    rendering_line_segment_map =
        ra_ls_map{ { rendering_algorithm::line_naive_hor_vert_diag,
                     ra_core::rendering2d::line::naive_hv_line },
                   { rendering_algorithm::line_bresenham_defect,
                     ra_core::rendering2d::line::bresenham_defect_diag_line },
                   { rendering_algorithm::line_bresenham_int,
                     ra_core::rendering2d::line::bresenham_int_line } };
    rendering_circle_map =
        ra_cir_map{ { rendering_algorithm::circle_bresenham_int,
                      ra_core::rendering2d::circuits::bresenham_int_circle } };

    fill3_map = ra_fill3_map{
        { filling_algorithm::fill3_naive_horizontal,
          ra_core::rendering2d::filling::fill3_naive_hr },
        { filling_algorithm::fill3_line_sweeping_phase_01,
          ra_core::rendering2d::filling::fill3_line_sweeping_phase01_sides },
        { filling_algorithm::fill3_line_sweeping_phase_02,
          ra_core::rendering2d::filling::fill3_line_sweeping_phase02_sides },
        { filling_algorithm::fill3_line_sweeping,
          ra_core::rendering2d::filling::fill3_line_sweeping }
    };

    clip_map = ra_clip_map{
        { clipping_algorithm::cohen_sutherland,
          ra_core::rendering2d::clipping::clipping_cohen_sutherland_int }
    };

    setRenderingCircuitAlgorithm(
        ra_core::figures2d::eFigure2dType::Dot,
        ra_core::rendering2d::rendering_algorithm::dot_naive);

    setRenderingCircuitAlgorithm(
        ra_core::figures2d::eFigure2dType::Line,
        ra_core::rendering2d::rendering_algorithm::line_bresenham_int);
    setRenderingCircuitAlgorithm(
        ra_core::figures2d::eFigure2dType::Circle,
        ra_core::rendering2d::rendering_algorithm::circle_bresenham_int);

    setFillingAlgorithm(
        ra_core::figures2d::eFigure2dType::Triangle,
        ra_core::rendering2d::filling_algorithm::fill3_line_sweeping);
}

ra_core::rendering2d::rendering_dot_fptr AlgorithmProxy::getRenderDot() const
{
    return renderDot;
}

ra_core::rendering2d::rendering_line_segment_fptr
AlgorithmProxy::getRenderLineSegment() const
{
    return renderLineSegment;
}

bool AlgorithmProxy::setFillingAlgorithm(
    ra_core::figures2d::eFigure2dType figure2dType, filling_algorithm ca)
{
    switch (figure2dType)
    {
        case (ra_core::figures2d::eFigure2dType::Triangle):
        {
            try
            {
                fillTriangle = fill3_map[ca];
                return true;
            }
            catch (std::exception e)
            {
                fillTriangle =
                    fill3_map[filling_algorithm::fill3_naive_horizontal];
                return false;
            }
        };
        default:
            return false;
    }
}

bool AlgorithmProxy::setRenderingCircuitAlgorithm(
    ra_core::figures2d::eFigure2dType figure2dType, rendering_algorithm ra)
{
    switch (figure2dType)
    {
        case (ra_core::figures2d::eFigure2dType::Dot):
        {
            try
            {
                renderDot = rendering_dot_map[ra];
                return true;
            }
            catch (std::exception e)
            {
                renderDot = rendering_dot_map[rendering_algorithm::dot_naive];
                return false;
            }
        };
        case (ra_core::figures2d::eFigure2dType::Line):
        {
            try
            {
                renderLineSegment = rendering_line_segment_map[ra];
                return true;
            }
            catch (std::exception e)
            {
                renderLineSegment = rendering_line_segment_map
                    [rendering_algorithm::line_naive_hor_vert_diag];
                return false;
            }
        };
        case (ra_core::figures2d::eFigure2dType::Circle):
        {
            try
            {
                renderCircle = rendering_circle_map[ra];
                return true;
            }
            catch (std::exception e)
            {
                renderCircle = rendering_circle_map
                    [rendering_algorithm::circle_bresenham_int];
                return false;
            }
        };
        default:
            return false;
    }
}

bool AlgorithmProxy::setCustomRenderingAlgorithm(
    ra_core::figures2d::eFigure2dType figure2dType, void* function_ptr)
{
    switch (figure2dType)
    {
        case (ra_core::figures2d::eFigure2dType::Dot):
        {
            auto a = reinterpret_cast<ra_core::rendering2d::rendering_dot_fptr>(
                function_ptr);
            if (IsValidRenderingAlgorithm())
            {
                renderDot = a;
                return true;
            }

            else
            {
                setRenderingCircuitAlgorithm(
                    ra_core::figures2d::eFigure2dType::Dot,
                    rendering_algorithm::dot_naive);
                return false;
            }
        };
        case (ra_core::figures2d::eFigure2dType::Line):
        {
            auto a = reinterpret_cast<
                ra_core::rendering2d::rendering_line_segment_fptr>(
                function_ptr);
            if (IsValidRenderingAlgorithm())
            {
                renderLineSegment = a;
                return true;
            }
            else
            {
                setRenderingCircuitAlgorithm(
                    ra_core::figures2d::eFigure2dType::Line,
                    rendering_algorithm::line_naive_hor_vert_diag);
                return false;
            }
        };
        case (ra_core::figures2d::eFigure2dType::Circle):
        {
            auto a =
                reinterpret_cast<ra_core::rendering2d::rendering_circle_fptr>(
                    function_ptr);
            if (IsValidRenderingAlgorithm())
            {
                renderCircle = a;
                return true;
            }
            else
            {
                setRenderingCircuitAlgorithm(
                    ra_core::figures2d::eFigure2dType::Circle,
                    rendering_algorithm::circle_bresenham_int);
                return false;
            }
        };
        default:
            return false;
    }
}

bool AlgorithmProxy::setClippingAlgorithm(clipping_algorithm ca)
{
    try
    {
        clipRectangular = clip_map[ca];
        return true;
    }
    catch (std::exception e)
    {
        clipRectangular = clip_map[clipping_algorithm::cohen_sutherland];
        return false;
    }
}

bool AlgorithmProxy::IsValidRenderingAlgorithm()
{
    // TODO: public method & add RenderingAlgorithmValidator (based on pipeleine
    // running)
    return true;
}

ra_core::rendering2d::clipping_line_fptr AlgorithmProxy::getClipRectangular()
    const
{
    return clipRectangular;
}

ra_core::rendering2d::filling_triangle_fptr AlgorithmProxy::getFillTriangle()
    const
{
    return fillTriangle;
}

ra_core::rendering2d::rendering_circle_fptr AlgorithmProxy::getRenderCircle()
    const
{
    return renderCircle;
}
} // namespace ra_core::canvas2d
