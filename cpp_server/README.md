# Dbus example service
This project is an example for handing over file descriptors via dbus, makeing the service visable to d-feet and to control the dataexchange between two applications via dbus while the data exchange happens via a unix domain socket.

## Requirements
+ You need to have sdbus-c++ installed on your system
    - https://github.com/Kistler-Group/sdbus-cpp/blob/master/docs/using-sdbus-c++.md
+ You need to have boost installed on your system
    - e.g. via apt: `$ sudo apt install libboost-dev`
    - or by compiling the latest version on your own: https://www.boost.org/doc/libs/1_48_0/doc/html/bbv2/installation.html

## Sending file descriptors via dbus
+ See https://dbus.freedesktop.org/doc/dbus-specification.html section "***Basic Types***" for details
    - You can use the `h` datatype to (de-)serialize file descriptors in dbus
+ Test via terminal:
    - `$ dbus-send --system --print-reply --dest="org.jens.fdexchange" /org/jens/fdexchange org.jens.fdexchange.method.test`
        * You'll get the inode entry back