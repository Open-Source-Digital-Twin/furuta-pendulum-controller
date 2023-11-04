#pragma once

#include "ConfigurationName.h"
#include <optional>
#include <string>
#include <variant>

namespace config {

using SettingValueType = std::variant<int, float>;

struct Setting {
    ConfigurationName name;
    SettingValueType value;
    std::optional<SettingValueType> max_value;
    std::optional<SettingValueType> min_value;
    std::optional<std::string> unit;
    std::optional<std::string> description;

public:
    template <typename T>
    T Value() const
    {
        // Check if the variant holds a value of type T
        if (std::holds_alternative<T>(this->value)) {
            return std::get<T>(this->value);
        }
        // If not, throw an exception
        throw std::bad_variant_access();
    }
};

} // namespace config