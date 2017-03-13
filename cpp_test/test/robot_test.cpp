
#include <gtest/gtest.h>

#include "robot.h"

TEST(GenieRobotTest, Construction)
{
	EXPECT_EQ(1, 1);
	ASSERT_EQ(42, 42);
}

int main(int argc, char * argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
