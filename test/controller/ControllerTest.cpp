#include "Controller.h"
#include "ConfigurationName.h"
#include "MockConfig.h"
#include "Setting.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <memory>

using namespace testing;

namespace controller {

class ControllerTest : public Test {
    void SetUp() override
    {
        NiceMock<config::MockConfiguration> mock_config;
        // Set up the mock to return the desired configuration settings.
        ON_CALL(mock_config, GetSetting(config::ConfigurationName::kControllerProportionalGain)).WillByDefault(Return<config::Setting>(config::Setting {
            .name = config::ConfigurationName::kControllerProportionalGain,
            .value = 0.0,
        }));
        ON_CALL(mock_config, GetSetting(config::ConfigurationName::kControllerIntegrativeGain)).WillByDefault(Return<config::Setting>(config::Setting {
            .name = config::ConfigurationName::kControllerIntegrativeGain,
            .value = 0.1,
        }));
        ON_CALL(mock_config, GetSetting(config::ConfigurationName::kControllerDerivativeGain)).WillByDefault(Return<config::Setting>(config::Setting {
            .name = config::ConfigurationName::kControllerDerivativeGain,
            .value = 0.0,
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
