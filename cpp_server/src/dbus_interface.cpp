#include "dbus_interface.hpp"

#include <iostream>
#include <functional>

DbusInterface::DbusInterface() :
m_serviceName("org.jens.fdexchange"),
m_objectPath("/org/jens/fdexchange"),
m_interfaceNameFileDescriptorExchange("org.jens.fdexchange.interface")
{
    // connect to system bus
    m_dbusConnection = sdbus::createSystemBusConnection(m_serviceName);
    // create object aka ressource on the dbus server
    m_pDbusObject = sdbus::createObject(*m_dbusConnection.get(), m_objectPath);

    linkMethodstoObject();
    linkSignalsstoObject();

    m_fd = fopen("./config/data.dat", "rw");
}

void DbusInterface::getFileDescriptor(sdbus::MethodCall call) {
    auto reply = call.createReply();
    reply << fileno(m_fd); // get filedescriptor from FILE* and put it to the reply
    reply.send();
}

void DbusInterface::linkMethodstoObject() {
    m_pDbusObject->registerMethod(m_interfaceNameFileDescriptorExchange, "test", "", "h", std::bind(&DbusInterface::getFileDescriptor, this, std::placeholders::_1)); //registerMethod(m_serviceName, "getFileDescriptor", "", "h", &getFileDescriptor);
}

void DbusInterface::linkSignalsstoObject() {
    std::cout << "Currently no signals to link" << std::endl;
}

void DbusInterface::startEventLoop() {
    m_dbusConnection->enterEventLoop();
}    
    
void DbusInterface::startEventLoopAsync() {
    m_dbusConnection->enterEventLoopAsync();
}