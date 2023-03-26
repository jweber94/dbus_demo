#pragma once

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <stdio.h>


class DbusInterface {
    public:
        DbusInterface();
        ~DbusInterface() {
            fclose(m_fd);
        }
        
        void startEventLoop();
        void startEventLoopAsync();

    private:
        void linkMethodstoObject();
        void linkSignalsstoObject();
        void getFileDescriptor(sdbus::MethodCall call);

        // Dbus Service Configuration
        const std::string m_serviceName; // name at the dbus daemon
        const std::string m_objectPath; // like a ressource of a webserver
        const std::string m_interfaceNameFileDescriptorExchange; // every object path aka ressource can have multuple interfaces where methods and signals can be registered 
        // Dbus Daemon interaction
        std::shared_ptr<sdbus::IObject> m_pDbusObject;
        std::unique_ptr<sdbus::IConnection> m_dbusConnection;

        FILE* m_fd;
};