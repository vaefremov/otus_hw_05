#pragma once
#include <string>
#include <utility>
#include <limits>
#include <ostream>

namespace OTUS
{
/**
 *  
 * 
 */
std::string version();

/**
 * Small utility class to represent points on plane.
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

}
