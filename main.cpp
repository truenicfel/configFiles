#include <iostream>
#include <toml.hpp>
#include <memory>

#include "configuration/ConfigurationParser.h"

int main() {

    auto data = toml::parse("filename.toml");

    toml::value tableTop = toml::get<toml::table>(data);
    toml::value& table = toml::find(data, "mytable");

    toml::value v{};    // table
    v["super"] = "super";
    tableTop.at("test") = v;
    std::cout << tableTop << std::endl;

    std::unique_ptr<toml::value> megaTest(new toml::value(toml::parse("filename.toml")));
    std::make_unique<toml::value>(toml::parse("filename.toml"));
//    std:: cout << data << std::endl;
//
//    // Create and open a text file
//    std::ofstream MyFile("filename.toml");
//
//    // Write to the file
//    MyFile << toml::format(data, 120, 17);
//
//    // Close the file
//    MyFile.close();

    return 0;
}
