#include "curve.h"
using namespace MMaze;

Curve::Curve(CurveType type_) : type(type_)
{
}
CurveType Curve::GetType() const
{
    return type;
}

Line::Line(double x1_, double y1_, double x2_, double y2_)
    : Curve(CurveType::LINE), x1(x1_), x2(x2_), y1(y1_), y2(y2_)
{
}

Line::Line() : Line(0, 0, 0, 0)
{
}

Arc::Arc(double cx_, double cy_, double r_, double theta1_, double theta2_)
    : Curve(CurveType::ARC), cx(cx_), cy(cy_), r(r_), theta1(theta1_), theta2(theta2_)
{
}

Arc::Arc() : Arc(0, 0, 0, 0, 0)
{
}