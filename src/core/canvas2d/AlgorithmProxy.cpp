#include <exception>

#include "AlgorithmProxy.h"
#include "algorithm_filling_3v_line_sweeping.h"
#include "algorithms_circle.h"
#include "algorithms_filling_naive.h"
#include "algorithms_line_classic.h"
#include "algorithms_lines_naive.h"

namespace ra_core::canvas2d
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

    rendering_fill3_map = ra_fill3_map{
        { rendering_algorithm::fill3_naive_horizontal,
          ra_core::rendering2d::filling::fill3_naive_hr },
        { rendering_algorithm::fill3_line_sweeping_phase_01,
          ra_core::rendering2d::filling::fill3_line_sweeping_phase01_sides },
        { rendering_algorithm::fill3_line_sweeping_phase_02,
          ra_core::rendering2d::filling::fill3_line_sweeping_phase02_sides },
        { rendering_algorithm::fill3_line_sweeping,
          ra_core::rendering2d::filling::fill3_line_sweeping }
    };
}

ra_core::rendering2d::rendering_dot_fptr AlgorithmProxy::getRenderingDot() const
{
    return renderingDot;
}

ra_core::rendering2d::rendering_line_segment_fptr
AlgorithmProxy::getRenderingLineSegment() const
{
    return renderingLineSegment;
}

bool AlgorithmProxy::setFillingAlgorithm(
    ra_core::figures2d::eFigure2dType figure2dType, rendering_algorithm ra)
{
    switch (figure2dType)
    {
        case (ra_core::figures2d::eFigure2dType::Triangle):
        {
            try
            {
                renderingTriangleFilled = rendering_fill3_map[ra];
                return true;
            }
            catch (std::exception e)
            {
                renderingTriangleFilled = rendering_fill3_map
                    [rendering_algorithm::fill3_naive_horizontal];
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
                renderingDot = rendering_dot_map[ra];
                return true;
            }
            catch (std::exception e)
            {
                renderingDot =
                    rendering_dot_map[rendering_algorithm::dot_naive];
                return false;
            }
        };
        case (ra_core::figures2d::eFigure2dType::Line):
        {
            try
            {
                renderingLineSegment = rendering_line_segment_map[ra];
                return true;
            }
            catch (std::exception e)
            {
                renderingLineSegment = rendering_line_segment_map
                    [rendering_algorithm::line_naive_hor_vert_diag];
                return false;
            }
        };
        case (ra_core::figures2d::eFigure2dType::Circle):
        {
            try
            {
                renderingCircle = rendering_circle_map[ra];
                return true;
            }
            catch (std::exception e)
            {
                renderingCircle = rendering_circle_map
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
                renderingDot = a;
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
                renderingLineSegment = a;
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
                renderingCircle = a;
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

bool AlgorithmProxy::IsValidRenderingAlgorithm()
{
    // TODO: add RenderingAlgorithmValidator (based on example running)
    return true;
}

ra_core::rendering2d::rendering_triangle_filling_fptr
AlgorithmProxy::getRenderingTriangleFilled() const
{
    return renderingTriangleFilled;
}

ra_core::rendering2d::rendering_circle_fptr AlgorithmProxy::getRenderingCircle() const
{
    return renderingCircle;
}
} // namespace ra_core::canvas2d
