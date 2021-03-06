#include <gtest/gtest.h>
#include "utilities.h"
#include "shapes.h"
#include "model.h"

TEST(utilities, point)
{   
    double exp_x = 1.;
    double exp_y = 2.;
    OTUS::DPoint<double> p{exp_x, exp_y};

    ASSERT_DOUBLE_EQ(exp_x, p.x());
    ASSERT_DOUBLE_EQ(exp_y, p.y());

    OTUS::DPoint<float> p2{1, 2};
    ASSERT_FLOAT_EQ(exp_x, p2.x());
    ASSERT_FLOAT_EQ(exp_y, p2.y());

    OTUS::DPoint<> p3{1, 2};
    ASSERT_DOUBLE_EQ(exp_x, p3.x());
    ASSERT_DOUBLE_EQ(exp_y, p3.y());

    OTUS::DPoint<> p4{0, 0};
    // Testing that the operator= works;
    p4 = p3;
    ASSERT_DOUBLE_EQ(exp_x, p4.x());
    ASSERT_DOUBLE_EQ(exp_y, p4.y());
}

TEST(utilities, is_near)
{   
    OTUS::DPoint<double> p1{1, 2};
    OTUS::DPoint<double> p2{1.001, 2};
    ASSERT_FALSE(p1.isNear(p2));
    ASSERT_TRUE(p1.isNear(p2, 0.1));
}

TEST(shapes, point)
{
    double exp_x = 1.;
    double exp_y = 2.;
    OTUS::Point p1{OTUS::DPoint<double>(exp_x, exp_y)};
    OTUS::DPoint<> p1_out = p1.coords();
    ASSERT_DOUBLE_EQ(exp_x, p1_out.x());
    ASSERT_DOUBLE_EQ(exp_y, p1_out.y());
}

TEST(model, add_delete_elt)
{
    OTUS::Model m;
    auto id1 = m.createPoint(OTUS::DPoint(1., 2.));
    ASSERT_EQ(1, m.size());
    m.deleteByID(id1);
    ASSERT_EQ(0, m.size());
}

TEST(model, collisions)
{
    OTUS::Model m;
    auto id1 = m.createPoint(OTUS::DPoint(1., 2.));
    auto id2 = m.createPoint(OTUS::DPoint(10., 20.));
    auto id3 = m.createLine(OTUS::DPoint(1., 1.), OTUS::DPoint(2., 2.));
    
    auto coll1 = m.findCollisions(OTUS::DPoint<>(1., 2.));
    ASSERT_EQ(1, coll1.size());

    auto coll2 = m.findCollisions(OTUS::DPoint<>(1., 1.));
    ASSERT_EQ(0, coll2.size());

    auto coll3 = m.findCollisions(OTUS::DPoint<>(1.5, 1.5));
    ASSERT_EQ(1, coll3.size());
}

TEST(model, create_shape)
{
    OTUS::Model m;
    auto id1 = m.createShape<OTUS::Point>(OTUS::DPoint<>(1., 2.));
    ASSERT_EQ(1, m.size());
    m.deleteByID(id1);
    ASSERT_EQ(0, m.size());

}