#include "Controller.h"
#include "ConfigurationName.h"
#include "MockConfig.h"
#include "Setting.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>
#include <optional>

using namespace testing;

namespace controller {

class ControllerTest : public Test {
    void SetUp() override
    {
        NiceMock<config::MockConfiguration> mock_config;
        // Set up the mock to return the desired configuration settings.
        ON_CALL(mock_config, GetSetting(config::ConfigurationName::kControllerProportionalGain)).WillByDefault(Return<config::Setting>(config::Setting {
            config::ConfigurationName::kControllerProportionalGain,
            0.0,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt,
        }));
        ON_CALL(mock_config, GetSetting(config::ConfigurationName::kControllerIntegrativeGain)).WillByDefault(Return<config::Setting>(config::Setting {
            config::ConfigurationName::kControllerIntegrativeGain,
            0.1,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt,
        }));
        ON_CALL(mock_config, GetSetting(config::ConfigurationName::kControllerDerivativeGain)).WillByDefault(Return<config::Setting>(config::Setting {
            config::ConfigurationName::kControllerDerivativeGain,
            0.0,
            std::nullopt,
            std::nullopt,
            std::nullopt,
            std::nullopt,
        }));

        // Create a controller object using the mock configuration.
        controller_ = std::make_unique<controller::Controller>(mock_config, std::chrono::milliseconds(1000));
    }

public:
    std::unique_ptr<controller::Controller> controller_;
};

TEST_F(ControllerTest, calculate)
{
    // Verify that the controller calculated the correct output.
    EXPECT_EQ(controller_->Write(), 0.0);
}

} // namespace controller
