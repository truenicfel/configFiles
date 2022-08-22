#include "tomlParser/TOMLParser.h"

#include <toml.hpp>

namespace configFiles {

    TOMLParser::TOMLParser(const std::string& path)
        : tomlData(std::make_unique<toml::value>(toml::parse("filename.toml")))
    {
    }

    int TOMLParser::getInteger(const std::string& key, const std::optional<std::string>& group) {
        return 0;
    }

    double TOMLParser::getDouble(const std::string& key, const std::optional<std::string>& group) {
        return 0;
    }

    std::string TOMLParser::getString(const std::string& key, const std::optional<std::string>& group) {
        return {};
    }
} // configFiles