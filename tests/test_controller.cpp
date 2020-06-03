#include <gtest/gtest.h>
#include "utilities.h"
#include "shapes.h"
#include "model.h"
#include "controller.h"

TEST(controller, delete_under)
{   
    OTUS::Model m;
    OTUS::BaseController c(&m);
    OTUS::DPoint<> pt1(1, 2);
    OTUS::DPoint<> pt2(100, 200);
    c.drawPoint(pt1);
    ASSERT_EQ(1, m.size());
    c.deleteShapesUnder(pt2);
    ASSERT_EQ(1, m.size());
    c.deleteShapesUnder(pt1);
    ASSERT_EQ(0, m.size());
}

TEST(controller, draw_point)
{   
    OTUS::Model m;
    OTUS::BaseController c(&m);
    OTUS::DPoint<> pt1(1, 2);
    c.drawPoint(pt1);
    ASSERT_EQ(1, m.size());
}

TEST(controller, draw_line)
{   
    OTUS::Model m;
    OTUS::BaseController c(&m);
    OTUS::DPoint<> pt1(1, 2);
    OTUS::DPoint<> pt2(100, 200);
    c.startDrawingLine(pt1);
    c.drawPoint(pt2);
    ASSERT_EQ(1, m.size());
}

TEST(controller, change_colour)
{   
    OTUS::Model m;
    OTUS::BaseController c(&m);
    OTUS::DPoint<> pt1(1, 1);
    OTUS::DPoint<> pt2(3, 3);
    OTUS::DPoint<> midpoint(2, 2);
    c.startDrawingLine(pt1);
    c.drawPoint(pt2);
    ASSERT_EQ(1, m.size());
    OTUS::Colour exp_col = OTUS::Colour::RED;
    c.setColour(midpoint, exp_col);
    auto coll = m.findCollisions(midpoint);
    auto shp = coll.at(0);
    ASSERT_EQ(exp_col, shp->colour());
}


