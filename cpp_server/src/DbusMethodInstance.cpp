#include "DbusMethodInstance.hpp"

#include <iostream>
#include <functional>

DbusMethodInstance::DbusMethodInstance(sdbus::IConnection* dbusConnection) :
m_interfaceMethodName("org.jens.fdexchange.method"),
m_interfaceSignalName("org.jens.signal"),
m_objectPath("/org/jens/fdexchange"),
m_dbusConnection(dbusConnection),
m_signalName("receivedRequestsCounter"),
m_propertyStr("FooBar")
{
    // create object aka ressource on the dbus server
    m_pDbusObject = sdbus::createObject(*m_dbusConnection, m_objectPath);

    // open up the filedescriptor that we want to share via dbus
    m_fd = fopen("/home/jens/Desktop/dbus_example/cpp_server/config/data.dat", "rw");
    if (m_fd) {
        m_fdSdbus = sdbus::UnixFd(fileno(m_fd));
    }
    else {
        std::cerr << "Could not open the file. Terminating program!" << std::endl;
        exit(1);
    }

    linkMethodstoObject();
    linkSignalsstoObject();
    linkPropertiesToObjects();

    m_pDbusObject->finishRegistration();
}

void DbusMethodInstance::getFileDescriptor(sdbus::MethodCall call) {
    std::cout << "Received getFileDescriptor request" << std::endl;
    m_requestsReceivedCounter++;
    if (m_fdSdbus.isValid()) {
        auto reply = call.createReply();
        reply << m_fdSdbus;
        reply.send();
    } else {
        std::cerr << "No valid filedescriptor. Could not send something valid to the client." << std::endl;
        sdbus::Error err("org.jens.fdexchange.method.Error", "Invalid filedescriptor detected");
        auto reply = call.createErrorReply(err);
        reply.send();
    }
    emitSignal();
}

void DbusMethodInstance::setPropertyCb(sdbus::PropertySetCall& msg) {
    std::cout << "setPropertyCb was called" << std::endl;
    msg >> m_propertyStr;
    std::cout << "New value is: " << m_propertyStr << std::endl;
}

void DbusMethodInstance::getPropertyCb(sdbus::PropertyGetReply& reply) {
    std::cout << "getPropertyCb was called" << std::endl;
    reply << m_propertyStr;
}

void DbusMethodInstance::linkMethodstoObject() {
    m_pDbusObject->registerMethod(m_interfaceMethodName, "test", "", "h", std::bind(&DbusMethodInstance::getFileDescriptor, this, std::placeholders::_1));
}

void DbusMethodInstance::linkSignalsstoObject() {    
    m_pDbusObject->registerSignal(m_interfaceSignalName, m_signalName, "i");
}

void DbusMethodInstance::linkPropertiesToObjects() {
    //sdbus::Flags test_flags;
    //test_flags.set(sdbus::Flags::CONST_PROPERTY_VALUE);
    m_pDbusObject->registerProperty(m_interfaceSignalName, "SignalNameTBS", "s", std::bind(&DbusMethodInstance::getPropertyCb, this, std::placeholders::_1), std::bind(&DbusMethodInstance::setPropertyCb, this, std::placeholders::_1), {}); // read/write property
    //m_pDbusObject->registerProperty(m_interfaceSignalName, "SignalNameTBS", "s", std::bind(&DbusMethodInstance::getPropertyCb, this, std::placeholders::_1), test_flags); // Read-Only property
}

// Emit 'concatenated' signal
void DbusMethodInstance::emitSignal() {
    const char* interfaceName = "org.sdbuscpp.Concatenator";
    auto signal = m_pDbusObject->createSignal(m_interfaceSignalName, m_signalName); // Maybe we could write a template for createing and emitting an arbitrary signal
    signal << m_requestsReceivedCounter;
    m_pDbusObject->emitSignal(signal);
    std::cout << "Signal filedescriptor request emitted" << std::endl;
}
    
void DbusMethodInstance::startEventLoop() {
    m_dbusConnection->enterEventLoop();
}    
    
void DbusMethodInstance::startEventLoopAsync() {
    m_dbusConnection->enterEventLoopAsync();
}