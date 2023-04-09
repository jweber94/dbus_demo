#!/usr/bin/bash

echo "CAUTION: Run this script as root!"

# copy files
make clean && make build_project
cp ./build/dbus-service-app /sbin/dbus-service-app
mkdir -p /etc/dbus-service-app/
cp ./config/config.json /etc/dbus-service-app/
cp ./config/dbus_example.service /etc/systemd/system/
cp ./config/dbus.example.service.conf /etc/dbus-1/system.d/
cp ./config/data.dat /etc/dbus-service-app/

# enable service
systemctl daemon-reload
systemctl enable dbus_example.service
systemctl start dbus_example.service