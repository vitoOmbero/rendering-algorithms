#ifndef GETSTRING_H
#define GETSTRING_H

#include <sstream>
#include <string>

#include "ra_types.h"

inline void line_formatting(std::ostringstream& oss, bool use_endl_separator)
{
    if (use_endl_separator)
        oss << std::endl;
    else
        oss << " ";
}

namespace ra_types
{

inline std::string GetString(const displacement1i_t d1i)
{
    std::ostringstream oss;
    oss << "displacement: " << d1i;
    return oss.str();
}

/**
 * @brief GetString - namespace free helping function overload
 * @param edir - sreenview related direction
 * @return readonly string representation
 */
inline std::string_view GetString(const eViewDirection2d edir)
{
    switch (edir)
    {
        case eViewDirection2d::North:
            return "North";
        case eViewDirection2d::East:
            return "East";
        case eViewDirection2d::South:
            return "South";
        case eViewDirection2d::West:
            return "West";
        default:
            return "No string is provided for eDirection";
    }
}

inline std::string_view GetString(const eDirection1d d1d)
{
    switch (d1d)
    {
        case eDirection1d::PosInf:
            return "+Inf";
        case eDirection1d::NegInf:
            return "-Inf";
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
inline std::string GetString(const displacement2i cp, bool oneline = false)
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
inline std::string GetString(const ra_types::point2i point, bool oneline = true)
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

inline std::string GetString(const Space1i space_do, bool oneline = true)
{
    std::ostringstream oss;
    line_formatting(oss, !oneline);
    oss << "Space1i {";

    line_formatting(oss, !oneline);
    oss << "ZPoffset :";
    oss << GetString(space_do.viewZeroPointOffset);

    line_formatting(oss, !oneline);
    oss << "Axis direction :";
    oss << GetString(space_do.directionOx);

    line_formatting(oss, !oneline);
    oss << "Length :";
    oss << space_do.viewLength;

    line_formatting(oss, !oneline);
    oss << "}";
    line_formatting(oss, !oneline);
    return oss.str();
}

inline std::string GetString(const Space2i space_do, bool oneline = true)
{
    std::ostringstream oss;
    line_formatting(oss, !oneline);
    oss << "Space2i {";
    line_formatting(oss, !oneline);

    oss << "ZPoffset :";
    oss << GetString(space_do.viewZeroPointOffset, oneline);
    line_formatting(oss, !oneline);

    oss << "0x direction: ";
    oss << GetString(space_do.directionOx);
    line_formatting(oss, !oneline);

    oss << "0y direction: ";
    oss << GetString(space_do.directionOy);
    line_formatting(oss, !oneline);

    oss << "Width : ";
    oss << space_do.viewWidth;
    line_formatting(oss, !oneline);

    oss << "Height : ";
    oss << space_do.viewHeight;
    line_formatting(oss, !oneline);

    line_formatting(oss, !oneline);
    oss << "}";
    line_formatting(oss, !oneline);
    return oss.str();
}

/**
 * @brief GetString - namespace free helping function overload
 * @param rgb - rgb888 color code
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

inline std::string_view GetString(const eColor ecol)
{
    switch (ecol)
    {
        case eColor::Black:
            return "Black";
        case eColor::White:
            return "White";
        case eColor::Navy:
            return "Navy";
        case eColor::Blue:
            return "Blue";
        case eColor::Green:
            return "Green";
        case eColor::Teal:
            return "Teal";
        case eColor::Blue_light:
            return "Blue_light";
        case eColor::Lime:
            return "Lime";
        case eColor::Green_springB:
            return "Green_springB";
        case eColor::Cyan:
            return "Cyan";
        case eColor::Indigo:
            return "Indigo";
        case eColor::Maroon:
            return "Maroon";
        case eColor::Purple:
            return "Purple";
        case eColor::Purple_blue:
            return "Purple_blue";
        case eColor::Olive:
            return "Olive";
        case eColor::Gray:
            return "Gray";
        case eColor::Sky_blue_dark:
            return "Sky_blue_dark";
        case eColor::Silver:
            return "Silver";
        case eColor::Violet:
            return "Violet";
        case eColor::Red:
            return "Red";
        case eColor::Fuchsia_dark:
            return "Fuchsia_dark";
        case eColor::Magenta:
            return "Magenta";
        case eColor::DarkOrange1B:
            return "DarkOrange1B";
        case eColor::Orange:
            return "Orange";
        case eColor::Coral_lightd:
            return "Coral_lightd";
        case eColor::Orchid1_l:
            return "Orchid1_l";
        case eColor::Yellow:
            return "Yellow";
        case eColor::Khaki1_l:
            return "Khaki1_l";
        case eColor::No:
            return "No (invisible color)";
        case eColor::Unnamed:
            return "Unnamed (enum null value)";
        case eColor::_FIRST_:
            return "_FIRST_ (enum iterator)";
        case eColor::_LAST_:
            return "_LAST_ (enum iterator)";
        default:
            return "No string is provided for current eColor";
            // TODO: add feature if ColorMap service is static
    }
}

} // namespace ra_types

#endif // GETSTRING_H
