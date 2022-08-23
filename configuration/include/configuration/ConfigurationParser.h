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

        virtual void setTimePoint(
                const std::string& key,
                const std::optional<std::string>& group,
                const std::chrono::time_point<std::chrono::system_clock>& timePoint) = 0;
    };

}