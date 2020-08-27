#ifndef FIGURE2DVISITOR_H
#define FIGURE2DVISITOR_H

namespace ra_core::figures2d
{
class Dot;
class LineSegment;
class Circle;

class Figure2dVisitor
{
public:
    virtual ~Figure2dVisitor() {}
    virtual void VisitDot(const Dot* dot) const = 0;
    virtual void VisitLine(const LineSegment* ls) const = 0;
    virtual void VisitCircle(const Circle* c) const     = 0;
};
} // namespace ra_core::canvas2d
#endif // FIGURE2DVISITOR_H
