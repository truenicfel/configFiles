#pragma once

#include <memory>
#include <filesystem>

#include "configuration/ConfigurationParser.h"

namespace configFiles {

    class TOMLParser: public ConfigurationParser {

    public:

        explicit TOMLParser(const std::filesystem::path& path);

        explicit TOMLParser(const std::string& path);

        ~TOMLParser();

        int64_t getLong(const std::string& key, const std::optional<std::string>& group) override;

        double getDouble(const std::string& key, const std::optional<std::string>& group) override;

        std::string getString(const std::string& key, const std::optional<std::string>& group) override;

        std::chrono::time_point<std::chrono::system_clock> getTimePoint(
                const std::string& key, const std::optional<std::string>& group) override;

        void setTimePoint(const std::string& key, const std::optional<std::string>& group,
                          const std::chrono::time_point<std::chrono::system_clock>& timePoint) override;

    private:

        struct TOMLParserMembers;
        std::unique_ptr<TOMLParserMembers> tomlData;

        static std::string timePointToString(const std::chrono::time_point<std::chrono::system_clock>& timePoint);
        static std::chrono::time_point<std::chrono::system_clock> stringToTimePoint(const std::string& timePoint);
    };

} // configFiles

