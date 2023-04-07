#include <iostream>
#include <string>
#include <memory>

#include "data_exchange_class.hpp"
#include "DbusMethodInstance.hpp"
#include "command_line_parser.hpp"

int main(int argc, char** argv) {
    // parse args
    CmdParser parser(argc, argv);
    std::cout << "Starting dbus service " << parser.getConfig().name << std::endl;
    // start dbus
    std::unique_ptr<sdbus::IConnection> dbusConnection = sdbus::createSystemBusConnection(parser.getConfig().name);
    DbusMethodInstance dbusInstance(dbusConnection.get());
    dbusInstance.startEventLoop();
    return 0;
}