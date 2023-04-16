#!/usr/bin/python3

from dbus_next.aio import MessageBus
from dbus_next.constants import BusType
import asyncio
import os

serviceName = "org.jens.fdexchange"
objectPath = "/org/jens/fdexchange"
methodInterface = "org.jens.fdexchange.method"
signalInterface = "org.jens.signal"

loop = asyncio.get_event_loop()


def printProperties(interface):
    print("Properties:")
    for property in interface.introspection.properties:
        print(property.name)

def printSignals(interface):
    print("Signals:")
    for signal in interface.introspection.signals:
        print(signal.name)

def printMethods(interface):
    print("Methods:")
    for method in interface.introspection.methods:
        print(method.name)

def printIntrospection(interface):
    printProperties(interface)
    printSignals(interface)
    printMethods(interface)

async def main():
    print("Starting the dbus client")
    bus = await MessageBus(bus_type=BusType.SYSTEM, negotiate_unix_fd=True).connect()
    introspection = await bus.introspect(serviceName, objectPath)
    
    obj = bus.get_proxy_object(serviceName, objectPath, introspection)
    fdMethodInterface = obj.get_interface(methodInterface)
    sigInterface = obj.get_interface(signalInterface)

    print("Introspect fdMethodInterface")
    printIntrospection(fdMethodInterface)
    print("\nIntrospect sigInterface")
    printIntrospection(sigInterface)
    
    fdResult = await fdMethodInterface.call_test()
    print(fdResult)
    receivedFile = os.fdopen(fdResult, 'r')
    receivedFile.seek(0)
    data = receivedFile.read()
    print(data)
    receivedFile.close()

    loop.create_future()

try:
    loop.run_until_complete(main())
finally:
    loop.close()