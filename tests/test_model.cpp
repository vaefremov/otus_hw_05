#include <gtest/gtest.h>
#include "utilities.h"

TEST(utilities, version)
{   
    std::string exp{"0.0.42"};
    auto v = version();
    ASSERT_EQ(exp, v);
}