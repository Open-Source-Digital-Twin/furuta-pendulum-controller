#include "AngleSensor.h"
#include <gtest/gtest.h>

TEST(AngleSensorTest, DummyTest) {
    auto *angle_sensor = new AngleSensor(42.0);

    EXPECT_EQ(angle_sensor->getAngle(), 42.0);
}
