#pragma once
#include "IMembershipFunction.h"

// Трапецеидальная функция принадлежности (включает треугольную при t=0).
class TrapezoidalFunction final : public IMembershipFunction
{
private:
    double center;   // Параметр c (центр)
    double topWidth; // Параметр t (ширина верхнего основания)
    double slope;    // Параметр s (крутизна наклона)

    // Вычисляемые границы
    double y;
    double z;

public:
    TrapezoidalFunction(double c, double t, double s)
        : center(c), topWidth(t), slope(s)
    {
        if (slope != 0.0)
        {
            y = center - (topWidth / 2.0) - (1.0 / slope);
            z = center + (topWidth / 2.0) + (1.0 / slope);
        }
        else
        {
            y = center;
            z = center;
        }
    }

    [[nodiscard]] double getMembership(double x) const override
    {
        if (slope == 0.0)
            return 0.0;

        double leftTop = center - (topWidth / 2.0);
        double rightTop = center + (topWidth / 2.0);

        if (x > z || x < y) return 0.0;
        else if (x >= leftTop && x <= rightTop) return 1.0;
        else if (x >= rightTop && x <= z) return slope * (z - x);
        else if (x >= y && x <= leftTop) return slope * (x - y);
        return 0.0;
    }

    [[nodiscard]] nlohmann::json serialize() const override {
        return {
            {"type", "trapezoidal"},
            {"params", {
                {"c", center},
                {"t", topWidth},
                {"s", slope}
            }}
        };
    }
};
