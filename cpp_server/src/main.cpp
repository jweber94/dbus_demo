#include <iostream>

#include "data_exchange_class.hpp"
#include "dbus_interface.hpp"
#include "command_line_parser.hpp"

int main(int argc, char** argv) {

    CmdParser parser(argc, argv);
    std::cout << "Name is " << parser.getConfig().name << std::endl;

    return 0;
}