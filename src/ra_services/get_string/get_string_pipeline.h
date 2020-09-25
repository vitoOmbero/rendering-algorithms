#ifndef GET_STRING_PIPELINE_H
#define GET_STRING_PIPELINE_H
#include <sstream>
#include <string>

#include "Canvas2d.h"
#include "PixelBuffer2d.h"
#include "get_string_types.h"

namespace ra_core::pipeline
{
/**
 * @brief GetString - namespace free helping function overload
 * @param pb - recatngular pixel buffer
 * @return pixel buffer string representation
 */
inline std::string GetString(const ra_core::pipeline::PixelBuffer2d& pb)
{
    using namespace std;
    ostringstream oss;
    oss << "Using PixelBuffer: " << pb.getName() << endl;
    oss << "Pixels drawn: " << pb.getTotalElementsDrawn() << endl;
    oss << "Zero point offset: " << ra_types::GetString(pb.getZeroPointOffset())
        << endl;
    /*
    oss << "Height, px: " << pb.getHeight() << endl;
    oss << "Width, dt: " << pb.getDotBufferWidth() << endl;
    oss << "Height, dt: " << pb.getDotBufferHeight() << endl;
    oss << "Dot scale: " << pb.getDotBufferExportDotSize() << endl;


    oss << "Buffer last index: " << pb.getDotBufferLastIndex() << endl;
    oss << "Zero index: " << pb.getDotBufferZeroIndex() << endl;
    oss << "Zero point offset: " << ra_types::GetString(pb.getZeroPointOffset())
        << endl;
    oss << "Dots drawn total: " << pb.getDotBufferDotsNumber() << endl;
    oss << "Lowest visible point: "
        << ra_types::GetString(pb.getLowestVisibleCanvasPoint()) << endl;
    oss << "Highest visible point: "
        << ra_types::GetString(pb.getHighestVisibleCanvasPoint()) << endl;
    oss << "Buffer zero point index: " << pb.getDotBufferZeroPointIndex()
        << endl;
    */
    return oss.str();
}

inline std::string GetString(const ra_core::pipeline::Canvas2d& c)
{
    using namespace std;
    ostringstream oss;
    oss << "Using Canvas2d: " << &c << endl;
    oss << "0x view direction: " << ra_types::GetString(c.getXAxisView())
        << endl;
    oss << "0y view direction: " << ra_types::GetString(c.getYAxisView())
        << endl;
    oss << "Zero point offset: " << ra_types::GetString(c.getZeroPointOffset())
        << endl;
    return oss.str();
}
} // namespace ra_core::pipeline

#endif // GET_STRING_PIPELINE_H
