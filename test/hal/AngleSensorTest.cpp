#include "AngleSensor.h"
#include <gtest/gtest.h>

TEST(AngleSensorTest, DummyTest)
{
    auto* angle_sensor = new Hal::AngleSensor(42.0);

    EXPECT_EQ(angle_sensor->GetValue(1), 42.0);
}
