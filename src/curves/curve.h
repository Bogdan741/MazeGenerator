#ifndef _CURVE_
#define _CURVE_
#include <vector>

namespace MMaze
{
    enum class CurveType
    {
        LINE,
        ARC
    };

    struct Curve
    {
        Curve(CurveType _type);
        CurveType GetType() const;
    private:
        CurveType type;
    };

    struct Line : public Curve
    {
        Line(double x1_, double y1_, double x2_, double y2_);
        Line();
        double x1;
        double x2;
        double y1;
        double y2;
    };

    struct Arc : public Curve
    {
        Arc(double cx_, double cy_, double r_, double theta1_, double theta2_);
        Arc();
        double cx;
        double cy;
        double r;
        double theta1;
        double theta2;
    };
}
#endif