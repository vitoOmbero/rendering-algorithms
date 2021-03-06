#ifndef FIGURE2DVISITOR_H
#define FIGURE2DVISITOR_H

namespace ra_core::figures2d
{
class Dot;
class LineSegment;
class Circle;
class Triangle;
class Quadrangle;

class Figure2dVisitor
{
public:
    virtual ~Figure2dVisitor() = default;
    virtual void VisitDot(const Dot* dot) const = 0;
    virtual void VisitLine(const LineSegment* ls) const = 0;
    virtual void VisitCircle(const Circle* c) const     = 0;
    virtual void VisitTriangle(const Triangle* tr) const = 0;
    virtual void VisitQuadrangle(const Quadrangle* tr) const = 0;
};
} // namespace ra_core::canvas2d
#endif // FIGURE2DVISITOR_H
