#pragma once

#include "ConfigurationName.h"
#include <optional>
#include <string>
#include <variant>

namespace config {

using SettingValueType = std::variant<int, float>;

/**
 * @brief Struct representing the configuration data.  
 * @remark Indipendent from the configuration file. Future development includes a configuration class that 
 parses the configuration file during compile time. Having a fixed size will be beneficial 
 when flashing resource-limited microcontrollers
 */
struct Setting {
    ConfigurationName name;
    SettingValueType value;
    std::optional<SettingValueType> max_value;
    std::optional<SettingValueType> min_value;
    std::optional<std::string> unit;
    std::optional<std::string> description;

public:
    /**
     * @brief Check if the variant holds a value of type T. 
     * 
     * @tparam 
     * @return The value of type T if it holds. If not, throw an exception
     */
    template <typename T>
    T Value() const
    {
        if (std::holds_alternative<T>(this->value)) {
            return std::get<T>(this->value);
        }
        throw std::bad_variant_access();
    }
};

} // namespace config