#include "tomlParser/TOMLParser.h"

#include <toml.hpp>

#include <iostream>

namespace configFiles {

    struct TOMLParser::TOMLParserMembers {
        toml::value value;

        TOMLParserMembers(const std::string& path)
        : value(toml::parse(path))
        {
        }

        TOMLParserMembers(const std::filesystem::path& path)
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

    TOMLParser::TOMLParser(const std::string& path)
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

    void TOMLParser::setTimePoint(const std::string& key, const std::optional<std::string>& group,
                                  const std::chrono::time_point<std::chrono::system_clock>& timePoint) {
        std::string timePointAsString = timePointToString(timePoint);
        auto& rootTable = TOMLParserMembers::getRootTable(tomlData).as_table();
        if (group) {
            if (rootTable.contains(group.value())) {
                toml::table& groupTable = rootTable[group.value()].as_table();
                groupTable[key] = timePointAsString;
            } else {
                toml::table groupTable = {};
                groupTable[key] = timePointAsString;
                rootTable[group.value()] = groupTable;
            }
        } else {
            rootTable[key] = timePointAsString;
        }

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


    TOMLParser::~TOMLParser() = default;

} // configFiles