#include <gtest/gtest.h>
#include "ostream_view.h"
#include "ostream_view.h"

#include <sstream>
#include <exception>

TEST(view, update)
{
    std::stringstream ssout;
    OTUS::Model m;
    std::string exp_out = "v1 [\nBlack Point {1 2}\n]\nv1 [\nBlack Point {1 2}\nBlack Line {2 3}\n]\n";
    auto v1 = OTUS::OstreamView::create("v1", &m, ssout);
    OTUS::DPoint<> p1{1, 2};
    OTUS::DPoint<> p2{3, 4};
    m.createPoint(p1);
    m.createLine(p1, p2);
    ASSERT_STREQ(exp_out.c_str(), ssout.str().c_str());
}

TEST(view, null_model)
{
    std::stringstream ssout;
    OTUS::Model* m = nullptr;
    // auto v1 = OTUS::OstreamView::create("v1", m, ssout);
    EXPECT_THROW(OTUS::OstreamView::create("v1", m, ssout), std::invalid_argument);
}