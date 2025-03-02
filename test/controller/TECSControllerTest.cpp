#include "TECSController.h"
#include "MockConfig.h"
#include "Setting.h"
#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

using namespace testing;
using namespace controller;
using namespace config;

class TECSControllerTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        mockConfig_ = std::make_unique<MockConfiguration>();

        // Set up default expectations for configuration
        EXPECT_CALL(*mockConfig_, GetSetting(ConfigurationName::kControllerProportionalGain))
            .WillRepeatedly(Return(Setting {
                ConfigurationName::kControllerProportionalGain,
                2.0,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt }));
        EXPECT_CALL(*mockConfig_, GetSetting(ConfigurationName::kControllerIntegrativeGain))
            .WillRepeatedly(Return(Setting {
                ConfigurationName::kControllerIntegrativeGain,
                0.5,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt }));
        EXPECT_CALL(*mockConfig_, GetSetting(ConfigurationName::kControllerDerivativeGain))
            .WillRepeatedly(Return(Setting {
                ConfigurationName::kControllerDerivativeGain,
                0.1,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt }));
        EXPECT_CALL(*mockConfig_, GetSetting(ConfigurationName::kControllerMassPendulum))
            .WillRepeatedly(Return(Setting {
                ConfigurationName::kControllerMassPendulum,
                0.1,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt }));
        EXPECT_CALL(*mockConfig_, GetSetting(ConfigurationName::kControllerLengthPendulum))
            .WillRepeatedly(Return(Setting {
                ConfigurationName::kControllerLengthPendulum,
                0.3,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt }));
        EXPECT_CALL(*mockConfig_, GetSetting(ConfigurationName::kControllerLengthRotatingArm))
            .WillRepeatedly(Return(Setting {
                ConfigurationName::kControllerLengthRotatingArm,
                0.2,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt }));
        EXPECT_CALL(*mockConfig_, GetSetting(ConfigurationName::kControllerMomentInertiaPendulum))
            .WillRepeatedly(Return(Setting {
                ConfigurationName::kControllerMomentInertiaPendulum,
                0.01,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt }));
        EXPECT_CALL(*mockConfig_, GetSetting(ConfigurationName::kControllerMomentInertiaRotatingArm))
            .WillRepeatedly(Return(Setting {
                ConfigurationName::kControllerMomentInertiaRotatingArm,
                0.02,
                std::nullopt,
                std::nullopt,
                std::nullopt,
                std::nullopt }));

        controller_ = std::make_unique<TECSController>(*mockConfig_, std::chrono::milliseconds(10));
    }

    std::unique_ptr<MockConfiguration> mockConfig_;
    std::unique_ptr<TECSController> controller_;
};

// Test initialization and energy calculation
TEST_F(TECSControllerTest, InitializationAndEnergyCalculation)
{
    // Initialize with pendulum at rest, hanging down (theta = M_PI)
    PendulumState state { 0.0, 0.0, M_PI, 0.0 };
    controller_->Read(state);

    // Write should execute Calculate() and return output
    double output = controller_->Write();

    // For a pendulum hanging down at rest, controller should try to add energy
    EXPECT_GT(output, 0.0);
}

// Test swing-up control when pendulum is far from upright
TEST_F(TECSControllerTest, SwingUpControl)
{
    // Pendulum hanging down (theta = M_PI) with some velocity
    PendulumState state { 0.0, 0.0, M_PI, 0.5 };
    controller_->Read(state);

    double output = controller_->Write();

    // Output should be capped at 1.0 during swing-up
    EXPECT_LE(std::abs(output), 1.0);

    // Test with pendulum at different angle but still in swing-up mode
    state = { 0.1, 0.1, M_PI - 1.0, 0.2 }; // About 57 degrees from hanging down
    controller_->Read(state);

    output = controller_->Write();
    EXPECT_LE(std::abs(output), 1.0);
}

// Test balancing control when pendulum is near upright
TEST_F(TECSControllerTest, BalancingControl)
{
    // Pendulum nearly upright (theta = 0.1 radians, about 5.7 degrees)
    PendulumState state { 0.0, 0.0, 0.1, 0.0 };
    controller_->Read(state);

    double output = controller_->Write();

    // For small angle from vertical, controller should push in opposite direction of angle
    EXPECT_LT(output, 0.0); // Negative output for positive theta

    // Test with small deviation in the other direction
    state = { 0.0, 0.0, -0.1, 0.0 };
    controller_->Read(state);

    output = controller_->Write();
    EXPECT_GT(output, 0.0); // Positive output for negative theta
}

