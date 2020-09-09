#ifndef COLOR_H
#define COLOR_H

#include <cstdint>

namespace ra_types
{

/**
 * @brief The color enum - Rainbow colors:
 * red/orange/yellow/green/blue/indigo/violet
 * @details Note that some colors are not properly named, but they are close to
 * originals. That color names have "B" or "_l" chars in names.
 */
enum class eColor
{
    No      = -1, ///< Invisible value
    Unnamed = 0,  ///< Unsupported value

    _FIRST_ = 1, ///< Iteration value

    Black,         ///<#000000	(0,0,0)
    Navy,          ///<#000080	(0,0,128)
    Blue,          ///<#0000FF	(0,0,255)
    Green,         ///<#008000	(0,128,0)
    Teal,          ///<#008080	(0,128,128)
    Blue_light,    ///<####### 	(0,128,255)
    Lime,          ///<#00FF00	(0,255,0)
    Green_springB, ///<#######	(0,255,128) Green_spring is (0,255,127)
    Cyan,          ///<#00FFFF	(0,255,255)
    Indigo,        ///<#######	(75,0,130)
    Maroon,        ///<#800000	(128,0,0)
    Purple,        ///<#800080	(128,0,128)
    Purple_blue,   ///<#8000FF	(128,0,255)
    Olive,         ///<#808000	(128,128,0)
    Gray,          ///<#808080	(128,128,128)
    Sky_blue_dark, ///<#######	(128,128,255)
    Silver,        ///<#C0C0C0	(192,192,192)
    Violet,        ///<####### 	(238,130,238)
    Red,           ///<#FF0000	(255,0,0)
    Fuchsia_dark,  ///<#FF0080	(255,0,128)
    Magenta,       ///<#FF00FF	(255,0,255)
    DarkOrange1B,  ///<#FF8000	(255,128,0) DarkOrange1 is (255,127,0)
    Orange,        ///<#######	(255,165,0)
    Coral_lightd,  ///<#FF8080	(255,128,128)
    Orchid1_l,     ///<#FF80FF	(255,128,255)
    Yellow,        ///<#FFFF00	(255,255,0)
    Khaki1_l,      ///<#FFFF00	(255,255,128)
    White,         ///<#FFFFFF	(255,255,255)

    _LAST_ ///< Iteration value
};

} // namespace ra_types

#endif // COLOR_H
