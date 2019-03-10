#include <Arduino.h>
#include <esp8266ndn.h>

char PREFIX[] = "/example/nrf52/ble/ping";

ndn::BleServerTransport g_transport;
ndn::Face g_face(g_transport);
ndn::DigestKey g_pvtkey;

ndn::NameWCB<4> g_prefix;
ndn::PingServer g_server(g_face, g_prefix);

void
makePayload(void* arg, const ndn::InterestLite& interest, uint8_t* payloadBuf, size_t* payloadSize)
{
  auto text = reinterpret_cast<const char*>(arg);
  size_t len = strlen(text);
  memcpy(payloadBuf, text, len);
  *payloadSize = len;

  static bool isLedOn = false;
  isLedOn = !isLedOn;
  digitalWrite(LED_BUILTIN, isLedOn);
}

void
setup()
{
  Serial.begin(115200);
  Serial.println();
  ndn::setLogOutput(Serial);

  // BLE MTU is 244, no need for the default 1500-octet buffer
  {
    ndn::PacketBuffer::Options opt;
    opt.maxSize = 244;
    opt.maxNameComps = 8;
    opt.maxKeyNameComps = 8;
    auto newPb = new ndn::PacketBuffer(opt);
    auto oldPb = g_face.swapPacketBuffer(newPb);
    if (oldPb != nullptr) {
      delete oldPb;
    }
  }
  g_transport.begin("NRF52-BLE-NDN");
  g_face.enableTracing(Serial);
  g_face.setSigningKey(g_pvtkey);

  ndn::parseNameFromUri(g_prefix, PREFIX);
  g_server.onProbe(&makePayload, const_cast<void*>(reinterpret_cast<const void*>("PingServer")));

  pinMode(LED_BUILTIN, OUTPUT);
}

void
loop()
{
  g_face.loop();
  delay(10);
}
