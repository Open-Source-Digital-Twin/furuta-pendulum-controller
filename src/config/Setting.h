#pragma once

#include "ConfigurationName.h"
#include <optional>
#include <string>
#include <variant>

namespace config {

using SettingValueType = std::variant<int, float, double>;

/**
 * @brief Class representing the configuration data.
 * @remark Independent from the configuration file. Future development includes a configuration class that
 parses the configuration file during compile time. Having a fixed size will be beneficial
 when flashing resource-limited microcontrollers
 */
class Setting {
public:
    Setting(ConfigurationName name,
        SettingValueType value,
        std::optional<SettingValueType> max_value, // NOLINT(bugprone-easily-swappable-parameters)
        std::optional<SettingValueType> min_value,
        std::optional<std::string> unit,
        std::optional<std::string> description)
        : name_(name)
        , value_(value)
        , max_value_(max_value)
        , min_value_(min_value)
        , unit_(std::move(unit))
        , description_(std::move(description)) {};

    [[nodiscard]] ConfigurationName Name() const { return this->name_; };

    /**
     * @brief Check if the variant holds a value of type T.
     *
     * @tparam
     * @return The value of type T if it holds. If not, throw an exception
     */
    template <typename T>
    [[nodiscard]] T Value() const
    {
        if (std::holds_alternative<T>(this->value_)) {
            return std::get<T>(this->value_);
        }
        throw std::bad_variant_access();
    }

    [[nodiscard]] std::optional<SettingValueType> MaxValue() const { return this->max_value_; };
    [[nodiscard]] std::optional<SettingValueType> MinValue() const { return this->min_value_; };
    [[nodiscard]] std::optional<std::string> Unit() const { return this->unit_; };
    [[nodiscard]] std::optional<std::string> Description() const { return this->description_; };

private:
    ConfigurationName name_;
    SettingValueType value_;
    std::optional<SettingValueType> max_value_;
    std::optional<SettingValueType> min_value_;
    std::optional<std::string> unit_;
    std::optional<std::string> description_;
};

} // namespace config