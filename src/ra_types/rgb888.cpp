#include "rgb888.h"
#include "typedefs.h"

namespace ra_types
{

rgb888::rgb888()
{
    r = 255;
    g = 255;
    b = 255;
}

rgb888::rgb888(uchar val)
{
    r = val;
    g = val;
    b = val;
}

rgb888::rgb888(uchar r_, uchar g_, uchar b_)
{
    r = r_;
    g = g_;
    b = b_;
}

bool rgb888::operator==(const rgb888& b) const
{
    return (this->r == b.r & this->g == b.g & this->b == b.b);
}

bool rgb888::operator!=(const rgb888& b) const
{
    return (this->r != b.r && this->g != b.g && this->b != b.b);
}

bool rgb888::operator<(const rgb888& b) const
{
    return this->r < b.r || this->g < b.g || this->b < b.b;
}

rgb888 rgb888::operator-(const rgb888& b) const
{
    return rgb888(r - b.r, g - b.g, this->b - b.b);
}

} // namespace ra_types
