
/* only call this when imported Wifi and Serial has been initialized */

bool connect_wifi(AsyncUDP& udp, char* ssid, char* pass)
{
	WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
	
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed, Reset the MCU to retry");
    return false;
	}

	return true;
}

bool start_server(AsyncUDP& udp, int port)
{
	if (!udp.listen(port))
	{
		Serial.print("Failed to listen on port ");
		Serial.print(port);
		Serial.println(", Reset MCU to retry");
		return false;
	}

	Serial.print("UDP Listening on IP: ");
	Serial.println(WiFi.localIP());

	return true;
}

void udp_on_packet(AsyncUDP& udp, UDPCallback func, bool debug)
{
    udp.onPacket([](AsyncUDPPacket packet) {
				if (debug)
				{
					Serial.print("UDP Packet Type: ");
					Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
					Serial.print(", From: ");
					Serial.print(packet.remoteIP());
					Serial.print(":");
					Serial.print(packet.remotePort());
					Serial.print(", To: ");
					Serial.print(packet.localIP());
					Serial.print(":");
					Serial.print(packet.localPort());
					Serial.print(", Length: ");
					Serial.print(packet.length());
					Serial.print(", Data: ");
					Serial.write(packet.data(), packet.length());
					Serial.println();
				}

				packet.printf("Got %u bytes of data", packet.length());

				func(packet);
			});
}
