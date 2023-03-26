#pragma once

#include <string>
#include <boost/program_options.hpp>

struct dbusConfig {
    std::string name;
    std::string data_file;
    int socket_fd;
};

class CmdParser {
    public:
        CmdParser(int argc, char** argv);
        CmdParser() = delete;

        dbusConfig getConfig();

    private:
        void processConfig();

        dbusConfig m_dbusConfig;
        std::string m_configPath;
        boost::program_options::variables_map m_vm;
};