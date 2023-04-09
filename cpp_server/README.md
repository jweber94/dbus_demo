# Dbus example service
This project is an example for handing over file descriptors via dbus, makeing the service visable to d-feet and to control the dataexchange between two applications via dbus while the data exchange happens via a unix domain socket.

## Requirements
+ You need to have sdbus-c++ installed on your system
    - https://github.com/Kistler-Group/sdbus-cpp/blob/master/docs/using-sdbus-c++.md
+ You need to have boost installed on your system
    - e.g. via apt: `$ sudo apt install libboost-dev`
    - or by compiling the latest version on your own: https://www.boost.org/doc/libs/1_48_0/doc/html/bbv2/installation.html

## Sending file descriptors and receiving signals via dbus
+ See https://dbus.freedesktop.org/doc/dbus-specification.html section "***Basic Types***" for details
    - You can use the `h` datatype to (de-)serialize file descriptors in dbus
+ Test via terminal:
    - `$ dbus-send --system --print-reply --dest="org.jens.fdexchange" /org/jens/fdexchange org.jens.fdexchange.method.test`
        * You'll get the inode entry back
    - `$ dbus-monitor --system --monitor "type='signal',interface='org.jens.signal'"`
+ Get Property via terminal:
    - `$ dbus-send --system --dest=org.jens.fdexchange --print-reply /org/jens/fdexchange org.freedesktop.DBus.Properties.Get string:org.jens.signal string:SignalNameTBS`
        - Gets the current value as a string from `SignalNameTBS`
+ Set Property via terminal:
    - `$ dbus-send --system --dest=org.jens.fdexchange --print-reply /org/jens/fdexchange org.freedesktop.DBus.Properties.Set string:org.jens.signal string:SignalNameTBS variant:string:Testing` 
        - Sets the value of property `SignalNameTBS` to _Testing_
+ Introspect a service:
    - `$ busctl introspect org.jens.fdexchange /org/jens/fdexchange org.jens.signal`

## Learnings about DBus
+ ***Convenient to use!***
    - Easy syntax with sdbus-cpp
    - Error-Handling via the bus is well thought through (See `auto reply = call.createErrorReply(err);` in `./src/DbusMethodInstance.cpp`)
    - Easy to use signals
        - Also with access rights equipped
    - A ***LOT*** of CLI tooling available --> *Very good for troubleshooting*
+ Fully integrated in yocto/meta-openembedded
+ Access rights enforcement
    - If an interface is not declared within the dbus config (`./config/dbus.example.service.conf`), you can not access it, even if it is implemented and up and running!
        - You can define rights who can access specific interfaces within the dbus config!
            - See `./config/dbus.example.service2.conf`
            - This is fully integrated with [SELinux](https://en.wikipedia.org/wiki/Security-Enhanced_Linux)
+ You can subscribe to the `org.freedesktop.DBus.Properties.PropertiesChanged` interface of a service, which will notify you on a change on the property.
    - Then, you do not need to emit a custom signal on your own!
    - But you ***need to enable*** this within the `./config/dbus.example.service.conf`!
+ Property read and write can be linked with callbacks and these callbacks do NOT call each other (in contrast to OPC UA open62541)