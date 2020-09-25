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
    rendering_dot_map_ = DotMap{ { RenderingAlgorithm::kDotNaive,
                                   ra_core::rendering2d::line::naive_dot } };
    rendering_line_segment_map_ =
        LineSegMap{ { RenderingAlgorithm::kLineNaiveHorVertDiag,
                      ra_core::rendering2d::line::naive_hv_line },
                    { RenderingAlgorithm::kLineBresenhamDefect,
                      ra_core::rendering2d::line::bresenham_defect_diag_line },
                    { RenderingAlgorithm::kLineBresenhamInt,
                      ra_core::rendering2d::line::bresenham_int_line } };
    rendering_circle_map_ =
        CircMap{ { RenderingAlgorithm::kCircleBresenhamInt,
                   ra_core::rendering2d::circuits::bresenham_int_circle } };

    fill3_map_ = Fill3Map{
        { FillingAlgorithm::kFill3NaiveHorizontal,
          ra_core::rendering2d::filling::fill3_naive_hr },
        { FillingAlgorithm::kFill3LineSweepingPhase01,
          ra_core::rendering2d::filling::fill3_line_sweeping_phase01_sides },
        { FillingAlgorithm::kFill3LineSweepingPhase02,
          ra_core::rendering2d::filling::fill3_line_sweeping_phase02_sides },
        { FillingAlgorithm::kFill3LineSweeping,
          ra_core::rendering2d::filling::fill3_line_sweeping }
    };

    clip_map_ = ClipMap{
        { ClippingAlgorithm::kCohenSutherland,
          ra_core::rendering2d::clipping::clipping_cohen_sutherland_int }
    };

    setRenderingCircuitAlgorithm(
        ra_core::figures2d::Figure2dType::kDot,
        ra_core::rendering2d::RenderingAlgorithm::kDotNaive);

    setRenderingCircuitAlgorithm(
        ra_core::figures2d::Figure2dType::kLine,
        ra_core::rendering2d::RenderingAlgorithm::kLineBresenhamInt);
    setRenderingCircuitAlgorithm(
        ra_core::figures2d::Figure2dType::kCircle,
        ra_core::rendering2d::RenderingAlgorithm::kCircleBresenhamInt);

    setFillingAlgorithm(
        ra_core::figures2d::Figure2dType::kTriangle,
        ra_core::rendering2d::FillingAlgorithm::kFill3LineSweeping);
}

ra_core::rendering2d::RenderingDotFunction AlgorithmProxy::getRenderDot() const
{
    return render_dot_func_;
}

ra_core::rendering2d::RenderingLineSegmentFunction
AlgorithmProxy::getRenderLineSegment() const
{
    return render_line_segment_func_;
}

bool AlgorithmProxy::setFillingAlgorithm(
    ra_core::figures2d::Figure2dType figure2d_type, FillingAlgorithm ca)
{
    switch (figure2d_type)
    {
        case (ra_core::figures2d::Figure2dType::kTriangle):
        {
            try
            {
                fill_triangle_func_ = fill3_map_[ca];
                return true;
            }
            catch (std::exception e)
            {
                fill_triangle_func_ =
                    fill3_map_[FillingAlgorithm::kFill3NaiveHorizontal];
                return false;
            }
        };
        default:
            return false;
    }
}

bool AlgorithmProxy::setRenderingCircuitAlgorithm(
    ra_core::figures2d::Figure2dType figure2d_type, RenderingAlgorithm ra)
{
    switch (figure2d_type)
    {
        case (ra_core::figures2d::Figure2dType::kDot):
        {
            try
            {
                render_dot_func_ = rendering_dot_map_[ra];
                return true;
            }
            catch (std::exception e)
            {
                render_dot_func_ =
                    rendering_dot_map_[RenderingAlgorithm::kDotNaive];
                return false;
            }
        };
        case (ra_core::figures2d::Figure2dType::kLine):
        {
            try
            {
                render_line_segment_func_ = rendering_line_segment_map_[ra];
                return true;
            }
            catch (std::exception e)
            {
                render_line_segment_func_ = rendering_line_segment_map_
                    [RenderingAlgorithm::kLineNaiveHorVertDiag];
                return false;
            }
        };
        case (ra_core::figures2d::Figure2dType::kCircle):
        {
            try
            {
                render_circle_func_ = rendering_circle_map_[ra];
                return true;
            }
            catch (std::exception e)
            {
                render_circle_func_ = rendering_circle_map_
                    [RenderingAlgorithm::kCircleBresenhamInt];
                return false;
            }
        };
        default:
            return false;
    }
}

