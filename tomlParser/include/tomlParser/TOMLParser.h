#pragma once

#include <memory>
#include <filesystem>
#include <string>

#include "configuration/ConfigurationParser.h"

namespace configFiles {

    class TOMLParser: public ConfigurationParser {

    public:

        explicit TOMLParser(const std::filesystem::path& path);

        ~TOMLParser();

        int64_t getLong(const std::string& key, const std::optional<std::string>& group) override;

        double getDouble(const std::string& key, const std::optional<std::string>& group) override;

        std::string getString(const std::string& key, const std::optional<std::string>& group) override;

        std::chrono::time_point<std::chrono::system_clock> getTimePoint(
                const std::string& key, const std::optional<std::string>& group) override;

        void setString(const std::string &key, const std::optional<std::string> &group, const std::string &value) override;

        void setLong(const std::string& key, const std::optional<std::string> &group, const long& value) override;

        void setDouble(const std::string& key, const std::optional<std::string> &group, const double& value) override;

        void setTimePoint(const std::string& key, const std::optional<std::string>& group,
                          const std::chrono::time_point<std::chrono::system_clock>& timePoint) override;

        void writeToFile(const std::filesystem::path& path) override;

        void setBuildInformation(const std::string &version, const std::string &branch,
                                 const std::string &commitHash) override;

        void setBuildInformation() override;

        void getBuildInformation(std::string& version, std::string& branch, std::string& commitHash) override;

        /**
         * Convert the current configuration into a string.
         *
         * @return std::string
         */
        std::string toString();

    private:

        struct TOMLParserMembers;
        std::unique_ptr<TOMLParserMembers> tomlData;

        static std::string timePointToString(const std::chrono::time_point<std::chrono::system_clock>& timePoint);
        static std::chrono::time_point<std::chrono::system_clock> stringToTimePoint(const std::string& timePoint);
    };

} // configFiles

