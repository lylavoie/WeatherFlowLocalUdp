# WeatherFlowLocalUdp

## Overview 

Arduino framework library to receive local UDP broadcast updates from WeatherFlow
systems, like the Tempest station.

Based on v171 of the Tempest UDP API: https://weatherflow.github.io/Tempest/api/udp/v171/

Currently supported devices:

* Tempest Station 
* SKY Station
* AIR Station

Currently supported messages:

* Rain Start Event
* Lightning Strike Event
* Rapid Wind
* Observation (AIR Station)
* Observation (SKY Station)
* Observation (Tempest Station)
* Status (device)
* Status (hub)

Each message type is implemented as a dedicated class, with read-only access functions
for the message attributes (i.e. wind speed or direction).  The access functions
automatically convert the units of the attribute according to the base WeatherFlow
class.  The units are set via the constructor and may be updated by the 
WeatherFlow.SetUnits() method.

The base receiver class object (WeatherFlow) provides two required methods.

* WeatherFlow.Begin() must be called after Wi-Fi is connected, and is responsible for
opening the UDP socket to being receiving messages.
* WeatherFlow.ReceiveLoop() must be called within the main loop() function, to handle
parsing of UDP messages.  This method returns true if a value message has been received
and parsed.

Each message class (i.e. RapidWind) provide a read-only Valid() method that returns
true if the message object contains valid data.  Message data, and this valid indicator,
persist between reads, and can not be used as a check for "new" or "updated" data.

At this time, the library does not support multiple stations or devices connected to a
single hub.

## Examples

The following examples are provided.

### Tempest Rapid Wind

This simple example implements the typically receive loop, and prints the RapidWind
message data to the serial port.  RapidWind messages are typically transmitted every
3 to 5 seconds by the stations supporting the wind sensors.

Note, you must update the SSID and Password character arrays for your Wi-Fi network
settings, and that network must be the same broadcast domain where the WeatherFlow
Hub is connected.

