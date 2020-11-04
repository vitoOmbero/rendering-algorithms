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
inline std::string_view GetString(const ViewDirection2d edir)
{
    switch (edir)
    {
        case ViewDirection2d::kNorth:
            return "North";
        case ViewDirection2d::kEast:
            return "East";
        case ViewDirection2d::kSouth:
            return "South";
        case ViewDirection2d::kWest:
            return "West";
        default:
            return "No string is provided for eDirection";
    }
}

inline std::string_view GetString(const Direction1d d1d)
{
    switch (d1d)
    {
        case Direction1d::kPosInf:
            return "+Inf";
        case Direction1d::kNegInf:
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
inline std::string GetString(const ra_types::Point2i point, bool oneline = true)
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
inline std::string GetString(Rgb888 rgb)
{
    using namespace std;
    ostringstream oss;
    oss << "{R:" << rgb.red() << "; G:" << rgb.green() << "; B:" << rgb.blue()
        << ";}";
    return oss.str();
}

inline std::string_view GetString(const Color ecol)
{
    switch (ecol)
    {
        case Color::kBlack:
            return "Black";
        case Color::kWhite:
            return "White";
        case Color::kNavy:
            return "Navy";
        case Color::kBlue:
            return "Blue";
        case Color::kGreen:
            return "Green";
        case Color::kTeal:
            return "Teal";
        case Color::kBlueLight:
            return "Blue_light";
        case Color::kLime:
            return "Lime";
        case Color::kGreenSpringB:
            return "Green_springB";
        case Color::kCyan:
            return "Cyan";
        case Color::kIndigo:
            return "Indigo";
        case Color::kMaroon:
            return "Maroon";
        case Color::kPurple:
            return "Purple";
        case Color::kPurpleBlue:
            return "Purple_blue";
        case Color::kOlive:
            return "Olive";
        case Color::kGray:
            return "Gray";
        case Color::kSkyBlueDark:
            return "Sky_blue_dark";
        case Color::kSilver:
            return "Silver";
        case Color::kViolet:
            return "Violet";
        case Color::kRed:
            return "Red";
        case Color::kFuchsiaDark:
            return "Fuchsia_dark";
        case Color::kMagenta:
            return "Magenta";
        case Color::kDarkOrange1B:
            return "DarkOrange1B";
        case Color::kOrange:
            return "Orange";
        case Color::kCoralLightD:
            return "Coral_lightd";
        case Color::kOrchid1L:
            return "Orchid1_l";
        case Color::kYellow:
            return "Yellow";
        case Color::kKhaki1L:
            return "Khaki1_l";
        case Color::kNo:
            return "No (invisible color)";
        case Color::kUnnamed:
            return "Unnamed (enum null value)";
        case Color::k_FIRST_:
            return "_FIRST_ (enum iterator)";
        case Color::k_LAST_:
            return "_LAST_ (enum iterator)";
        default:
            return "No string is provided for current Color";
            // TODO: add feature if ColorMap service is static
    }
}

} // namespace ra_types

#endif // GETSTRING_H
