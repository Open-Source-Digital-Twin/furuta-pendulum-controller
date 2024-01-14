#include "AngleSensor.h"
#include <gtest/gtest.h>
#include <memory>

TEST(AngleSensorTest, DummyTest)
{
    auto angle_sensor = std::make_unique<hal::AngleSensor>(42.0);

    EXPECT_EQ(angle_sensor->GetValue(1), 42.0);
}
