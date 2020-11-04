#ifndef DIRECTION2D_H
#define DIRECTION2D_H
namespace ra_types
{
/**
 * @brief The eViewDirection enum - description of front view based direction
 */
enum class ViewDirection2d
{
    kNorth, ///< Front View Up
    kEast,  ///< Front View Right
    kSouth, ///< Front View Down
    kWest   ///< Front View Left
};
} // namespace ra_types
#endif // DIRECTION2D_H
