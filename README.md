# esp8266ndn on nRF52

Project member: [Junxiao Shi](https://yoursunny.com)

During the hackathon, I ported [esp8266ndn](https://github.com/yoursunny/esp8266ndn) library to [Adafruit nRF52](https://github.com/adafruit/Adafruit_nRF52_Arduino) platform.

* `BleServerTransport` is adapted for nRF52 Bluefruit library, but it's using 16-bit UUIDs instead of 128-bit due to apparent bugs in Bluefruit library.
* Security are software backed.
* All existing unit tests (covering face internals and security) are passing.
* These are tested on Adafruit nRF52832 Feather device.
* Changes do not break compilation on ESP8266 and ESP32, as confirmed by Travis CI.
* There's currently no CI for nRF52.

Code for this effort is in [esp8266ndn](https://github.com/yoursunny/esp8266ndn) repository.
This repository contains a PlatformIO project of the `BlePingServer` example, adding a LED blinking effect.

I also wrote `BleProxy.py`, an NFD to Bluetooth Low Energy proxy.
The proxy creates a BLE transport to nRF52 or ESP32 and a Unix socket transport to NFD, and transfers packets between them.

Comparing to [NDN-Lite](https://github.com/named-data-iot/ndn-lite), esp8266ndn library allows the use of Arduino IDE, which is popular among maker community.
Furthermore, esp8266ndn library is based on ndn-cpp-lite, which ensures wire format compatibility at all times.
`BleProxy.py` is a new valuable tool to test compatibility between heterogeneous entities for esp8266ndn and NDN-Lite alike.

Since this is a one person project, I only accomplished a subset of the originally planned tasks.
This subset was intended for 2 participants, which indicates I've been working at 200% efficiency.
