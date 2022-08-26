#pragma once

#include <string>
#include <optional>
#include <chrono>

namespace configFiles {

    /**
     * Interface for parsers.
     *
     * Supports three data types in config files:
     *  - integer
     *  - double
     *  - string
     *  - time
     *
     * Config files might have groups which groups certain keys together for
     * organization.
     *
     */
    class ConfigurationParser {

    public:

        /**
         * Get long by key from config file.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional)
         * @return
         */
        virtual int64_t getLong(
                const std::string& key,
                const std::optional<std::string>& group) = 0;

        /**
         * Get double by key from config file.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional)
         * @return
         */
        virtual double getDouble(
                const std::string& key,
                const std::optional<std::string>& group) = 0;
        /**
         * Get string by key from config file.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional)
         * @return
         */
        virtual std::string getString(
                const std::string& key,
                const std::optional<std::string>& group) = 0;

        /**
         * Get time_point by key from config file.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional)
         * @return
         */
        virtual std::chrono::time_point<std::chrono::system_clock> getTimePoint(
                const std::string& key,
                const std::optional<std::string>& group) = 0;

        /**
         * Set long by key in config file.
         *
         * Note: key and group should be created if they dont exist.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional).
         * @param value the value to set.
         */
        virtual void setString(
                const std::string& key,
                const std::optional<std::string>& group,
                const std::string& value) = 0;

        /**
         * Set double by key in config file.
         *
         * Note: key and group should be created if they dont exist.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional).
         * @param value the value to set.
         */
        virtual void setDouble(
                const std::string& key,
                const std::optional<std::string>& group,
                const double& value) = 0;

        /**
         * Set long by key in config file.
         *
         * Note: key and group should be created if they dont exist.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional).
         * @param value the value to set.
         */
        virtual void setLong(
                const std::string& key,
                const std::optional<std::string>& group,
                const int64_t& value) = 0;

        /**
         * Set time_point by key in config file.
         *
         * Note: key and group should be created if they dont exist.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional).
         * @param timePoint the time point as standard library time point object.
         */
        virtual void setTimePoint(
                const std::string& key,
                const std::optional<std::string>& group,
                const std::chrono::time_point<std::chrono::system_clock>& timePoint) = 0;

        /**
         * Write the current configuration to the given file.
         *
         * @param path path to file.
         * @throws std::runtime_error if file cannot be opened.
         */
        virtual void writeToFile(const std::filesystem::path& path) = 0;

        /**
         * Write information about the build into the configuration.
         *
         * @param version version
         * @param branch git branch
         * @param commitHash git commit hash
         */
        virtual void setBuildInformation(
                const std::string& version,
                const std::string& branch,
                const std::string& commitHash) = 0;
    };

}