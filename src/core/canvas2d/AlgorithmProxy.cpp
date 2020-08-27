#include <exception>

#include "AlgorithmProxy.h"
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

bool AlgorithmProxy::setRenderingAlgorithm(
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
                setRenderingAlgorithm(ra_core::figures2d::eFigure2dType::Dot,
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
                setRenderingAlgorithm(
                    ra_core::figures2d::eFigure2dType::Line,
                    rendering_algorithm::line_naive_hor_vert_diag);
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
} // namespace ra_core::canvas2d
