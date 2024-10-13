#include <gtest/gtest.h>
#include <filesystem>
#include "Configuration.h"

namespace config {

class ConfigurationTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code here
        test_filepath_ = std::filesystem::temp_directory_path() / "test_config.json";
    }

    void TearDown() override {
        // Cleanup code here
        if (std::filesystem::exists(test_filepath_)) {
            std::filesystem::remove(test_filepath_);
        }
    }

    std::filesystem::path test_filepath_;
};

TEST_F(ConfigurationTest, CreateDefaultConfigurationFile) {
    Configuration config(test_filepath_);
    EXPECT_TRUE(std::filesystem::exists(test_filepath_));
}

} // namespace config