#pragma once
#include <string>
#include <utility>
#include <limits>
#include <ostream>
#include <cmath>

namespace OTUS
{

/**
 * Small utility class to represent points on a plane.
 *  
 */
template<typename T = double, typename = std::enable_if_t<std::is_floating_point_v<T>>>
class DPoint final
{
    public:
    DPoint() = default;
    ~DPoint() = default;
    explicit DPoint(T const& x, T const& y) noexcept
    {
        m_x = x;
        m_y = y;
    }
    DPoint(DPoint const& from) = default;
    T x() const noexcept
    {
        return m_x;
    }
    T y() const noexcept
    {
        return m_y;
    }
    bool isNear(DPoint const& other, T acc = std::numeric_limits<T>::epsilon())
    {
        return (std::fabs(m_x - other.m_x) <= acc) && (std::fabs(m_y - other.m_y) <= acc);
    }
    private:
    T m_x, m_y;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, DPoint<T> pt)
{
    out << "{" << pt.x() << " " << pt.y() << "}";
    return out;
}

enum class Colour
{
    BLACK, RED, GREEN, BLUE, WHITE
};

constexpr char const* ColourName(Colour c)
{
    switch (c)
    {
    case Colour::BLACK:
        return "Black";
        break;
    case Colour::RED:
        return "Red";
        break;
    case Colour::GREEN:
        return "Green";
        break;
    case Colour::BLUE:
        return "Blue";
        break;
    case Colour::WHITE:
        return "White";
        break;
    default:
        return "Unknown";
    }
}

std::ostream& operator<<(std::ostream& out, Colour c);

}
