#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "configuration/ConfigurationParser.h"

namespace toml {
    template<typename Comment,
            template<typename ...> class Table,
            template<typename ...> class Array>
    class basic_value;
    struct discard_comments;
}
namespace configFiles {

    class TOMLParser: public ConfigurationParser {

    public:

        explicit TOMLParser(const std::string& path);

        ~TOMLParser() = default;

        int getInteger(const std::string& key, const std::optional<std::string>& group) override;

        double getDouble(const std::string& key, const std::optional<std::string>& group) override;

        std::string getString(const std::string& key, const std::optional<std::string>& group) override;

    private:

        // ??
        std::unique_ptr<toml::basic_value<toml::discard_comments, std::unordered_map, std::vector>> tomlData;

    };

} // configFiles

