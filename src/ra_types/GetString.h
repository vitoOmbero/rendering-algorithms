#ifndef GETSTRING_H
#define GETSTRING_H

#include <sstream>
#include <string>

#include "Directions.h"
#include "RectangularPixelBuffer.h"
#include "displacement2d.h"

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
inline std::string_view GetString(const eDirection edir)
{
    switch (edir)
    {
        case eDirection::North:
            return "North";
        case eDirection::East:
            return "East";
        case eDirection::South:
            return "South";
        case eDirection::West:
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
 * @param pb - recatngular pixel buffer
 * @return pixel buffer string representation
 */
inline std::string GetString(
    const ra_core::canvas2d::RectangularPixelBuffer& pb)
{
    using namespace std;
    ostringstream oss;
    oss << "Output from DefaultCanvs2dViewer:" << endl;
    oss << "Using PixelBuffer: " << pb.GetName() << endl;
    oss << "Width: " << pb.GetWidth() << endl;
    oss << "Height: " << pb.GetHeight() << endl;
    oss << "Dot size in pixels: " << pb.GetDotSize() << endl;
    oss << "Dots total: " << pb.GetDotsNumber() << endl;
    oss << "0x view direction: " << ra_types::GetString(pb.GetXAxisDirection())
        << endl;
    oss << "0y view direction: " << ra_types::GetString(pb.GetYAxisDirection())
        << endl;
    oss << "Zero point offset: " << ra_types::GetString(pb.GetZeroPointOffset())
        << endl;
    return oss.str();
}

} // namespace ra_types

#endif // GETSTRING_H
