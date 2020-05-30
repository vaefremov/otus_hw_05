#include <gtest/gtest.h>
#include "utilities.h"
#include "shapes.h"
#include "model.h"

TEST(utilities, version)
{   
    std::string exp{"0.0.42"};
    auto v = OTUS::version();
    ASSERT_EQ(exp, v);
}

TEST(utilities, point)
{   
    double exp_x = 1.;
    double exp_y = 2.;
    OTUS::DPoint<double> p{1, 2};

    ASSERT_DOUBLE_EQ(exp_x, p.x());
    ASSERT_DOUBLE_EQ(exp_y, p.y());

    OTUS::DPoint<float> p2{1, 2};
    ASSERT_FLOAT_EQ(exp_x, p2.x());
    ASSERT_FLOAT_EQ(exp_y, p2.y());

    OTUS::DPoint<> p3{1, 2};
    ASSERT_DOUBLE_EQ(exp_x, p3.x());
    ASSERT_DOUBLE_EQ(exp_y, p3.y());

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