// Test with heavy pendulum
TEST_F(TECSControllerTest, HeavyPendulumTest)
{
    // Create a new test instance with a heavier pendulum
    auto heavy_config = std::make_unique<MockConfiguration>();

    // Set up expectations for heavy pendulum
    EXPECT_CALL(*heavy_config, GetSetting(ConfigurationName::kControllerProportionalGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerProportionalGain,
            2.0,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*heavy_config, GetSetting(ConfigurationName::kControllerIntegrativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerIntegrativeGain,
            0.5,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*heavy_config, GetSetting(ConfigurationName::kControllerDerivativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerDerivativeGain,
            0.1,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*heavy_config, GetSetting(ConfigurationName::kControllerMassPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMassPendulum,
            0.5,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt })); // 5x heavier
    EXPECT_CALL(*heavy_config, GetSetting(ConfigurationName::kControllerLengthPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthPendulum,
            0.3,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*heavy_config, GetSetting(ConfigurationName::kControllerLengthRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthRotatingArm,
            0.2,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*heavy_config, GetSetting(ConfigurationName::kControllerMomentInertiaPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaPendulum,
            0.01,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*heavy_config, GetSetting(ConfigurationName::kControllerMomentInertiaRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaRotatingArm,
            0.02,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));

    auto heavy_controller = std::make_unique<TECSController>(*heavy_config, std::chrono::milliseconds(10));

    // Test with pendulum at 90 degrees
    PendulumState state { 0.0, 0.0, M_PI / 2, 0.0 };
    heavy_controller->Read(state);
    double heavy_output = heavy_controller->Write();

    // Compare with standard controller
    controller_->Read(state);
    double standard_output = controller_->Write();

    // Heavier pendulum should require more torque (larger absolute output)
    EXPECT_GT(std::abs(heavy_output), std::abs(standard_output));
}

// Test with longer pendulum
TEST_F(TECSControllerTest, LongPendulumTest)
{
    // Create a new test instance with a longer pendulum
    auto long_config = std::make_unique<MockConfiguration>();

    // Set up expectations for long pendulum
    EXPECT_CALL(*long_config, GetSetting(ConfigurationName::kControllerProportionalGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerProportionalGain,
            2.0,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*long_config, GetSetting(ConfigurationName::kControllerIntegrativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerIntegrativeGain,
            0.5,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*long_config, GetSetting(ConfigurationName::kControllerDerivativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerDerivativeGain,
            0.1,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*long_config, GetSetting(ConfigurationName::kControllerMassPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMassPendulum,
            0.1,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*long_config, GetSetting(ConfigurationName::kControllerLengthPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthPendulum,
            0.6, // 2x longer
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*long_config, GetSetting(ConfigurationName::kControllerLengthRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthRotatingArm,
            0.2,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*long_config, GetSetting(ConfigurationName::kControllerMomentInertiaPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaPendulum,
            0.01,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*long_config, GetSetting(ConfigurationName::kControllerMomentInertiaRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaRotatingArm,
            0.02,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));

    auto long_controller = std::make_unique<TECSController>(*long_config, std::chrono::milliseconds(10));

    // Test with pendulum at 90 degrees
    PendulumState state { 0.0, 0.0, M_PI / 2, 0.0 };
    long_controller->Read(state);
    double long_output = long_controller->Write();

    // Compare with standard controller
    controller_->Read(state);
    double standard_output = controller_->Write();

    // Longer pendulum should require more torque
    EXPECT_GT(std::abs(long_output), std::abs(standard_output));
}

// Test output limiting
TEST_F(TECSControllerTest, OutputLimitingTest)
{
    // Create a new test instance with high gains
    auto high_gain_config = std::make_unique<MockConfiguration>();

    // Set up expectations with extreme PID values
    EXPECT_CALL(*high_gain_config, GetSetting(ConfigurationName::kControllerProportionalGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerProportionalGain,
            100.0, // High P gain
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*high_gain_config, GetSetting(ConfigurationName::kControllerIntegrativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerIntegrativeGain,
            50.0, // High I gain
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*high_gain_config, GetSetting(ConfigurationName::kControllerDerivativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerDerivativeGain,
            0.1,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*high_gain_config, GetSetting(ConfigurationName::kControllerMassPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMassPendulum,
            0.1,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*high_gain_config, GetSetting(ConfigurationName::kControllerLengthPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthPendulum,
            0.3,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*high_gain_config, GetSetting(ConfigurationName::kControllerLengthRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthRotatingArm,
            0.2,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*high_gain_config, GetSetting(ConfigurationName::kControllerMomentInertiaPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaPendulum,
            0.01,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*high_gain_config, GetSetting(ConfigurationName::kControllerMomentInertiaRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaRotatingArm,
            0.02,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));

    auto high_gain_controller = std::make_unique<TECSController>(*high_gain_config, std::chrono::milliseconds(10));

    // Large angle that will generate large control output
    PendulumState state { 1.0, 2.0, M_PI - 0.1, -3.0 };
    high_gain_controller->Read(state);

    double output = high_gain_controller->Write();

    // Output should be limited to max value (5.0)
    EXPECT_LE(std::abs(output), 5.0);
}

// Test PID behavior over time
TEST_F(TECSControllerTest, PIDTimeResponseTest)
{
    // Create controllers with different PID configurations

    // P-only controller
    auto p_config = std::make_unique<MockConfiguration>();
    EXPECT_CALL(*p_config, GetSetting(ConfigurationName::kControllerProportionalGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerProportionalGain,
            1.0,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*p_config, GetSetting(ConfigurationName::kControllerIntegrativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerIntegrativeGain,
            0.0,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt })); // No I term
    EXPECT_CALL(*p_config, GetSetting(ConfigurationName::kControllerDerivativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerDerivativeGain,
            0.0,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt })); // No D term
    // Set remaining parameters same as default
    EXPECT_CALL(*p_config, GetSetting(ConfigurationName::kControllerMassPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMassPendulum,
            0.1,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*p_config, GetSetting(ConfigurationName::kControllerLengthPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthPendulum,
            0.3,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*p_config, GetSetting(ConfigurationName::kControllerLengthRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthRotatingArm,
            0.2,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*p_config, GetSetting(ConfigurationName::kControllerMomentInertiaPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaPendulum,
            0.01,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*p_config, GetSetting(ConfigurationName::kControllerMomentInertiaRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaRotatingArm,
            0.02,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));

    auto p_controller = std::make_unique<TECSController>(*p_config, std::chrono::milliseconds(10));

    // PI controller
    auto pi_config = std::make_unique<MockConfiguration>();
    EXPECT_CALL(*pi_config, GetSetting(ConfigurationName::kControllerProportionalGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerProportionalGain,
            1.0,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*pi_config, GetSetting(ConfigurationName::kControllerIntegrativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerIntegrativeGain,
            0.5,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt })); // With I term
    EXPECT_CALL(*pi_config, GetSetting(ConfigurationName::kControllerDerivativeGain))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerDerivativeGain,
            0.0,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt })); // No D term
    // Set remaining parameters same as default
    EXPECT_CALL(*pi_config, GetSetting(ConfigurationName::kControllerMassPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMassPendulum,
            0.1,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*pi_config, GetSetting(ConfigurationName::kControllerLengthPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthPendulum,
            0.3,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*pi_config, GetSetting(ConfigurationName::kControllerLengthRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerLengthRotatingArm,
            0.2,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*pi_config, GetSetting(ConfigurationName::kControllerMomentInertiaPendulum))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaPendulum,
            0.01,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));
    EXPECT_CALL(*pi_config, GetSetting(ConfigurationName::kControllerMomentInertiaRotatingArm))
        .WillRepeatedly(Return(Setting {
            ConfigurationName::kControllerMomentInertiaRotatingArm,
            0.02,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt }));

    auto pi_controller = std::make_unique<TECSController>(*pi_config, std::chrono::milliseconds(10));

    // Start with pendulum at 45 degrees
    PendulumState state { 0.0, 0.0, M_PI / 4, 0.0 };

    // First output with only proportional term
    p_controller->Read(state);
    double p_output = p_controller->Write();

    // First output with PI controller
    pi_controller->Read(state);
    double pi_output1 = pi_controller->Write();

    // Initially outputs should be similar (mostly P term)
    EXPECT_NEAR(p_output, pi_output1, 0.01);

    // Simulate multiple cycles with the same error to accumulate integral term
    for (int i = 0; i < 10; i++) {
        pi_controller->Read(state);
        (void)pi_controller->Write();
    }

    // Final output with accumulated integral term
    double pi_output2 = pi_controller->Write();

    // Integral action should make the control output stronger over time
    EXPECT_GT(std::abs(pi_output2), std::abs(pi_output1));
}

// Test different pendulum positions and velocities
TEST_F(TECSControllerTest, DifferentPendulumPositionsTest)
{
    // Test case array with different pendulum states and expected output signs
    struct TestCase {
        PendulumState state;
        bool expectPositiveOutput;
    };

    std::vector<TestCase> test_cases = {
        // Pendulum hanging down, stationary
        { { 0.0, 0.0, M_PI, 0.0 }, true }, // Should try to add energy

        // Pendulum upright, slight angle
        { { 0.0, 0.0, 0.1, 0.0 }, false }, // Should push back toward center
        { { 0.0, 0.0, -0.1, 0.0 }, true }, // Should push back toward center

        // Pendulum with velocity
        { { 0.0, 0.0, M_PI / 2, 1.0 }, true }, // Moving up, should add energy
        { { 0.0, 0.0, M_PI / 2, -1.0 }, false }, // Moving down, should try to reverse

        // Pendulum with arm rotation
        { { 0.0, 0.5, M_PI / 2, 0.0 }, false }, // Should apply damping to arm
        { { 0.0, -0.5, M_PI / 2, 0.0 }, true } // Should apply damping to arm
    };

    for (const auto& tc : test_cases) {
        controller_->Read(tc.state);
        double output = controller_->Write();

        if (tc.expectPositiveOutput) {
            EXPECT_GT(output, 0.0) << "Failed with state: alpha=" << tc.state.alpha
                                   << ", alpha_dot=" << tc.state.alpha_dot
                                   << ", theta=" << tc.state.theta
                                   << ", theta_dot=" << tc.state.theta_dot;
        }
        else {
            EXPECT_LT(output, 0.0) << "Failed with state: alpha=" << tc.state.alpha
                                   << ", alpha_dot=" << tc.state.alpha_dot
                                   << ", theta=" << tc.state.theta
                                   << ", theta_dot=" << tc.state.theta_dot;
        }
    }
}