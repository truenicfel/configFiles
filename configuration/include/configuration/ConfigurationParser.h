#pragma once

#include <string>
#include <optional>

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
         * Get integer by key from config file.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional)
         * @return
         */
        virtual int getInteger(
                const std::string& key,
                const std::optional<std::string>& group = std::nullopt) = 0;

        /**
         * Get double by key from config file.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional)
         * @return
         */
        virtual double getDouble(
                const std::string& key,
                const std::optional<std::string>& group = std::nullopt) = 0;
        /**
         * Get string by key from config file.
         *
         * @param key the key in the config file
         * @param group the group the key is in (optional)
         * @return
         */
        virtual std::string getString(
                const std::string& key,
                const std::optional<std::string>& group = std::nullopt) = 0;
    };

}