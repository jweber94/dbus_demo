#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <stdio.h>

class DbusMethodInstance {
    public:
        DbusMethodInstance(sdbus::IConnection* dbusConnection);
        ~DbusMethodInstance() {
            fclose(m_fd);
        }
        
        void startEventLoop();
        void startEventLoopAsync();

    private:
        void linkMethodstoObject();
        void linkSignalsstoObject();
        void linkPropertiesToObjects();
        void setPropertyCb(sdbus::PropertySetCall& msg);
        void getPropertyCb(sdbus::PropertyGetReply& reply);
        void getFileDescriptor(sdbus::MethodCall call);
        void emitSignal();

        // Dbus Service Configuration
        const std::string m_interfaceMethodName; // name at the dbus daemon
        const std::string m_interfaceSignalName;
        const std::string m_objectPath; // like a ressource of a webserver
        // Dbus Daemon interaction
        std::shared_ptr<sdbus::IObject> m_pDbusObject;
        sdbus::IConnection* m_dbusConnection;
        // Signal configuration
        std::string m_signalName;
        std::size_t m_requestsReceivedCounter{0};
        // Property string
        std::string m_propertyStr;

        FILE* m_fd;
        sdbus::UnixFd m_fdSdbus;
};