#ifndef GETSTRING_H
#define GETSTRING_H

#include <sstream>
#include <string>

#include "Directions.h"
#include "RectangularPixelBuffer.h"
#include "displacement2d.h"
#include "point2d.h"
#include "rgb888.h"

inline void line_formatting(std::ostringstream& oss, bool use_endl_separator)
{
    if (use_endl_separator)
        oss << std::endl;
    else
        oss << " ";
}

namespace ra_types
{

/**
 * @brief GetString - namespace free helping function overload
 * @param edir - sreenview related direction
 * @return readonly string representation
 */
inline std::string_view GetString(const eScreenDirection edir)
{
    switch (edir)
    {
        case eScreenDirection::North:
            return "North";
        case eScreenDirection::East:
            return "East";
        case eScreenDirection::South:
            return "South";
        case eScreenDirection::West:
            return "West";
        default:
            return "No string is provided for eDirection";
    }
}

/**
 * @brief GetString - namespace free helping function overload
 * @param cp - 2d displacement
 * @param oneline - formatting flag (FALSE by default)
 * @return 2d displacement string representation
 */
inline std::string GetString(const displacement2d cp, bool oneline = false)
{
    std::ostringstream oss;
    line_formatting(oss, !oneline);
    oss << "0x displacement: " << cp.x;
    line_formatting(oss, !oneline);
    oss << "0y displacement: " << cp.y;
    line_formatting(oss, !oneline);
    return oss.str();
}

/**
 * @brief GetString - namespace free helping function overload
 * @param point - 2d point
 * @param oneline - formatting flag (TRUE by default)
 * @return 2d point string representation
 */
inline std::string GetString(const ra_core::figures2d::point2d point,
                             bool                              oneline = true)
{
    std::ostringstream oss;
    line_formatting(oss, !oneline);
    oss << "(";
    line_formatting(oss, !oneline);
    oss << point.x;
    line_formatting(oss, !oneline);

    if (oneline)
        oss << "; ";
    oss << point.y;
    line_formatting(oss, !oneline);
    oss << ")";
    line_formatting(oss, !oneline);
    return oss.str();
}

/**
 * @brief GetString - namespace free helping function overload
 * @param pb - recatngular pixel buffer
 * @return pixel buffer string representation
 */
inline std::string GetString(
    const ra_core::canvas2d::RectangularPixelBuffer& pb)
{
    using namespace std;
    ostringstream oss;
    oss << "Output from DefaultCanvs2dViewer:" << endl;
    oss << "Using PixelBuffer: " << pb.getName() << endl;
    oss << "Width, px: " << pb.getPxWidth() << endl;
    oss << "Height, px: " << pb.getPxHeight() << endl;
    oss << "Width, dt: " << pb.getDtWidth() << endl;
    oss << "Height, dt: " << pb.getDtHeight() << endl;
    oss << "Dot scale: " << pb.getBufferDotSize() << endl;

    oss << "0x view direction: " << ra_types::GetString(pb.getXAxisDirection())
        << endl;
    oss << "0y view direction: " << ra_types::GetString(pb.getYAxisDirection())
        << endl;
    oss << "Buffer last index: " << pb.getBufferLastIndex() << endl;
    oss << "Zero index: " << pb.getBufferZeroIndex() << endl;
    oss << "Zero point offset: " << ra_types::GetString(pb.getZeroPointOffset())
        << endl;
    oss << "Dots drawn total: " << pb.getBufferDotsNumber() << endl;
    oss << "Lowest visible point: "
        << ra_types::GetString(pb.getLowestVisiblePoint()) << endl;
    oss << "Highest visible point: "
        << ra_types::GetString(pb.getHighestVisiblePoint()) << endl;
    oss << "Buffer zero point index: " << pb.getBufferZeroPointIndex() << endl;
    return oss.str();
}

/**
 * @brief GetString - namespace free helping function overload
 * @param rgb - rgb888 coloe code
 * @return string
 */
inline std::string GetString(rgb888 rgb)
{
    using namespace std;
    ostringstream oss;
    oss << "{R:" << rgb.red() << "; G:" << rgb.green() << "; B:" << rgb.blue()
        << ";}";
    return oss.str();
}

} // namespace ra_types

#endif // GETSTRING_H
