#pragma once
#include "utilities.h"

namespace OTUS
{

    class Point;
    class Line;

    class IDrawVisitor
    {
        public:
        virtual ~IDrawVisitor() = default;
        virtual void visit(const Point * point) = 0;
        virtual void visit(const Line* line) = 0;
    };

    class BaseShape
    {
        public:
        BaseShape() = default;
        virtual ~BaseShape() = default;
        virtual DPoint<> coords() const noexcept = 0;
        virtual void accept(IDrawVisitor * ) const = 0;
        virtual Colour colour() const
        {
            return m_colour;
        }
        virtual void setColour(Colour c)
        {
            m_colour = c;
        }
        protected:
        Colour m_colour;
    };

    class Point: public BaseShape
    {
        public:
        explicit Point(DPoint<> const & pt): m_point(pt) {}
        DPoint<> coords() const noexcept override
        {
            return m_point;
        }
        virtual void accept(IDrawVisitor * view_draw_visitor) const override
        {
            view_draw_visitor->visit(this);
        }
        private:
        DPoint<> m_point;
    };

    class Line: public BaseShape
    {
        public:
        explicit Line(DPoint<> const & start, DPoint<> const & end):
            m_start(start), m_end(end) {}
        DPoint<> coords() const noexcept override
        {
            return DPoint<>((m_start.x()+m_end.x())/2., (m_start.y()+m_end.y())/2.);
        }
        virtual void accept(IDrawVisitor * view_draw_visitor) const override
        {
            view_draw_visitor->visit(this);
        }
            
        private:
        DPoint<> m_start;
        DPoint<> m_end;
    };
}