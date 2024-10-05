#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ConfigurationInterface.h"
#include "ConfigurationName.h"
#include "Setting.h"
#include <filesystem>
#include <nlohmann/json.hpp>

NLOHMANN_JSON_NAMESPACE_BEGIN

/**
 * @brief Serializer. Uses Argument-dependent lookup to choose to_json/from_json functions from the types' namespaces.
Overloaded to work with std::optional
 *
 * @tparam T
 */
template <typename T>
struct adl_serializer<std::optional<T>> {
    /**
     * @brief Converts any value type to a JSON value
     *
     * @param json
     * @param t
     */
    static void to_json(json& json, const std::optional<T>& t)
    {
        if (t.has_value()) {
            json = *t;
        }
        else {
            json = nullptr;
        }
    }
    /**
     * @brief Converts a JSON value to any value type
     *
     * @param j
     * @param opt
     */
    static void from_json(const json& j, std::optional<T>& opt)
    {
        if (j.is_null()) {
            opt = std::nullopt;
        }
        else {
            opt = j.get<T>();
        }
    }
};

/**
 * @brief
 *
 * @tparam T
 * @tparam Ts
 * @param j
 * @param data
 */
template <typename T, typename... Ts>
void variant_from_json(const nlohmann::json& j, std::variant<Ts...>& data)
{
    try {
        data = j.get<T>();
    }
    catch (...) {
    }
}

/**
 * @brief Serializer. Uses Argument-dependent lookup to choose to_json/from_json functions from the types' namespaces.
Overloaded to work with std::variant
 *
 * @tparam Ts
 */
template <typename... Ts>
struct adl_serializer<std::variant<Ts...>> {
    /**
     * @brief Converts any value type to a JSON value
     *
     * @param json
     * @param t
     */
    static void to_json(nlohmann::json& j, const std::variant<Ts...>& data)
    {
        std::visit([&j](const auto& v) { j = v; }, data);
    }
    /**
     * @brief Converts a JSON value to any value type
     *
     * @param j
     * @param opt
     */
    static void from_json(const nlohmann::json& j, std::variant<Ts...>& data)
    {
        (variant_from_json<Ts>(j, data), ...);
    }
};

NLOHMANN_JSON_NAMESPACE_END

namespace config {

using json = nlohmann::json;
class Configuration : public ConfigurationInterface {
public:
    explicit Configuration(std::filesystem::path filepath);
    [[nodiscard]] Setting GetSetting(ConfigurationName config_name) override;

private:
    [[nodiscard]] bool LoadConfigurationFile();
    [[nodiscard]] bool WriteConfigurationFile(json& jsonfile);
    [[nodiscard]] bool CreateDefaultConfigurationFile();

    std::filesystem::path filepath_;
    json configData_;
};

void to_json(json& j, const Setting& setting);
void from_json(const json& j, config::Setting& setting);

} // namespace config

#endif // CONFIGURATION_H
