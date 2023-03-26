#include "command_line_parser.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

CmdParser::CmdParser(int argc, char** argv) {
    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("config", boost::program_options::value<std::string>(), "Path to the config file (defaults to /etc/dbus_example/config.json)");

    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), m_vm);
    boost::program_options::notify(m_vm);

    // help screen
    if (m_vm.count("help")) {
        std::cout << desc << "\n";
        exit(0);
    }

    // get cmd arg(s)
    if (m_vm.count("config")) {
        m_configPath = m_vm["config"].as<std::string>();
    } else {
        std::cout << "name level was not set but is required. - Could not start the application!\n";
        exit(1);
    }

    // process the received config file
    processConfig();
}

dbusConfig CmdParser::getConfig(){
    return m_dbusConfig;
}

void CmdParser::processConfig() {
    boost::property_tree::ptree configPtree;
    boost::property_tree::read_json(m_configPath, configPtree);
    m_dbusConfig.name = configPtree.get_child("name").get_value<std::string>();
    m_dbusConfig.data_file = configPtree.get_child("file").get_value<std::string>();
}