bool AlgorithmProxy::setCustomRenderingAlgorithm(
    ra_core::figures2d::Figure2dType figure2d_type, void* function_ptr)
{
    switch (figure2d_type)
    {
        case (ra_core::figures2d::Figure2dType::kDot):
        {
            auto a =
                reinterpret_cast<ra_core::rendering2d::RenderingDotFunction>(
                    function_ptr);
            if (IsValidRenderingAlgorithm())
            {
                render_dot_func_ = a;
                return true;
            }

            else
            {
                setRenderingCircuitAlgorithm(
                    ra_core::figures2d::Figure2dType::kDot,
                    RenderingAlgorithm::kDotNaive);
                return false;
            }
        };
        case (ra_core::figures2d::Figure2dType::kLine):
        {
            auto a = reinterpret_cast<
                ra_core::rendering2d::RenderingLineSegmentFunction>(
                function_ptr);
            if (IsValidRenderingAlgorithm())
            {
                render_line_segment_func_ = a;
                return true;
            }
            else
            {
                setRenderingCircuitAlgorithm(
                    ra_core::figures2d::Figure2dType::kLine,
                    RenderingAlgorithm::kLineNaiveHorVertDiag);
                return false;
            }
        };
        case (ra_core::figures2d::Figure2dType::kCircle):
        {
            auto a =
                reinterpret_cast<ra_core::rendering2d::RenderingCircleFunction>(
                    function_ptr);
            if (IsValidRenderingAlgorithm())
            {
                render_circle_func_ = a;
                return true;
            }
            else
            {
                setRenderingCircuitAlgorithm(
                    ra_core::figures2d::Figure2dType::kCircle,
                    RenderingAlgorithm::kCircleBresenhamInt);
                return false;
            }
        };
        default:
            return false;
    }
}

bool AlgorithmProxy::setCustomFillingAlgorithm(
    figures2d::Figure2dType figure2d_type, void* function_ptr)
{
    switch (figure2d_type)
    {
        case (ra_core::figures2d::Figure2dType::kTriangle):
        {
            auto a =
                reinterpret_cast<ra_core::rendering2d::FillingTriangleFunction>(
                    function_ptr);
            if (IsValidRenderingAlgorithm())
            {
                fill_triangle_func_ = a;
                return true;
            }

            else
            {
                setFillingAlgorithm(ra_core::figures2d::Figure2dType::kTriangle,
                                    FillingAlgorithm::kFill3LineSweeping);
                return false;
            }
        };
        default:
            return false;
    }
}

bool AlgorithmProxy::setClippingAlgorithm(ClippingAlgorithm ca)
{
    try
    {
        clip_rectangular_func_ = clip_map_[ca];
        return true;
    }
    catch (std::exception e)
    {
        clip_rectangular_func_ = clip_map_[ClippingAlgorithm::kCohenSutherland];
        return false;
    }
}

bool AlgorithmProxy::IsValidRenderingAlgorithm()
{
    // TODO: public method & add RenderingAlgorithmValidator (based on pipeleine
    // running)
    return true;
}

ra_core::rendering2d::ClippingLineFunction AlgorithmProxy::getClipRectangular()
    const
{
    return clip_rectangular_func_;
}

ra_core::rendering2d::FillingTriangleFunction AlgorithmProxy::getFillTriangle()
    const
{
    return fill_triangle_func_;
}

ra_core::rendering2d::RenderingCircleFunction AlgorithmProxy::getRenderCircle()
    const
{
    return render_circle_func_;
}
} // namespace ra_core::canvas2d
