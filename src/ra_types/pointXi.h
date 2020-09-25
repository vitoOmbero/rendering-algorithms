#ifndef POINTXI_H
#define POINTXI_H

#include <variant>

#include "point2i.h"
#include "typedefs.h"

namespace ra_types
{

union pointXi {
    ra_types::Point2i       point2i;
    ra_types::distance1ui_t point1d;
};
}

#endif // POINT_H
