#include "tomlParser/TOMLParser.h"

#include <toml.hpp>
#include <fstream>
#include <projectInfo/ProjectInfo.h>

namespace configFiles {

    struct TOMLParser::TOMLParserMembers {
        toml::value value;

        explicit TOMLParserMembers(const std::string& path)
        : value(toml::parse(path))
        {
        }

        explicit TOMLParserMembers(const std::filesystem::path& path)
        : value(toml::parse(path))
        {
        }

        ~TOMLParserMembers() = default;

        inline static toml::value& getRootTable(std::unique_ptr<TOMLParser::TOMLParserMembers>& members) {
            return members->value;
        }

        inline static toml::value& getValue(std::unique_ptr<TOMLParser::TOMLParserMembers>& members, const std::string& key) {
            return toml::find(getRootTable(members), key);
        }

    };

    TOMLParser::TOMLParser(const std::filesystem::path& path)
    : tomlData(std::make_unique<TOMLParserMembers>(path))
    {
    }

    int64_t TOMLParser::getLong(const std::string& key, const std::optional<std::string>& group) {
        int64_t result;
        if (!group) {
            result = TOMLParserMembers::getValue(tomlData, key).as_integer();
        } else {
            toml::table& table = TOMLParserMembers::getValue(tomlData, group.value()).as_table();
            result = table[key].as_integer();
        }
        return result;
    }

    double TOMLParser::getDouble(const std::string& key, const std::optional<std::string>& group) {
        double result;
        if (!group){
            result = TOMLParserMembers::getValue(tomlData, key).as_floating();
        } else {
            toml::table& table = TOMLParserMembers::getValue(tomlData, group.value()).as_table();
            result = table[key].as_floating();
        }
        return result;
    }

    std::string TOMLParser::getString(const std::string& key, const std::optional<std::string>& group) {
        std::string result;
        if (!group) {
            result = TOMLParserMembers::getValue(tomlData, key).as_string();
        } else {
            toml::table& table = TOMLParserMembers::getValue(tomlData, group.value()).as_table();
            result = table[key].as_string();
        }
        return result;
    }

    std::chrono::time_point<std::chrono::system_clock>
    TOMLParser::getTimePoint(const std::string& key, const std::optional<std::string>& group) {
        std::string timePointAsString;
        if (!group) {
            timePointAsString = TOMLParserMembers::getValue(tomlData, key).as_string();
        } else {
            toml::table& table = TOMLParserMembers::getValue(tomlData, group.value()).as_table();
            timePointAsString = table[key].as_string();
        }
        return stringToTimePoint(timePointAsString);
    }

    void TOMLParser::setString(const std::string& key, const std::optional<std::string>& group, const std::string& value) {
        auto& rootTable = TOMLParserMembers::getRootTable(tomlData).as_table();
        if (group) {
            if (rootTable.contains(group.value())) {
                toml::table& groupTable = rootTable[group.value()].as_table();
                groupTable[key] = value;
            } else {
                toml::table groupTable = {};
                groupTable[key] = value;
                rootTable[group.value()] = groupTable;
            }
        } else {
            rootTable[key] = value;
        }
    }

    void TOMLParser::setDouble(const std::string& key, const std::optional<std::string>& group, const double& value) {
        auto& rootTable = TOMLParserMembers::getRootTable(tomlData).as_table();
        if (group) {
            if (rootTable.contains(group.value())) {
                toml::table& groupTable = rootTable[group.value()].as_table();
                groupTable[key] = value;
            } else {
                toml::table groupTable = {};
                groupTable[key] = value;
                rootTable[group.value()] = groupTable;
            }
        } else {
            rootTable[key] = value;
        }
    }

    void TOMLParser::setLong(const std::string& key, const std::optional<std::string>& group, const int64_t& value) {
        auto& rootTable = TOMLParserMembers::getRootTable(tomlData).as_table();
        if (group) {
            if (rootTable.contains(group.value())) {
                toml::table& groupTable = rootTable[group.value()].as_table();
                groupTable[key] = value;
            } else {
                toml::table groupTable = {};
                groupTable[key] = value;
                rootTable[group.value()] = groupTable;
            }
        } else {
            rootTable[key] = value;
        }
    }

    void TOMLParser::setTimePoint(const std::string& key, const std::optional<std::string>& group,
                                  const std::chrono::time_point<std::chrono::system_clock>& timePoint) {
        std::string timePointAsString = timePointToString(timePoint);
        setString(key, group, timePointAsString);
    }

    std::string TOMLParser::timePointToString(const std::chrono::time_point<std::chrono::system_clock>& point) {
        const std::time_t timeT = std::chrono::system_clock::to_time_t(point);
        std::stringstream stringstream;
        std::tm* tm = std::localtime(&timeT);
        tm->tm_isdst = -1;
        stringstream << std::put_time(tm, "%d.%m.%Y %T %Z");
        return stringstream.str();
    }

    std::chrono::time_point<std::chrono::system_clock> TOMLParser::stringToTimePoint(const std::string& timePoint) {
        std::istringstream ss(timePoint);
        std::tm t{};
        t.tm_isdst = -1;
        ss >> std::get_time(&t, "%d.%m.%Y %T %Z");
        std::time_t timeT = std::mktime(&t);
        return std::chrono::system_clock::from_time_t(timeT);
    }

    void TOMLParser::writeToFile(const std::filesystem::path& path) {
        std::ofstream ofstream;
        ofstream.open(path);
        if (ofstream) {
            ofstream << tomlData->value << std::endl;
        } else {
            throw std::runtime_error("File could not be opened!");
        }
    }

    std::string TOMLParser::toString() {
        std::stringstream stringstream;
        stringstream << tomlData->value;
        return stringstream.str();
    }

    void TOMLParser::setBuildInformation(const std::string& version, const std::string& branch,
                                         const std::string& commitHash) {
        static const std::string tableName = "buildInfo";
        auto& rootTable = TOMLParserMembers::getRootTable(tomlData).as_table();

        if (!rootTable.contains(tableName)) {
            rootTable[tableName] = toml::table({});
        }
        toml::table& table = rootTable[tableName].as_table();
        table["version"] = version;
        table["branch"] = branch;
        table["commitHash"] = commitHash;
    }

    void TOMLParser::setBuildInformation() {
        setBuildInformation(projectInfo::VERSION, projectInfo::GIT_BRANCH, projectInfo::GIT_HASH);
    }

    void TOMLParser::getBuildInformation(std::string& version, std::string& branch, std::string& commitHash) {
        static const std::string tableName = "buildInfo";
        auto& rootTable = TOMLParserMembers::getRootTable(tomlData).as_table();

        if (rootTable.contains(tableName)) {
            toml::table& table = rootTable[tableName].as_table();
            version = table["version"].as_string();
            branch = table["branch"].as_string();
            commitHash = table["commitHash"].as_string();
        } else {
            version = "";
            branch = "";
            commitHash = "";
        }

    }

    TOMLParser::~TOMLParser() = default;

} // configFiles