#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "ConfigurationInterface.h"
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace config {
class Configuration : public ConfigurationInterface<json> {
public:
    explicit Configuration(std::filesystem::path filepath);
    [[nodiscard]] bool LoadConfigurationFile() override;
    [[nodiscard]] bool WriteConfigurationFile(json& jsonfile) override;
    [[nodiscard]] Setting GetSetting(ConfigurationName config_name) override;
    [[nodiscard]] bool CreateDefaultConfigurationFile();

private:
    std::filesystem::path filepath_;
    json configData_;
};
} // namespace config

NLOHMANN_JSON_NAMESPACE_BEGIN

template <typename T>
struct adl_serializer<std::optional<T>> {
    static void from_json(const json& j, std::optional<T>& opt)
    {
        if (j.is_null()) {
            opt = std::nullopt;
        }
        else {
            opt = j.get<T>();
        }
    }
    static void to_json(json& json, std::optional<T> t)
    {
        if (t) {
            json = *t;
        }
        else {
            json = nullptr;
        }
    }
};

template <typename T, typename... Ts>
void variant_from_json(const nlohmann::json& j, std::variant<Ts...>& data)
{
    try {
        data = j.get<T>();
    }
    catch (...) {
    }
}

template <typename... Ts>
struct adl_serializer<std::variant<Ts...>> {
    static void to_json(nlohmann::json& j, const std::variant<Ts...>& data)
    {
        std::visit([&j](const auto& v) { j = v; }, data);
    }

    static void from_json(const nlohmann::json& j, std::variant<Ts...>& data)
    {
        (variant_from_json<Ts>(j, data), ...);
    }
};

NLOHMANN_JSON_NAMESPACE_END

#endif // CONFIGURATION_H