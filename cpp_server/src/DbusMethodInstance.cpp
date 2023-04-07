#include "DbusMethodInstance.hpp"

#include <iostream>
#include <functional>

DbusMethodInstance::DbusMethodInstance(sdbus::IConnection* dbusConnection) :
m_interfaceMethodName("org.jens.fdexchange.method"),
m_interfaceSignalName("org.jens.signal"),
m_objectPath("/org/jens/fdexchange"),
m_dbusConnection(dbusConnection)
{
    // create object aka ressource on the dbus server
    m_pDbusObject = sdbus::createObject(*m_dbusConnection, m_objectPath);

    linkMethodstoObject();

    // open up the filedescriptor that we want to share via dbus
    m_fd = fopen("/home/jens/Desktop/dbus_example/cpp_server/config/data.dat", "rw");
    m_fdSdbus = sdbus::UnixFd(fileno(m_fd));
}

void DbusMethodInstance::getFileDescriptor(sdbus::MethodCall call) {
    auto reply = call.createReply();
    if (m_fdSdbus.isValid()) {
        reply << m_fdSdbus;
    } else {
        std::cerr << "No valid filedescriptor. Could not send something valid to the client." << std::endl;
    }
    reply.send();
}

void DbusMethodInstance::linkMethodstoObject() {
    m_pDbusObject->registerMethod(m_interfaceMethodName, "test", "", "h", std::bind(&DbusMethodInstance::getFileDescriptor, this, std::placeholders::_1)); //registerMethod(m_serviceName, "getFileDescriptor", "", "h", &getFileDescriptor);
    m_pDbusObject->finishRegistration();
}

void DbusMethodInstance::startEventLoop() {
    m_dbusConnection->enterEventLoop();
}    
    
void DbusMethodInstance::startEventLoopAsync() {
    m_dbusConnection->enterEventLoopAsync();
}