#include <iostream>
#include "tomlParser/TOMLParser.h"


int main() {

    configFiles::TOMLParser parser("samples/toml/filled.toml");

    parser.getString("topLevelString", std::nullopt);
    parser.getLong("topLevelLong", std::nullopt);
    parser.getDouble("topLevelDouble", std::nullopt);
    parser.getTimePoint("topLevelTime", std::nullopt);

    parser.getString("levelString", "firstLevel");
    parser.getLong("levelLong", "firstLevel");
    parser.getDouble("levelDouble", "secondLevel");
    parser.getTimePoint("levelTime", "secondLevel");

    std::string version;
    std::string branch;
    std::string hash;
    parser.getBuildInformation(version, branch, hash);

    std::cout << parser.toString() << std::endl;

    parser.setString("topLevelString", std::nullopt, "TLS");
    parser.setLong("topLevelLong", std::nullopt, 100);
    parser.setDouble("topLevelDouble", std::nullopt, 1.11);
    parser.setTimePoint("topLevelTime", std::nullopt, std::chrono::system_clock::now());

    parser.setString("levelString", "firstLevel", "LS");
    parser.setLong("levelLong", "firstLevel", 200);
    parser.setDouble("levelDouble", "secondLevel", 2.22);
    parser.setTimePoint("levelTime", "secondLevel", std::chrono::system_clock::now());

    parser.setBuildInformation();

    parser.writeToFile("samples/toml/filled.toml");
    
    // Create and open a text file
//    std::ofstream MyFile("samples/toml/filename.toml");
//
//    // Write to the file
//    MyFile << std::setw(120) << data;
//
//    // Close the file
//    MyFile.close();
//
//    uint64_t ms = duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    return 0;
}
